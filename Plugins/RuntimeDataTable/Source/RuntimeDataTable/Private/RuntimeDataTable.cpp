// Copyright Jared Therriault 2019, 2022

#include "RuntimeDataTable.h"

#include "CsvToGoogleSheetsHandler.h"
#include "RuntimeDataTableModule.h"
#include "RuntimeDataTableProjectSettings.h"

#include "jwt-cpp/jwt.h"

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Engine/GameEngine.h"
#include "Engine/UserDefinedStruct.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/Paths.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/PropertyPortFlags.h"
#include "UObject/TextProperty.h"

FName URuntimeDataTableObject::GetTokenOperationName = "GetToken";

bool URuntimeDataTableWebToken::Init(const FString InTokenText, const int32 SecondsUntilExpiration)
{
	TokenText = InTokenText;

	const FTimespan SecondsInTheFuture = FTimespan::FromSeconds((double)(SecondsUntilExpiration - 1));
	TimeOfExpiration = FDateTime::UtcNow() + SecondsInTheFuture;

	const bool bInvalidToken = TokenText.IsEmpty() || HasTokenExpired();

	bIsInitialized = !bInvalidToken;
	
	return bIsInitialized;
}

bool URuntimeDataTableWebToken::HasTokenExpired() const
{
	const bool bHasTokenExpired = FDateTime::UtcNow() > TimeOfExpiration;
	
	if (bHasTokenExpired)
	{
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: InTokenhas expired, aborting operation."), __FUNCTION__), FRuntimeDataTableModule::ELogType::Error);
	}
	
	return bHasTokenExpired;
}

int32 URuntimeDataTableWebToken::GetNumberOfSecondsUntilExpiration() const
{
	if (bIsInitialized)
	{
		const int32 SecondsLeft = (TimeOfExpiration - FDateTime::UtcNow()).GetSeconds();

		FRuntimeDataTableModule::Print("SecondsLeft: " + FString::FromInt(SecondsLeft));
		
		return SecondsLeft > 0 ? SecondsLeft : 0;
	}

	return 0;
}

FString URuntimeDataTableWebToken::GetTokenText() const
{
	return TokenText;
}

bool URuntimeDataTableObject::GenerateTokenInfoFromString(FRuntimeDataTableTokenInfo& OutTokenInfo,
	const FString InJsonString, const int32 DesiredSecondsUntilExpiration)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InJsonString);

	FString FinalCSV;
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FRuntimeDataTableTokenInfo TokenInfo;

		if (JsonObject->TryGetStringField("client_email", TokenInfo.ServiceAccountEmail) &&
			JsonObject->TryGetStringField("private_key", TokenInfo.PrivateKey) &&
			JsonObject->TryGetStringField("token_uri", TokenInfo.TokenUri))
		{
			TokenInfo.SecondsUntilExpiration = DesiredSecondsUntilExpiration;

			OutTokenInfo = TokenInfo;

			return true;
		}
		
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: Required parameters not found in json string. Requirements: client_email, private_key, token_uri."),
			__FUNCTION__), FRuntimeDataTableModule::ELogType::Error);

		return false;
	}
	
	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Could not deserialise json string."),
		__FUNCTION__), FRuntimeDataTableModule::ELogType::Error);
	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: %s"),
		__FUNCTION__, *InJsonString), FRuntimeDataTableModule::ELogType::Error);

	return false;
}

bool URuntimeDataTableObject::GenerateTokenInfoFromFile(
	FRuntimeDataTableTokenInfo& OutTokenInfo, const FString InPathToFile, const int32 DesiredSecondsUntilExpiration)
{
	FString LoadedString;
	if (UEasyCsv::LoadStringFromLocalFile(InPathToFile, LoadedString))
	{
		return GenerateTokenInfoFromString(OutTokenInfo, LoadedString, DesiredSecondsUntilExpiration);
	}
	
	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Could not load json string."),
		__FUNCTION__), FRuntimeDataTableModule::ELogType::Error);

	return false;
}

void URuntimeDataTableObject::DownloadPublicSheet(
	FString SheetURL, FRDTGetStringDelegate CallOnComplete, const FRuntimeDataTableOperationParams OperationParams)
{
	FString AssetID = GetSpreadsheetIdFromUrl(SheetURL);
	FString gid = GetSheetIdFromUrl(SheetURL);
	FString MIME = "csv";

	FString URL = "https://docs.google.com/spreadsheets/d/" + AssetID + "/export?format=" + MIME + (gid != "" ? "&gid=" + gid : "");
	FRuntimeDataTableModule::Print("URL to download csv is " + URL);

	Request_GET_PublicSheetAsCSV(URL, CallOnComplete, OperationParams);
}

void URuntimeDataTableObject::Request_GET_PublicSheetAsCSV(
	FString RequestURL, const FRDTGetStringDelegate& CallOnComplete, const FRuntimeDataTableOperationParams OperationParams)
{
	FHttpModule* HTTP_Module = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HTTP_Module->CreateRequest();

	Request->SetURL(RequestURL);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Accept"), "text/csv");
	Request->OnProcessRequestComplete().BindUObject(this, &URuntimeDataTableObject::OnResponseReceived_GET_SheetAsCSV, CallOnComplete, OperationParams);
	Request->SetTimeout(OperationParams.RequestTimeout);
	
	AddToRoot();
	Request->ProcessRequest();
}

void URuntimeDataTableObject::OnResponseReceived_GET_SheetAsCSV(
	FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful,
	FRDTGetStringDelegate CallOnComplete, const FRuntimeDataTableOperationParams OperationParams)
{
	FRuntimeDataTableCallbackInfo CallbackInfo;
	CallbackInfo.OperationName = OperationParams.OperationName;
	CallbackInfo.bWasSuccessful = bWasSuccessful;
	GenericValidateHttpResponse(Request, Response, CallbackInfo);
	CallOnComplete.ExecuteIfBound(CallbackInfo);
}

FString URuntimeDataTableObject::GetSpreadsheetIdFromUrl(const FString SheetURL)
{
	FString AssetID = SheetURL.RightChop(SheetURL.Find("/d/") + 3);
	return AssetID.Left(AssetID.Find("/"));
}

FString URuntimeDataTableObject::GetSheetIdFromUrl(const FString SheetURL)
{
	const int32 gidPos = SheetURL.Find("gid=");
	FString gidText = (gidPos >= 0) ? SheetURL.RightChop(gidPos + 4) : "";

	// If there are parameters after the gid, remove them.
	if (gidText.Contains("&"))
	{
		gidText = gidText.Left(gidText.Find("&"));
	}
	return gidText;
}

int32 URuntimeDataTableObject::GetSheetIdFromUrl_Int(const FString SheetURL)
{
	return  FCString::Atoi(*GetSheetIdFromUrl(SheetURL));
}

