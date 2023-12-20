// Fill out your copyright notice in the Description page of Project Settings.

#include "LGCsvDataProcessorFunctionLibrary.h"
#include "EasyCsv.h"
#include "LGBlueprintFunctionLibrary.h"
#include "Interfaces/LGCsvProcessorInterface.h"


void ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(const FLGCsvInfoImportPayload& InImportPayload, FRDTGetStringDelegate InCallbackDelegate)
{
	if(InImportPayload.URL.IsEmpty()){return;}
	
	FRuntimeDataTableTokenInfo TokenInfo;
	FRuntimeDataTableOperationParams RuntimeDataTableOperationParams;
	RuntimeDataTableOperationParams.OperationName = FName(TEXT("CsvUpdate"));
	RuntimeDataTableOperationParams.FilePath = InImportPayload.FilePath;
	RuntimeDataTableOperationParams.FolderName = InImportPayload.FolderName;
	RuntimeDataTableOperationParams.FileName = InImportPayload.FileName;
	RuntimeDataTableOperationParams.Caller = InImportPayload.Caller;
	RuntimeDataTableOperationParams.CsvArrayTypeTag = InImportPayload.CsvArrayTypeTag;
	RuntimeDataTableOperationParams.DialogueStructID = InImportPayload.DialogueStructID;
	RuntimeDataTableOperationParams.DialogueArrayID = InImportPayload.DialogueArrayID;
	RuntimeDataTableOperationParams.DialogueLabel = InImportPayload.DialogueLabel;
	
	if(!InCallbackDelegate.IsBound()) {UE_LOG(LogCsvDataProcessor, Warning, TEXT("Delegate is not bound."));}
	
	URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv(TokenInfo, RuntimeDataTableOperationParams, InCallbackDelegate, InImportPayload.URL, true);
}

void ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo, void* InArrayPtr, UScriptStruct* InStructPtr, const FName& InPropertyName)
{
	if(!InCallbackInfo.bWasSuccessful) {return;}
	
	FEasyCsvInfo EasyCsvInfo;
	ERuntimeDataTableBackupResultCode RuntimeDataTableBackupResultCode;
	FString ProjectSavePath = InCallbackInfo.FilePath;

	FString CsvFilePath = ProjectSavePath + InCallbackInfo.FolderName + "/" + InCallbackInfo.FileName + ".csv";

	if(!URuntimeDataTableObject::ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded(InCallbackInfo, EasyCsvInfo, RuntimeDataTableBackupResultCode, CsvFilePath, CsvFilePath))
	{
		UE_LOG(LogCsvDataProcessor, Warning, TEXT("Google Sheet Validation Failed"));
		return;
	}

	FLGCsvInfo CSVInfo;
	CSVInfo.CSVToWrite = InCallbackInfo.ResponseAsString;
	CSVInfo.CSVInfoResults = EasyCsvInfo;
	ULGBlueprintFunctionLibrary::FNameArrayToFStringArray(EasyCsvInfo.CSV_Keys, CSVInfo.ExportKeys);

	FArrayProperty* ArrayProperty = FindFProperty<FArrayProperty>(InStructPtr, InPropertyName);
	if(!ArrayProperty){UE_LOG(LogCsvDataProcessor, Error, TEXT("Failed to find ArrayProperty.")); return;}

	if(!URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(ArrayProperty, InArrayPtr, InCallbackInfo.Caller, CSVInfo.CSVInfoResults, true)){UE_LOG(LogDemo, Warning, TEXT("UpdateArrayFromCsvInfo_Internal failed.")); return;}

	FString CSVString = URuntimeDataTableObject::GenerateCsvFromArray_Internal(ArrayProperty, InArrayPtr, CSVInfo.ExportKeys, InCallbackInfo.Caller);

	FString StringToFilePath = ProjectSavePath + InCallbackInfo.FolderName;
	
	if(!UEasyCsv::SaveStringToFile(CSVString,StringToFilePath, InCallbackInfo.FileName)){UE_LOG(LogDemo, Error, TEXT("SaveStringToFile failed.")); return;}

	FEasyCsvInfo CsvInfoResults;
	if(!UEasyCsv::MakeCsvInfoStructFromFile(CsvFilePath, CsvInfoResults)){UE_LOG(LogDemo, Error, TEXT("MakeCsvInfoStructFromFile failed.")); return;}

	CSVInfo.CSVInfoResults = CsvInfoResults;
		
	if(URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(ArrayProperty, InArrayPtr, InCallbackInfo.Caller, CSVInfo.CSVInfoResults, true))
	{
		if (!IsValid(InCallbackInfo.Caller) || !InCallbackInfo.Caller->Implements<ULGCsvProcessorInterface>()) {return;}
		
		if (ILGCsvProcessorInterface* DialogueProcessorObject = Cast<ILGCsvProcessorInterface>(InCallbackInfo.Caller))
		{
			DialogueProcessorObject->Execute_OnCsvProcessComplete(InCallbackInfo.Caller, InCallbackInfo, InStructPtr);

			if(DialogueProcessorObject->Execute_StructTypeHasEmbeddedCsv(InCallbackInfo.Caller, InCallbackInfo.CsvArrayTypeTag))
			{
				FString EmbeddedSavePath = ProjectSavePath + InCallbackInfo.FolderName;
				DialogueProcessorObject->Execute_OnRequestCheckForEmbeddedCsv(InCallbackInfo.Caller, InCallbackInfo.CsvArrayTypeTag, EmbeddedSavePath, InCallbackInfo.DialogueLabel, InCallbackInfo.DialogueStructID, InCallbackInfo.DialogueArrayID);
			}
		}
	}
}