FString URuntimeDataTableObject::GetGoogleSheetsUrlPrefix()
{
	if (const URuntimeDataTableProjectSettings* Settings = GetDefault<URuntimeDataTableProjectSettings>())
	{
		return Settings->GoogleSheetsUrlPrefix;
	}
		
	FRuntimeDataTableModule::Print("Unable to get URuntimeDataTableProjectSettings Object", FRuntimeDataTableModule::ELogType::Error);
	return "https://docs.google.com/spreadsheets/d/";
}

FString URuntimeDataTableObject::GetMimeCsv()
{
	if (const URuntimeDataTableProjectSettings* Settings = GetDefault<URuntimeDataTableProjectSettings>())
	{
		return Settings->GoogleSheetsMimeCsv;
	}
		
	FRuntimeDataTableModule::Print("Unable to get URuntimeDataTableProjectSettings Object", FRuntimeDataTableModule::ELogType::Error);
	return "text/csv";
}

FString URuntimeDataTableObject::GetGoogleSheetsApiUrlPrefix()
{
	if (const URuntimeDataTableProjectSettings* Settings = GetDefault<URuntimeDataTableProjectSettings>())
	{
		return Settings->GoogleSheetsApiUrlPrefix;
	}
		
	FRuntimeDataTableModule::Print("Unable to get URuntimeDataTableProjectSettings Object", FRuntimeDataTableModule::ELogType::Error);
	return "https://sheets.googleapis.com/v4/spreadsheets/";
}

FString URuntimeDataTableObject::GetGoogleSheetsValuesBatchUpdateURL(const FString InSpreadsheetId)
{
	if (const URuntimeDataTableProjectSettings* Settings = GetDefault<URuntimeDataTableProjectSettings>())
	{
		return GetGoogleSheetsApiUrlPrefix() + InSpreadsheetId + Settings->GoogleSheetsValuesBatchUpdateCommand;
	}
		
	FRuntimeDataTableModule::Print("Unable to get URuntimeDataTableProjectSettings Object", FRuntimeDataTableModule::ELogType::Error);
	return GetGoogleSheetsApiUrlPrefix() + InSpreadsheetId + "/values:batchUpdate";
}

FString URuntimeDataTableObject::GetGoogleSheetsBatchUpdateURL(const FString InSpreadsheetId)
{
	if (const URuntimeDataTableProjectSettings* Settings = GetDefault<URuntimeDataTableProjectSettings>())
	{
		return GetGoogleSheetsApiUrlPrefix() + InSpreadsheetId + Settings->GoogleSheetsBatchUpdateCommand;
	}
		
	FRuntimeDataTableModule::Print("Unable to get URuntimeDataTableProjectSettings Object", FRuntimeDataTableModule::ELogType::Error);
	return GetGoogleSheetsApiUrlPrefix() + InSpreadsheetId + ":batchUpdate";
}

bool URuntimeDataTableObject::ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded(
	const FRuntimeDataTableCallbackInfo InCallbackInfo,
	FEasyCsvInfo& OutCsvInfo,
	ERuntimeDataTableBackupResultCode& OutResultCode,
	const FString& BackupSavePath, const FString& BackupLoadPath)
{	
	if (InCallbackInfo.bWasSuccessful)
	{
		if (UEasyCsv::MakeCsvInfoStructFromString(InCallbackInfo.ResponseAsString, OutCsvInfo))
		{
			FText* Result = nullptr;
			const bool bCanMakeSaveAttempt = !BackupSavePath.IsEmpty() && FPaths::ValidatePath(BackupSavePath, Result);
			
			if (bCanMakeSaveAttempt && UEasyCsv::SaveStringToFileWithFullPath(InCallbackInfo.ResponseAsString, BackupSavePath))
			{
				OutResultCode = ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupSaved;
			}
			else
			{
				OutResultCode = ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupCouldNotBeSaved;
			}
		}
		else
		{
			OutResultCode = ERuntimeDataTableBackupResultCode::DownloadSucceededButCsvCouldNotBeParsed;
		}
	}
	else
	{
		if (FPaths::FileExists(BackupLoadPath))
		{
			if (UEasyCsv::MakeCsvInfoStructFromFile(BackupLoadPath, OutCsvInfo))
			{
				OutResultCode = ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupLoaded;
			}
			else
			{
				OutResultCode = ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupExistsBuCouldNotBeLoaded;
			}
		}
		else
		{
			OutResultCode = ERuntimeDataTableBackupResultCode::DownloadFailedWithoutBackup;
		}
	}

	return OutResultCode == ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupCouldNotBeSaved ||
		OutResultCode == ERuntimeDataTableBackupResultCode::DownloadSucceededAndBackupSaved ||
		OutResultCode == ERuntimeDataTableBackupResultCode::DownloadFailedAndBackupLoaded;
}

bool URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(
	FArrayProperty* ArrayProperty, void* ArrayPtr, UObject* OwningObject, FEasyCsvInfo CsvInfo, bool bNameMatch)
{
	if (CsvInfo.CSV_Headers.Num() < 1 || CsvInfo.CSV_Keys.Num() < 1)
	{
		FRuntimeDataTableModule::Print("UpdateArrayFromCSV_Info_Internal: CSV_Info is not valid. Headers length is " + FString::FromInt(CsvInfo.CSV_Headers.Num()) +
			" and Keys length is " + FString::FromInt(CsvInfo.CSV_Keys.Num()), FRuntimeDataTableModule::ELogType::Error);
		return false;
	}

	FProperty* InnerProperty = ArrayProperty->Inner;

	if (InnerProperty->IsA(FObjectProperty::StaticClass()))
	{
		FScriptArrayHelper ArrayHelper(ArrayProperty, ArrayPtr);
		for (int32 i = 0; i < ArrayHelper.Num(); i++)
		{
			OwningObject = ((FObjectProperty*)InnerProperty)->GetObjectPropertyValue(ArrayHelper.GetRawPtr(i));
			FRuntimeDataTableModule::Print("OwningObject = " + OwningObject->GetName() + " with class " + OwningObject->GetClass()->GetFName().ToString());
			TArray<FString> StringArray = CsvInfo.CSV_Map[CsvInfo.CSV_Keys[i]].StringValues;

			int32 Count = 0;
			for (int32 x = 0; x < CsvInfo.CSV_Headers.Num(); x++)
			{
				FProperty* Property = OwningObject->GetClass()->FindPropertyByName(*CsvInfo.CSV_Headers[x]);
				
				if (Property)
				{
					FString ValueAsString = "";
					if (x > StringArray.Num() - 1)
					{
						break;
					}
					ValueAsString = StringArray[x];
					FRuntimeDataTableModule::Print("ValueAsString = " + ValueAsString);

					if (ValueAsString != "")
					{
						FRuntimeDataTableModule::Print("Count: " + FString::FromInt(Count) + ", ValueAsString is: " + ValueAsString);
						IterateThroughPropertyAndUpdateFromString(
							Property, ArrayHelper.GetRawPtr(i), ValueAsString, OwningObject, true);
					}
					Count++;
				}
			}
		}
	}
	else if (InnerProperty->IsA(FStructProperty::StaticClass()))
	{
		FScriptArrayHelper ArrayHelper(ArrayProperty, ArrayPtr);
		ArrayHelper.EmptyValues(ArrayHelper.Num());
		for (int32 i = 0; i < CsvInfo.CSV_Keys.Num(); i++)
		{
			TArray<FString> StringArray = CsvInfo.CSV_Map[CsvInfo.CSV_Keys[i]].StringValues;
			ArrayHelper.AddValue();

			UScriptStruct* Struct = ((FStructProperty*)InnerProperty)->Struct;
			int32 Count = 0;
			for (TFieldIterator<FProperty> It(Struct); It; ++It)
			{
				FProperty* Property = *It;
				FString ValueAsString = "";

				if (!bNameMatch) // Sequential
				{
					if (Count > StringArray.Num() - 1)
					{
						break;
					}
					ValueAsString = StringArray[Count];
				}
				else 
				{
					FString VariableName = Property->GetAuthoredName().TrimStartAndEnd();
					FRuntimeDataTableModule::Print("VName = " + VariableName);

					int32 MatchIndex = CsvInfo.CSV_Headers.IndexOfByPredicate(([VariableName](FString s)
						{ return s.ToLower().TrimStartAndEnd().Equals(VariableName.ToLower()); }));

					if (MatchIndex != INDEX_NONE && MatchIndex > -1)
					{
						if (MatchIndex > StringArray.Num() - 1)
						{
							break;
						}
						ValueAsString = StringArray[MatchIndex];
					}
				}

				if (ValueAsString != "")
				{
					FRuntimeDataTableModule::Print("Count: " + FString::FromInt(Count) + ", ValueAsString is: " + ValueAsString);
					IterateThroughPropertyAndUpdateFromString(
						Property, ArrayHelper.GetRawPtr(i), ValueAsString, OwningObject, false);
				}
				Count++;
			}
		}
	}
	else
	{
		FRuntimeDataTableModule::Print(
			"The provided array's inner property is not an object or struct. Did you plug in an array of floats or something instead?",
			FRuntimeDataTableModule::ELogType::Error);
		return false;
	}

	return true;
}

void URuntimeDataTableObject::IterateThroughPropertyAndUpdateFromString(
	const FProperty* InnerProperty, void* ContainerPtr, const FString ValueAsString, UObject* OwningObject, bool IsUObject)
{
	if (IsPropertyDataTableSupported(InnerProperty))
	{
		FRuntimeDataTableModule::Print("Passes IsA series");
		// Never assume ArrayDim is always 1
		for (int32 ArrayIndex = 0; ArrayIndex < InnerProperty->ArrayDim; ArrayIndex++)
		{
			// This grabs the pointer to where the property value is stored
			void* ValuePtr; 
			if (IsUObject)
			{
				ValuePtr = InnerProperty->ContainerPtrToValuePtr<void>(OwningObject); //UObject
			}
			else
			{
				ValuePtr = InnerProperty->ContainerPtrToValuePtr<void>(ContainerPtr, ArrayIndex); //Struct
			}
			InnerProperty->InitializeValue(ValuePtr); //This ensures that the value is not optimized away before we get to set it
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
			InnerProperty->ImportText_Direct(*ValueAsString, ValuePtr, OwningObject, PPF_None);
#else
			InnerProperty->ImportText(*ValueAsString, ValuePtr, PPF_None, OwningObject);
#endif
			FRuntimeDataTableModule::Print("Import success"); 
		}
	}
}

FString URuntimeDataTableObject::GenerateCsvFromArray_Internal(FArrayProperty* ArrayProperty, void* ArrayPtr,
	TArray<FString> RowKeys, UObject* OwningObject, FString MembersToInclude, const bool bSortColumnsAlphanumerically)
{
	if (!ArrayProperty || !ArrayPtr || !OwningObject)
	{
		FRuntimeDataTableModule::Print(
			FString::Printf(TEXT("%hs: Parameters are not valid."),
				__FUNCTION__),
			FRuntimeDataTableModule::ELogType::Error);
		return "";
	}

	FString FinalCSV = "";
	
	FProperty* InnerProperty = ArrayProperty->Inner;

	const bool bIsUObject = InnerProperty->IsA(FObjectProperty::StaticClass());

	// All members in objects are stored as a struct, so we can treat them as such
	FStructProperty* StructProperty = (FStructProperty*)InnerProperty;

	if (!StructProperty)
	{
		FRuntimeDataTableModule::Print(
			FString::Printf(TEXT("%hs: StructProperty could not be cast from ArrayProperty->Inner"),
				__FUNCTION__),
			FRuntimeDataTableModule::ELogType::Error);
		return "";
	}

	FScriptArrayHelper ArrayHelper(ArrayProperty, ArrayPtr);

	for (int32 i = 0; i < ArrayHelper.Num(); i++)
	{
		FString RowKey = "";
		if (i < RowKeys.Num())
		{
			RowKey = RowKeys[i];
		}

		if (RowKey.TrimStartAndEnd() == "")
		{
			RowKey = "Row" + FString::FromInt(i);
		}

		FRuntimeDataTableModule::Print(RowKey);

		// Turn whitelist string into whitelist array
		TArray<FString> MembersWhitelist;
		MembersToInclude.ParseIntoArray(MembersWhitelist, TEXT(","));

		// If this is an object then we need to make OwningObject the object in question
		if (bIsUObject)
		{
			OwningObject = ((FObjectProperty*)InnerProperty)->GetObjectPropertyValue(ArrayHelper.GetRawPtr(i));
		}

		// Convert members to string
		FString Row;
		uint8 NumValues;
		FString TopRow;
		IterateThroughStructPropertyAndMakeRowString(
			StructProperty, ArrayHelper.GetRawPtr(i), RowKey, OwningObject,
			bIsUObject, bSortColumnsAlphanumerically, NumValues, TopRow, Row, MembersWhitelist
		);

		//Add to local CSV
		FString Prefix = ",\n";
		if (i == 0) { FinalCSV = TopRow; } //Headers
		FinalCSV += "\n" + Row;
	}

	return FinalCSV;
}

bool URuntimeDataTableObject::IsPropertyDataTableSupported(const FProperty* Property)
{
	//Is Property DataTable supported?
	return ((Property &&
			(Property->IsA(FIntProperty::StaticClass()) ||
			Property->IsA(FNumericProperty::StaticClass()) ||
			Property->IsA(FDoubleProperty::StaticClass()) ||
			Property->IsA(FFloatProperty::StaticClass()) ||
			Property->IsA(FNameProperty::StaticClass()) ||
			Property->IsA(FStrProperty::StaticClass()) ||
			Property->IsA(FBoolProperty::StaticClass()) ||
			Property->IsA(FObjectPropertyBase::StaticClass()) ||
			Property->IsA(FStructProperty::StaticClass()) ||
			Property->IsA(FByteProperty::StaticClass()) ||
			Property->IsA(FTextProperty::StaticClass()) ||
			Property->IsA(FArrayProperty::StaticClass()) ||
			Property->IsA(FSetProperty::StaticClass()) ||
			Property->IsA(FMapProperty::StaticClass()) ||
			Property->IsA(FEnumProperty::StaticClass())
			)));
}

void URuntimeDataTableObject::IterateThroughStructPropertyAndMakeRowString(
		const FStructProperty* StructProperty, void* StructPtr, const FString& RowKey, UObject* OwningObject, const bool bIsUObject,
		const bool bSortColumnsAlphanumerically,
		uint8& OutNumValues, FString& OutTopRow, FString& OutRowString, const TArray<FString>& InMemberWhitelist)
{
	if (!StructProperty || !StructPtr || !OwningObject)
	{
		FRuntimeDataTableModule::Print(
			FString::Printf(TEXT("%hs: Parameters are not valid."),
				__FUNCTION__),
			FRuntimeDataTableModule::ELogType::Error);
		return;
	}
	
	const bool bIncludeAllMembers = InMemberWhitelist.Num() == 0;
	
	// Walk the structs' properties
	const UScriptStruct* Struct = StructProperty->Struct;

	struct FPropertyNameMap
	{
		FPropertyNameMap(FProperty* InProperty, const FString& InAuthoredName)
			: Property(InProperty)
			, AuthoredName(InAuthoredName)
			{}
		
		FProperty* Property;
		FString AuthoredName;
	};
	TArray<FPropertyNameMap> PropertiesToExport;

	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		if (FProperty* Property = *It)
		{
			const FString& VariableName = Property->GetAuthoredName().TrimStartAndEnd();
		
			if (bIncludeAllMembers || InMemberWhitelist.ContainsByPredicate(
				[&VariableName](const FString& s)
			{
				return s.ToLower().TrimStartAndEnd().Equals(VariableName.ToLower());
			}))
			{
				PropertiesToExport.Add(FPropertyNameMap(Property, VariableName));
			}
		}
	}

	if (bSortColumnsAlphanumerically)
	{
		PropertiesToExport.Sort([](const FPropertyNameMap& PropertyA, const FPropertyNameMap& PropertyB)
	   {
		   return PropertyA.AuthoredName < PropertyB.AuthoredName;
	   });
	}
	
	int32 Count = 0;
	OutTopRow = "\"Key\"";
	FString ValueAsString = "\"" + RowKey + "\"";
	
	for (const FPropertyNameMap& Entry : PropertiesToExport)
	{
		OutTopRow += ",\"" + Entry.AuthoredName + "\"";
	
		//Is Property DataTable supported?
		if (IsPropertyDataTableSupported(Entry.Property))
		{
			// Never assume ArrayDim is always 1
			for (int32 ArrayIndex = 0; ArrayIndex < Entry.Property->ArrayDim; ArrayIndex++)
			{
				// This grabs the pointer to where the property value is stored
				void* ValuePtr;
				if (bIsUObject)
				{
					ValuePtr = Entry.Property->ContainerPtrToValuePtr<void>(OwningObject); //UObject
				}
				else
				{
					ValuePtr = Entry.Property->ContainerPtrToValuePtr<void>(StructPtr, ArrayIndex); //Struct
				}

				FString AsString = "";

				// Objects do not serialize to string (causes crash) so the solution is to get the path information instead.
				if (Entry.Property->IsA(FObjectProperty::StaticClass()))
				{
					AsString = Entry.Property->GetFullName();
				}
				else
				{
					Entry.Property->ExportText_Direct(AsString, ValuePtr, ValuePtr, OwningObject, PPF_None);
				}

				AsString = AsString.Replace(TEXT("\""), TEXT("\"\"")); // Double quotes must be exported as quad quotes to deserialize

				ValueAsString += ",\"" + AsString + "\"";
			}
		}

		Count++;
	}

	OutNumValues = Count;

	OutRowString = ValueAsString;
}

FString URuntimeDataTableObject::GetAllObjectVariableNames(const UObject* Object,
	const bool bIncludeOnlyConfigVariables, const bool bIncludeInheritedVariables, FString MemberBlacklist)
{
	FString ReturnValue;
	TArray<FString> VarBlacklist;

	if (MemberBlacklist != "")
	{
		MemberBlacklist.ParseIntoArray(VarBlacklist, TEXT(","));
	}

	const EFieldIteratorFlags::SuperClassFlags IncludeFlags = bIncludeInheritedVariables ? EFieldIteratorFlags::IncludeSuper : EFieldIteratorFlags::ExcludeSuper;

	for (TFieldIterator<FProperty> It(Object->GetClass(), IncludeFlags); It; ++It)
	{
		const FProperty* Property = *It;
		
		if (bIncludeOnlyConfigVariables)
		{
			const bool bIsConfigProperty = (Property->GetPropertyFlags() & EPropertyFlags::CPF_Config) != 0;

			if (!bIsConfigProperty)
			{
				continue;
			}
		}
			
		if (!IsPropertyDataTableSupported(Property))
		{
			continue;
		}
			
		FString VariableName = Property->GetAuthoredName();
		//print(VariableName + " is of class " + Property->GetClass()->GetFName().ToString());
		if (VarBlacklist.Num() > 0 &&
			VarBlacklist.ContainsByPredicate(
			[&VariableName](FString s)
			{
				return s.ToLower().TrimStartAndEnd().Equals(VariableName.ToLower().TrimStartAndEnd());
			}))
		{
			continue;
		}

		ReturnValue += VariableName;
		ReturnValue += ", ";
	}

	return ReturnValue.TrimStartAndEnd().LeftChop(1); // Chop off the last comma
}

void URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv_Internal(
	FRuntimeDataTableTokenInfo InTokenInfo, const FRuntimeDataTableOperationParams OperationParams,
	const FRDTGetStringDelegate& CallOnComplete, const FString& InSheetURL, const bool bSheetIsPublic)
{
	FString ErrorMessage;
	if (bSheetIsPublic)
	{
		DownloadPublicSheet(InSheetURL, CallOnComplete, OperationParams);
	}
	else if (ValidateTokenInfo(InTokenInfo, ErrorMessage))
	{
		// Get the auth token then go the next function on callback
		CreateAndAuthenticateToken(
			InTokenInfo,
			FRDTGetJWTDelegate::CreateUObject(
				this, &URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv_AfterToken,
					OperationParams, CallOnComplete, InSheetURL)
		);
	}
	else
	{
		const FString OutputMessage = FString::Printf(TEXT("InTokenInfo not valid; error: %s"), *ErrorMessage);
		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs:\n%s"), __FUNCTION__, *OutputMessage), FRuntimeDataTableModule::ELogType::Warning);
		CallOnComplete.Execute({OperationParams.OperationName, false, OutputMessage});
	}
}

void URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv_AfterToken(
	const FRuntimeDataTableCallbackInfo CallbackInfo, URuntimeDataTableWebToken* InToken,
	const FRuntimeDataTableOperationParams OperationParams, const FRDTGetStringDelegate CallOnComplete, const FString InSheetURL)
{
	if (!InToken || InToken->HasTokenExpired())
	{
		FRuntimeDataTableCallbackInfo FailedInfo;
		FailedInfo.bWasSuccessful = false;
		FailedInfo.OperationName = OperationParams.OperationName;
		FailedInfo.ResponseAsString = "ERROR: InToken has expired or was not successfully created.";
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(FailedInfo);
		return;
	}

	FString AssetID = GetSpreadsheetIdFromUrl(InSheetURL);
	FString Gid = GetSheetIdFromUrl(InSheetURL);
	const FString Mime = "csv";

	const FString URL = GetGoogleSheetsUrlPrefix() + AssetID + "/export?format=" + Mime + (!Gid.IsEmpty() ? "&gid=" + Gid : "");

	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: URL to download csv is %s"), __FUNCTION__, *URL));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = CreateAuthorizedGenericRequest_Internal(
		InToken->GetTokenText(), OperationParams, "GET",
		URL, false, GetMimeCsv());

	Request->OnProcessRequestComplete().BindUObject(
		this, &URuntimeDataTableObject::OnResponseReceivedGenericReturnString, OperationParams, CallOnComplete);
	Request->ProcessRequest();
}

void URuntimeDataTableObject::WriteCsvToSheet_Internal(FRuntimeDataTableTokenInfo InTokenInfo,
	const FRuntimeDataTableOperationParams OperationParams, const FRDTGetStringDelegate& CallOnComplete,
	const FString& InSpreadsheetID, const int32 InSheetId, const FString& InCsv)
{
	FString ErrorMessage;
	if (ValidateTokenInfo(InTokenInfo, ErrorMessage))
	{
		// Get the auth token then go the next function on callback
		CreateAndAuthenticateToken(
			InTokenInfo,
			FRDTGetJWTDelegate::CreateUObject(
				this, &URuntimeDataTableObject::WriteCsvToSheet_AfterToken,
					OperationParams, CallOnComplete, InSpreadsheetID, InSheetId, InCsv)
		);
	}
}

void URuntimeDataTableObject::WriteCsvToSheet_AfterToken(
	const FRuntimeDataTableCallbackInfo CallbackInfo, URuntimeDataTableWebToken* InToken,
	const FRuntimeDataTableOperationParams OperationParams, FRDTGetStringDelegate CallOnComplete,
	const FString InSpreadsheetId, const int32 InSheetId, const FString InCsv)
{
	// First parse the CSV into a sheet data object and if valid, continue to step 2.
	if (InSheetId < 0)
	{
		FRuntimeDataTableCallbackInfo FailedInfo;
		FailedInfo.bWasSuccessful = false;
		FailedInfo.OperationName = OperationParams.OperationName;
		FailedInfo.ResponseAsString =
			"ERROR: Input 'InSheetId' was not valid. Please enter a valid sheet ID.";
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(FailedInfo);
	}
	
	FCsvToGoogleSheetsHandler SheetTabData = FCsvToGoogleSheetsHandler::CsvToSheetTabData(InCsv);

	if (SheetTabData.GetRowCount() == 0)
	{
		FRuntimeDataTableCallbackInfo FailedInfo;
		FailedInfo.bWasSuccessful = false;
		FailedInfo.OperationName = OperationParams.OperationName;
		FailedInfo.ResponseAsString = "ERROR: InSheetsSheet Tab Data Object has no values.";
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(FailedInfo);
		return;
	}
	
	if (!InToken || InToken->HasTokenExpired())
	{
		FRuntimeDataTableCallbackInfo FailedInfo;
		FailedInfo.bWasSuccessful = false;
		FailedInfo.OperationName = OperationParams.OperationName;
		FailedInfo.ResponseAsString = "ERROR: InToken has expired or was not successfully created.";
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(FailedInfo);
		return;
	}

	const FString RequestURL = GetGoogleSheetsApiUrlPrefix() + InSpreadsheetId + "?&fields=sheets.properties";

	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Built RequestURL:\n%s"), __FUNCTION__, *RequestURL));
	
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		CreateAuthorizedGenericRequest_Internal(
			InToken->GetTokenText(), OperationParams, "GET", RequestURL, false);
	
	Request->OnProcessRequestComplete().BindUObject(
		this, &URuntimeDataTableObject::WriteCsvToSheet_Internal_CompareColumnCounts,
		InToken, OperationParams, CallOnComplete, InSpreadsheetId, InSheetId, InCsv, SheetTabData
	);
	
	Request->ProcessRequest();
}

void URuntimeDataTableObject::WriteCsvToSheet_Internal_CompareColumnCounts(FHttpRequestPtr InRequest,
	FHttpResponsePtr InResponse, bool bWasSuccessful, URuntimeDataTableWebToken* InToken,
	const FRuntimeDataTableOperationParams OperationParams, FRDTGetStringDelegate CallOnComplete,
	FString InSpreadsheetId, const int32 InSheetId, FString InCsv, FCsvToGoogleSheetsHandler SheetTabData)
{
	// Get the target sheet's column count
	// Then check CSV column count against target sheet and if needed, append necessary columns to the target sheet. Else, move on to clear sheet.
	
	FRuntimeDataTableCallbackInfo CallbackInfo;
	CallbackInfo.OperationName = OperationParams.OperationName;
	CallbackInfo.bWasSuccessful = bWasSuccessful;
	GenericValidateHttpResponse(InRequest, InResponse, CallbackInfo);
	if (!CallbackInfo.bWasSuccessful)
	{
		CallbackInfo.ResponseAsString = "ERROR: The GetSpreadsheet operation was not successful.\n\n" + CallbackInfo.ResponseAsString;
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *CallbackInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(CallbackInfo);
		return;
	}

	TSharedPtr<FJsonObject> Spreadsheet = MakeShareable(new FJsonObject());
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(CallbackInfo.ResponseAsString);

	if (FJsonSerializer::Deserialize(JsonReader, Spreadsheet) && Spreadsheet.IsValid())
	{
		int32 RowCount = -1;
		int32 ColumnCount = -1;

		const TArray<TSharedPtr<FJsonValue>>* OutSheets;
		Spreadsheet->TryGetArrayField("sheets", OutSheets);

		if (OutSheets)
		{
			for (const TSharedPtr<FJsonValue>& Sheet : *OutSheets)
			{
				const TSharedPtr<FJsonObject>* SheetProperties;
				Sheet->AsObject()->TryGetObjectField("properties", SheetProperties);

				if (SheetProperties)
				{
					int32 LoopSheetId;
					(*SheetProperties)->TryGetNumberField("sheetId", LoopSheetId);

					if (LoopSheetId == InSheetId)
					{
						const TSharedPtr<FJsonObject>* GridProperties;
						(*SheetProperties)->TryGetObjectField("gridProperties", GridProperties);

						if (GridProperties)
						{
							(*GridProperties)->TryGetNumberField("rowCount", RowCount);
							(*GridProperties)->TryGetNumberField("columnCount", ColumnCount);
						}
							
						break;
					}
				}
			}
		}

		if (!InToken || InToken->HasTokenExpired())
		{
			FRuntimeDataTableCallbackInfo FailedInfo;
			FailedInfo.bWasSuccessful = false;
			FailedInfo.OperationName = OperationParams.OperationName;
			FailedInfo.ResponseAsString = "ERROR: InToken has expired or was not successfully created.";
			FRuntimeDataTableModule::Print(FString::Printf(
				TEXT("%hs: %s"),
				__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
			CallOnComplete.ExecuteIfBound(FailedInfo);
			return;
		}

		if (ColumnCount < SheetTabData.GetColumnCount())
		{
			// If needed, append necessary columns to the target sheet.

			const int32 NumberToAppend = SheetTabData.GetColumnCount() - ColumnCount;
			
			//Build JSON
			const FString JsonContent =
			"{\
				\"requests\": \
				[\
					{\
						\"appendDimension\": \
						{\
							\"sheetId\": " + FString::FromInt(InSheetId) + ",\
							\"dimension\": \"COLUMNS\", \
							\"length\": " + FString::FromInt(NumberToAppend) + "\
						}\
					}\
				]\
			}";

			//Build URL
			const FString RequestURL = GetGoogleSheetsBatchUpdateURL(InSpreadsheetId);

			FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Built JsonContent:\n%s"), __FUNCTION__, *JsonContent));
			FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Built RequestURL:\n%s"), __FUNCTION__, *RequestURL));

			TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
				CreateAuthorizedGenericRequest_Internal(
					InToken->GetTokenText(), OperationParams,
					"POST", RequestURL, false);

			Request->SetContentAsString(JsonContent);

			// Clear target sheet
			Request->OnProcessRequestComplete().BindUObject(
				this, &URuntimeDataTableObject::WriteCsvToSheet_Internal_ClearSheet,
				InToken, OperationParams, CallOnComplete, InSpreadsheetId, InSheetId, InCsv, SheetTabData
			);
	
			Request->ProcessRequest();
		}
		else
		{
			// Clear target sheet
			WriteCsvToSheet_Internal_ClearSheet(
				InRequest, InResponse, bWasSuccessful,
				InToken, OperationParams, CallOnComplete,
				InSpreadsheetId, InSheetId, InCsv, SheetTabData
			);
		}
	}
}

void URuntimeDataTableObject::WriteCsvToSheet_Internal_ClearSheet(FHttpRequestPtr InRequest,
	FHttpResponsePtr InResponse, bool bWasSuccessful, URuntimeDataTableWebToken* InToken,
	const FRuntimeDataTableOperationParams OperationParams, FRDTGetStringDelegate CallOnComplete,
	FString InSpreadsheetId, const int32 InSheetId, FString InCsv, FCsvToGoogleSheetsHandler SheetTabData)
{
	FRuntimeDataTableCallbackInfo CallbackInfo;
	CallbackInfo.OperationName = OperationParams.OperationName;
	CallbackInfo.bWasSuccessful = bWasSuccessful;
	GenericValidateHttpResponse(InRequest, InResponse, CallbackInfo);
	if (!CallbackInfo.bWasSuccessful)
	{
		CallbackInfo.ResponseAsString = "ERROR: The ClearSheet operation was not successful.\n\n" + CallbackInfo.ResponseAsString;
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *CallbackInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(CallbackInfo);
		return;
	}

	if (InSheetId < 0)
	{
		FRuntimeDataTableCallbackInfo FailedInfo;
		FailedInfo.bWasSuccessful = false;
		FailedInfo.OperationName = OperationParams.OperationName;
		FailedInfo.ResponseAsString =
			"ERROR: Input 'InSheetId' was not valid. Please enter a valid sheet ID.";
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(FailedInfo);
	}

	if (!InToken || InToken->HasTokenExpired())
	{
		FRuntimeDataTableCallbackInfo FailedInfo;
		FailedInfo.bWasSuccessful = false;
		FailedInfo.OperationName = OperationParams.OperationName;
		FailedInfo.ResponseAsString = "ERROR: InToken has expired or was not successfully created.";
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(FailedInfo);
		return;
	}

	const FString DataType = "userEnteredValue";

	//Build JSON
	const FString JsonContent =
	"{\
		\"requests\":\
		[\
			{\
				\"updateCells\":\
				{\
					\"range\":\
					{\
						\"sheetId\": " + FString::FromInt(InSheetId) + "\
					},\
					\"fields\": \"" + DataType + "\"\
				}\
			}\
		]\
	}";

	//Build URL
	const FString& RequestURL = GetGoogleSheetsBatchUpdateURL(InSpreadsheetId);

	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Built JsonContent:\n%s"), __FUNCTION__, *JsonContent));
	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Built RequestURL:\n%s"), __FUNCTION__, *RequestURL));
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
	CreateAuthorizedGenericRequest_Internal(
		InToken->GetTokenText(), OperationParams, "POST",
		RequestURL, false);
	
	// Finally, send the CSV to target sheet.
	Request->OnProcessRequestComplete().BindUObject(
		this, &URuntimeDataTableObject::WriteCsvToSheet_Internal_SendCsvDataToSheet,
		InToken, OperationParams, CallOnComplete, InSpreadsheetId, InSheetId, InCsv, SheetTabData
	);

	Request->SetContentAsString(JsonContent);

	Request->ProcessRequest();
}

void URuntimeDataTableObject::WriteCsvToSheet_Internal_SendCsvDataToSheet(FHttpRequestPtr InRequest,
	FHttpResponsePtr InResponse, bool bWasSuccessful, URuntimeDataTableWebToken* InToken,
	const FRuntimeDataTableOperationParams OperationParams, FRDTGetStringDelegate CallOnComplete,
	FString InSpreadsheetId, const int32 InSheetId, FString InCsv, FCsvToGoogleSheetsHandler SheetTabData)
{
	FRuntimeDataTableCallbackInfo CallbackInfo;
	CallbackInfo.OperationName = OperationParams.OperationName;
	CallbackInfo.bWasSuccessful = bWasSuccessful;
	GenericValidateHttpResponse(InRequest, InResponse, CallbackInfo);
	if (!CallbackInfo.bWasSuccessful)
	{
		CallbackInfo.ResponseAsString = "ERROR: The ClearSheet operation was not successful.\n\n" + CallbackInfo.ResponseAsString;
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *CallbackInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(CallbackInfo);
		return;
	}
	
	int32 OutColumnStartIndex, OutRowStartIndex;
	if (FCsvToGoogleSheetsHandler::A1_CellToColumnAndRowIndices("A1", OutColumnStartIndex, OutRowStartIndex))
	{
		FString JsonContent;
		{
			// Master object
			TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
			{
				TArray<TSharedPtr<FJsonValue>> RequestsArray;
				{
					// The single object which will go in the requests array, only contains UpdateCellsObject
					TSharedPtr<FJsonObject> RequestObject = MakeShareable(new FJsonObject);
					{
						// Set updateCells/appendCells fields
						TSharedPtr<FJsonObject> CellsOperationObject = MakeShareable(new FJsonObject);
						{
							CellsOperationObject->SetNumberField("sheetId", InSheetId);

							// rows
							TArray<TSharedPtr<FJsonValue>> RowsArray;
							{
								// for each row in data object
								for (const TArray<FString>& Row : SheetTabData.ArrayValues)
								{
									// Create a new Row object which is the type of RowsArray
									TSharedPtr<FJsonObject> RowObject = MakeShareable(new FJsonObject);
									// Then make a new array for each value in the row. This will be a field in RowObject.
									TArray<TSharedPtr<FJsonValue>> ValuesArray;

									// for each value in data object's row
									for (const FString& Value : Row)
									{
										// Create new object to house the cell data
										TSharedPtr<FJsonObject> CellDataObject = MakeShareable(new FJsonObject);
										{
											// We're only interested in userEnteredValue.stringValue right now for this function
											TSharedPtr<FJsonObject> UserEnteredValueObject = MakeShareable(new FJsonObject);
											{
												UserEnteredValueObject->SetStringField("stringValue", Value);
											}
											CellDataObject->SetObjectField("userEnteredValue", UserEnteredValueObject);
										}

										// Add the cell data object to our ValuesArray
										ValuesArray.Add(MakeShareable(new FJsonValueObject(CellDataObject)));
									}

									// When we're done adding values to ValuesArray we need to add ValuesArray to RowObject as a field
									RowObject->SetArrayField("values", ValuesArray);

									// Then add RowObject to the RowsArray
									RowsArray.Add(MakeShareable(new FJsonValueObject(RowObject)));
								}
							}
							CellsOperationObject->SetArrayField("rows", RowsArray);

							// fields
							CellsOperationObject->SetStringField("fields", "userEnteredValue.stringValue");
						}

						// Add UpdateCellsObject to RequestObject
						RequestObject->SetObjectField("appendCells", CellsOperationObject);
					}

					// Add RequestObject to RequestsArray
					RequestsArray.Add(MakeShareable(new FJsonValueObject(RequestObject)));
				}

				// Add RequestsArray to master object
				JsonObject->SetArrayField("requests", RequestsArray);
			}

			// Serialize master object
			const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonContent);
			FJsonSerializer::Serialize(JsonObject, JsonWriter);
		}

		if (!InToken || InToken->HasTokenExpired())
		{
			FRuntimeDataTableCallbackInfo FailedInfo;
			FailedInfo.bWasSuccessful = false;
			FailedInfo.OperationName = OperationParams.OperationName;
			FailedInfo.ResponseAsString = "ERROR: InToken has expired or was not successfully created.";
			FRuntimeDataTableModule::Print(FString::Printf(
				TEXT("%hs: %s"),
				__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
			CallOnComplete.ExecuteIfBound(FailedInfo);
			return;
		}

		//Build URL
		const FString RequestURL = GetGoogleSheetsBatchUpdateURL(InSpreadsheetId);

		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Built JsonContent:\n%s"), __FUNCTION__, *JsonContent));
		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Built RequestURL:\n%s"), __FUNCTION__, *RequestURL));

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
			CreateAuthorizedGenericRequest_Internal(
				InToken->GetTokenText(), OperationParams,
				"POST", RequestURL, false);

		Request->SetContentAsString(JsonContent);
	
		Request->OnProcessRequestComplete().BindUObject(
			this, &URuntimeDataTableObject::OnResponseReceivedGenericReturnString,
			OperationParams, CallOnComplete
		);
	
		Request->ProcessRequest();
	}
}

void URuntimeDataTableObject::OnResponseReceivedGenericReturnString(
	FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bWasSuccessful, FRuntimeDataTableOperationParams OperationParams,
	FRDTGetStringDelegate CallOnComplete)
{
	FRuntimeDataTableCallbackInfo CallbackInfo;
	CallbackInfo.OperationName = OperationParams.OperationName;
	CallbackInfo.bWasSuccessful = bWasSuccessful;
	GenericValidateHttpResponse(Request, Response, CallbackInfo);

	CallOnComplete.ExecuteIfBound(CallbackInfo);
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> URuntimeDataTableObject::CreateAuthorizedGenericRequest_Internal(
	const FString InTokenText, const FRuntimeDataTableOperationParams OperationParams,
	const FString InVerb, const FString InURL,
	const bool bShouldProcessRequest, const FString ContentType)
{
	FHttpModule* HTTP_Module = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HTTP_Module->CreateRequest();
	
	Request->SetURL(InURL);
	Request->SetVerb(InVerb);
	Request->SetHeader("Authorization", "Bearer " + InTokenText);
	Request->SetHeader("Content-Type", ContentType);
	Request->SetHeader("Accept", ContentType);
	Request->SetTimeout(OperationParams.RequestTimeout);
	AddToRoot();

	if (bShouldProcessRequest)
	{
		Request->ProcessRequest();
	}

	return Request;
}

void URuntimeDataTableObject::CreateAndAuthenticateToken_Internal(FRuntimeDataTableTokenInfo InTokenInfo, const FRDTGetJWTDelegate& CallOnComplete)
{
	FString ErrorMessage;
	if (!ValidateTokenInfo(InTokenInfo, ErrorMessage))
	{
		FRuntimeDataTableCallbackInfo FailedInfo;
		FailedInfo.bWasSuccessful = false;
		FailedInfo.OperationName = GetTokenOperationName;
		FailedInfo.ResponseAsString = "ERROR: InTokenInfo is not valid.";
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: %s"),
			__FUNCTION__, *FailedInfo.ResponseAsString), FRuntimeDataTableModule::ELogType::Error);
		CallOnComplete.ExecuteIfBound(FailedInfo, nullptr);
		return;
	}

	const FString& SignedToken = CreateJavaWebToken(InTokenInfo);

	Request_POST_ForToken(SignedToken, CallOnComplete, InTokenInfo);
}

void URuntimeDataTableObject::Request_POST_ForToken(
	const FString InJavaWebToken,
	const FRDTGetJWTDelegate& CallOnComplete, const FRuntimeDataTableTokenInfo InTokenInfo)
{
	FHttpModule* HTTP_Module = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HTTP_Module->CreateRequest();

	Request->SetURL("https://oauth2.googleapis.com/token?grant_type=urn%3Aietf%3Aparams%3Aoauth%3Agrant-type%3Ajwt-bearer&assertion=" + InJavaWebToken);
	Request->SetVerb("POST");
	Request->OnProcessRequestComplete().BindUObject(
		this, &URuntimeDataTableObject::OnResponseReceivedReturnToken, InTokenInfo, CallOnComplete);
	Request->SetTimeout(30);
	Request->ProcessRequest();
	AddToRoot();
}

void URuntimeDataTableObject::OnResponseReceivedReturnToken(
	FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful,
	FRuntimeDataTableTokenInfo InTokenInfo,	FRDTGetJWTDelegate CallOnComplete)
{	
	FRuntimeDataTableCallbackInfo CallbackInfo;
	CallbackInfo.OperationName = GetTokenOperationName;
	CallbackInfo.bWasSuccessful = bWasSuccessful;
	GenericValidateHttpResponse(Request, Response, CallbackInfo);
	if (CallbackInfo.bWasSuccessful)
	{		
		TSharedPtr<FJsonObject> PostResponse = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(CallbackInfo.ResponseAsString);

		if (FJsonSerializer::Deserialize(JsonReader, PostResponse) && PostResponse.IsValid())
		{
			URuntimeDataTableWebToken* NewToken = NewObject<URuntimeDataTableWebToken>();
			const FString AccessToken = PostResponse->GetStringField("access_token");

			CallbackInfo.bWasSuccessful = NewToken->Init(AccessToken, InTokenInfo.SecondsUntilExpiration);
			
			CallOnComplete.ExecuteIfBound(CallbackInfo, CallbackInfo.bWasSuccessful ? NewToken : nullptr);

			return;
		}
	}
	
	CallOnComplete.ExecuteIfBound(CallbackInfo, nullptr);
}

void URuntimeDataTableObject::GenericValidateHttpResponse(
	FHttpRequestPtr Request, FHttpResponsePtr Response, FRuntimeDataTableCallbackInfo& CallbackInfo)
{
	RemoveFromRoot();
	Request->OnProcessRequestComplete().Unbind();

	CallbackInfo.ResponseAsString = CallbackInfo.bWasSuccessful ? Response->GetContentAsString() : "";
	CallbackInfo.ResponseCode = Response->GetResponseCode();

	// Ensure on Response Code and returned body. The Response Code may say it's a success, but that just means we got a document. May be an error document.
	if (CallbackInfo.bWasSuccessful)
	{
		CallbackInfo.bWasSuccessful = CallbackInfo.ResponseCode < 300 && !CallbackInfo.ResponseAsString.Left(100).Contains("<!DOCTYPE html>");
	}

	FRuntimeDataTableModule::Print(FString::Printf(
		TEXT("%hs: %s Response received, success: %s, Response code: %i, Response:\n%s"),
		__FUNCTION__, *Request->GetVerb(),
		*FString(CallbackInfo.bWasSuccessful ? "true" : "false"),
		CallbackInfo.ResponseCode,
		*CallbackInfo.ResponseAsString),
		CallbackInfo.bWasSuccessful ? FRuntimeDataTableModule::ELogType::Display : FRuntimeDataTableModule::ELogType::Error);
}

FString URuntimeDataTableObject::CreateJavaWebToken(FRuntimeDataTableTokenInfo InTokenInfo)
{
	FString ErrorMessage;
	if (!ValidateTokenInfo(InTokenInfo, ErrorMessage))
	{
		return "";
	}

	InTokenInfo.PrivateKey = InTokenInfo.PrivateKey.ReplaceEscapedCharWithChar();
	InTokenInfo.ClaimUrl = InTokenInfo.ClaimUrl.ReplaceEscapedCharWithChar();
	InTokenInfo.TokenUri = InTokenInfo.TokenUri.ReplaceEscapedCharWithChar();
	
	const jwt::builder<jwt::traits::kazuho_picojson> TokenBuilder = jwt::create()
		.set_algorithm("RS256")
		.set_type("JWT")
		.set_issuer(TCHAR_TO_ANSI(*InTokenInfo.ServiceAccountEmail))
		.set_payload_claim("scope", jwt::claim(std::string{ TCHAR_TO_ANSI(*InTokenInfo.ClaimUrl) }))
		.set_audience(TCHAR_TO_ANSI(*InTokenInfo.TokenUri))
		.set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{ InTokenInfo.SecondsUntilExpiration })
		.set_issued_at(std::chrono::system_clock::now());
	
	const FString& TokenString =
		FString(
			TokenBuilder.sign(
				jwt::algorithm::rs256("",
				TCHAR_TO_ANSI(*InTokenInfo.PrivateKey),
				"", ""
				)
			).c_str()
		); 

	FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs: Token:\n%s"), __FUNCTION__, *TokenString));

	return TokenString;
}

bool URuntimeDataTableObject::ValidateTokenInfo(FRuntimeDataTableTokenInfo& InTokenInfo, FString& ErrorMessage)
{
	ErrorMessage = "No error, looks good!";

	bool bWasSuccessful = true;

	if (InTokenInfo.SecondsUntilExpiration < 1)
	{
		InTokenInfo.SecondsUntilExpiration = 1;

		ErrorMessage = "The SecondsUntilExpiration value was less than 1 and has been set to 1. Validation will continue. If this method returned true, nothing else went wrong.";
		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs:\n%s"), __FUNCTION__, *ErrorMessage), FRuntimeDataTableModule::ELogType::Warning);
	}
	else if (InTokenInfo.SecondsUntilExpiration > 3600)
	{
		InTokenInfo.SecondsUntilExpiration = 3600;

		ErrorMessage = "The SecondsUntilExpiration value was more than 3600 and has been set to 3600. Validation will continue. If this method returned true, nothing else went wrong.";
		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs:\n%s"), __FUNCTION__, *ErrorMessage), FRuntimeDataTableModule::ELogType::Warning);
	}

	InTokenInfo.ServiceAccountEmail.TrimStartAndEndInline();
	if (InTokenInfo.ServiceAccountEmail.IsEmpty() || !InTokenInfo.ServiceAccountEmail.Contains("@"))
	{
		ErrorMessage = "The provided service email is either empty or in the wrong format.";
		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs:\n%s"), __FUNCTION__, *ErrorMessage), FRuntimeDataTableModule::ELogType::Error);
		bWasSuccessful = false;
	}

	InTokenInfo.TokenUri.TrimStartAndEndInline();
	if (InTokenInfo.TokenUri.IsEmpty())
	{
		ErrorMessage = "Token URL is empty.";
		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs:\n%s"), __FUNCTION__, *ErrorMessage), FRuntimeDataTableModule::ELogType::Error);
		bWasSuccessful = false;
	}

	InTokenInfo.PrivateKey.TrimStartAndEndInline();
	if (!InTokenInfo.PrivateKey.EndsWith("\\n"))
	{
		InTokenInfo.PrivateKey += "\\n";
	}
	if (InTokenInfo.PrivateKey.IsEmpty() || 
		!InTokenInfo.PrivateKey.StartsWith("-----BEGIN PRIVATE KEY-----", ESearchCase::CaseSensitive) ||
		!InTokenInfo.PrivateKey.EndsWith("-----END PRIVATE KEY-----\\n", ESearchCase::CaseSensitive))
	{
		ErrorMessage = "The provided service private key is either empty or in the wrong format.";
		FRuntimeDataTableModule::Print(FString::Printf(TEXT("%hs:\n%s"), __FUNCTION__, *ErrorMessage), FRuntimeDataTableModule::ELogType::Error);
		bWasSuccessful = false;
	}

	return bWasSuccessful;
}
