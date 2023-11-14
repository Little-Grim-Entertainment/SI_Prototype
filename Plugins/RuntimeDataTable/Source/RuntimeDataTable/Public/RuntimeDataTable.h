// Copyright Jared Therriault 2019, 2022

#pragma once

#include "EasyCsv.h"

#include "HttpModule.h"
#include "UObject/Object.h"

#include "RuntimeDataTable.generated.h"

class URuntimeDataTableObject;
class URuntimeDataTableWebToken;

struct FCsvToGoogleSheetsHandler;

// Returned in every delegate
USTRUCT(BlueprintType)
struct FRuntimeDataTableCallbackInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Runtime DataTable")
	FName OperationName = NAME_None;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Runtime DataTable")
	bool bWasSuccessful = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime DataTable")
	FString ResponseAsString = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime DataTable")
	int32 ResponseCode = INDEX_NONE;
};

// Used to return a JWT internally. Don't use this.
DECLARE_DELEGATE_TwoParams(FRDTGetJWTDelegate, const FRuntimeDataTableCallbackInfo, URuntimeDataTableWebToken*);

DECLARE_DYNAMIC_DELEGATE_OneParam(FRDTGetStringDelegate, FRuntimeDataTableCallbackInfo, CallbackInfo);

// Sent with every operation
USTRUCT(BlueprintType)
struct FRuntimeDataTableOperationParams
{
	GENERATED_BODY()

	/** A name for your operation for tracking purposes */
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")
	FName OperationName = NAME_None;

	/** How long to wait for the operation to complete before a timeout is considered */
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")
	float RequestTimeout = 30.f;
};

// Used to build an authentication token
USTRUCT(BlueprintType)
struct FRuntimeDataTableTokenInfo
{
	GENERATED_BODY()

	// Maps to: private_key in the json
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")
		FString PrivateKey;

	// Maps to: client_email in the json
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")
		FString ServiceAccountEmail;

	// Only change this value if you know it needs to be changed. Not found in the json.
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")
		FString ClaimUrl = "https://www.googleapis.com/auth/spreadsheets";

	// Maps to: token_uri in the json. Only change this value if you know it needs to be changed
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")
		FString TokenUri = "https://oauth2.googleapis.com/token";

	// How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour).
	// Generally it's best practice to keep the expiration short and generate a new token for each operation.
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")
		int32 SecondsUntilExpiration = 30;
};

UENUM(BlueprintType)
enum class ERuntimeDataTableBackupResultCode : uint8
{
	DownloadFailedWithoutBackup = 0,
	DownloadFailedAndBackupExistsBuCouldNotBeLoaded,
	DownloadSucceededButCsvCouldNotBeParsed,
	DownloadFailedAndBackupLoaded,
	DownloadSucceededAndBackupSaved,
	DownloadSucceededAndBackupCouldNotBeSaved
};

// A class that contains authentication token information
UCLASS()
class RUNTIMEDATATABLE_API URuntimeDataTableWebToken : public UObject
{
public:

	GENERATED_BODY()

	/* Initialize the token with the appropriate information */
	UFUNCTION()
	bool Init(const FString InTokenText, const int32 SecondsUntilExpiration = 30);

	/**
	 * Returns true if the specified number of seconds until expiration have passed since authentication.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable", meta = (Keywords = "age, time"))
		bool HasTokenExpired() const;

	/**
	 * Returns the number of seconds remaining until this token's authorization expiration.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable", meta = (Keywords = "age, time"))
		int32 GetNumberOfSecondsUntilExpiration() const;

	/* Get the token string needed to pass into REST requests. */
	UFUNCTION()
	FString GetTokenText() const;

private:

	FString TokenText;
	FDateTime TimeOfExpiration;

	bool bIsInitialized;
};

UCLASS()
class RUNTIMEDATATABLE_API URuntimeDataTableObject : public UObject
{
	GENERATED_BODY()

public:

	URuntimeDataTableObject() {}

	// This is a struct from easyCSV that contains information about the loaded CSV. Use this when using Google Sheets.
	UPROPERTY(BlueprintReadWrite, Category = "Runtime DataTable")	
	FEasyCsvInfo CachedCsvInfo;

	/**
	 * Generate an FGoogleSheetsTokenInfo struct from a string. This is the same data found in the json key file downloaded from your Google Service Account.
	 * If you prefer to just load the file, call GenerateTokenInfoFromFile instead.
	 * This function is for users who wish to not keep the private key in an accessible file. Alternatively, you can use a Make node.
	 * @param OutTokenInfo A FGoogleSheetsTokenInfo struct used to create and authenticate a URuntimeDataTableWebToken.
	 * @param InJsonString The contents of a private key file
	 * @param DesiredSecondsUntilExpiration How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour). Generally it's best practice to keep the expiration short and generate a new token for each operation.
	 * @return Returns true if the file could be loaded, parsed, and had the required information to create a token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable|Token")
		static bool GenerateTokenInfoFromString(
			FRuntimeDataTableTokenInfo& OutTokenInfo, const FString InJsonString, const int32 DesiredSecondsUntilExpiration = 60);

	/**
	 * Generate an FGoogleSheetsTokenInfo struct from a file.
	 * If you have a json key file downloaded from your Google Service Account, you can create this struct by loading the file instead of copying the data into a Make node.
	 * If you wish not to keep the file accessible on disk, call GenerateTokenInfoFromString() instead.
	 * @param OutTokenInfo A FGoogleSheetsTokenInfo struct used to create and authenticate a URuntimeDataTableWebToken.
	 * @param InPathToFile Where on disk the key file resides.
	 * @param DesiredSecondsUntilExpiration How long should this token last? Min is 1 second, Max is 3600 seconds (1 hour). Generally it's best practice to keep the expiration short and generate a new token for each operation.
	 * @return Returns true if the file could be loaded, parsed, and had the required information to create a token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable|Token")
		static bool GenerateTokenInfoFromFile(
			FRuntimeDataTableTokenInfo& OutTokenInfo, const FString InPathToFile, const int32 DesiredSecondsUntilExpiration = 60);

	/**
	 * Returns the Sheet ID from a Google Sheet URL. This identifies a spreadsheet asset.
	 */
	UFUNCTION(BlueprintPure, Category = "Runtime DataTable|Google Sheets", meta=(Keywords="key"))
	static FString GetSpreadsheetIdFromUrl(const FString SheetURL);

	/**
	 * Returns the GID from a Google Sheet URL. The GID identifies a specific sheet or tab. Returns empty if the gid is not present.
	 */
	UFUNCTION(BlueprintPure, Category = "Runtime DataTable|Google Sheets", meta=(Keywords="gid, key"))
	static FString GetSheetIdFromUrl(const FString SheetURL);

	/**
	 * Returns the GID from a Google Sheet URL. The GID identifies a specific sheet or tab. Returns empty if the gid is not present.
	 */
	UFUNCTION(BlueprintPure, Category = "Runtime DataTable|Google Sheets", meta=(Keywords="gid, key"))
	static int32 GetSheetIdFromUrl_Int(const FString SheetURL);

	// docs.google.com/spreadsheets/d/
	UFUNCTION()
	static FString GetGoogleSheetsUrlPrefix();

	UFUNCTION()
	static FString GetMimeCsv();

	// sheets.googleapis.com/v4/spreadsheets/
	UFUNCTION()
	static FString GetGoogleSheetsApiUrlPrefix();

	// sheets.googleapis.com/v4/spreadsheets/{spreadsheetId}/values:batchUpdate
	UFUNCTION()
	static FString GetGoogleSheetsValuesBatchUpdateURL(const FString InSpreadsheetId);

	// sheets.googleapis.com/v4/spreadsheets/{spreadsheetId}:batchUpdate
	UFUNCTION()
	static FString GetGoogleSheetsBatchUpdateURL(const FString InSpreadsheetId);

	/**
	 * If you want to have row keys generated for you on export, insert the return value from this function into the export function's "Keys" parameter. You can also use "Make Array" with blank entries in blueprint or create a new TArray<FName> (or simply "{}") in C++ if you prefer.
	 * @return This is a blank array of FName. This signifies to the function that we should generate row keys on export. 
	 */
	UFUNCTION(BlueprintPure, Category = "Runtime DataTable")
	static TArray<FName> AutoGenerateKeys()
	{
		TArray<FName> BlankKeys;
		return BlankKeys;
	}

	// Google Sheets

	// Import

	/**
	 * Get any full sheet as CSV. This works for public or private sheets, provided you are authenticated. Set bSheetIsPublic to true if your sheet is public.
	 * @param InTokenInfo A validated URuntimeDataTableWebToken object. Used to authenticate the Sheets operation. Can be default if the sheet is public.
	 * @param OperationParams Generic request operation parameters
	 * @param InSheetURL The URL at which this sheet can be found.
	 * @param CallOnComplete This delegate will be called when the operation completes and tell you whether or not it was successful and return the response as a string.
     * @param bSheetIsPublic Set this parameter to true if your sheet does not require authentication because it is public and you have not provided a valid InTokenInfo. This avoids token validation.
	*/
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable")
		static void BuildGoogleSheetDownloadLinkAndGetAsCsv(
			const FRuntimeDataTableTokenInfo InTokenInfo, const FRuntimeDataTableOperationParams OperationParams, 
			const FRDTGetStringDelegate CallOnComplete, const FString InSheetURL, const bool bSheetIsPublic = false)
	{
		if (URuntimeDataTableObject* RuntimeDataTableObject = CreateRuntimeDataTableObject())
		{
			RuntimeDataTableObject->BuildGoogleSheetDownloadLinkAndGetAsCsv_Internal(
				InTokenInfo, OperationParams, CallOnComplete, InSheetURL, bSheetIsPublic);
		}
	}
	
	/**
	 * Determines if your CSV download was successful and tries to save the download to BackupSavePath if provided.
	 * If the download failed, will attempt to load the CSV from a local backup.
	 * If a CSV exists after that, will attempt to create and output FEasyCsvInfo from it.
	 * @return Whether FEasyCsvInfo could be parsed or not, regardless of whether it came from Google Sheets or a backup.
	 * @param InCallbackInfo A struct generated after calling BuildGoogleSheetDownloadLinkAndGetAsCsv. Contains information about the response from Google.
	 * @param OutCsvInfo If the download succeeded or the backup was loaded, this is the output FEasyCsvInfo.
	 * @param OutResultCode A result code describing the action or error resulting from this function.
	 * @param BackupSavePath Optional: If you have downloaded a sheet, you may save the sheet to a local path on disk.
	 * @param BackupLoadPath Optional: If no "InSheetURL" is specified or the sheet could not be downloaded for any reason, will attempt to load the CSV from the local disk at the specified path instead.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable")
		static bool ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded(
			const FRuntimeDataTableCallbackInfo InCallbackInfo,
			FEasyCsvInfo& OutCsvInfo, ERuntimeDataTableBackupResultCode& OutResultCode,
			const FString& BackupSavePath = "", const FString& BackupLoadPath = "");
	
	// Export

	/**
	 * Get any full sheet as CSV. This works for public or private sheets, provided you are authenticated.
	 * @param InTokenInfo A validated URuntimeDataTableWebToken object. Used to authenticate the Sheets operation. When writing to a sheet, you must provide a valid InTokenInfo even if the sheet is public.
	 * @param OperationParams Generic request operation parameters
	 * @param InSpreadsheetId This is the spreadsheet ID number or key. Get it from your spreadsheet URL by calling GetSpreadsheetIdFromUrl.
	 * @param InSheetId The GID for the desired sheet tab
	 * @param InCsv This is the Csv data represented as a string. To load a CSV document from a file, use LoadStringFromFile(). To generate a CSV from a struct/object array, use GenerateCsvFromArray (BP) or GenerateCsvFromArray_Internal (C++)
	 * @param CallOnComplete This delegate will be called when the operation completes and tell you whether or not it was successful and return the response as a string.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable")
	static void WriteCsvToSheet(
		FRuntimeDataTableTokenInfo InTokenInfo, const FRuntimeDataTableOperationParams OperationParams,
		const FRDTGetStringDelegate& CallOnComplete, const FString InSpreadsheetId, const int32 InSheetId,
		const FString InCsv)
	{
		if (URuntimeDataTableObject* RuntimeDataTableObject = CreateRuntimeDataTableObject())
		{
			RuntimeDataTableObject->WriteCsvToSheet_Internal(
				InTokenInfo, OperationParams, CallOnComplete, InSpreadsheetId, InSheetId, InCsv);
		}
	}

	// Local CSV

	// Import
	
	/**
	 * Fills an array of structs/objects with matching variables using a CSV_Info struct from MakeCsvInfoFromString or MakeCsvInfoFromFile.
	 * A bool is also returned reflecting whether the array could be updated.
	 * C++ users should use UpdateArrayFromCsvInfo_Internal instead.
	 * @param ArrayToUpdate An array of the type of struct/object you'd like to update using values from the loaded CSV. Struct arrays will be emptied prior to filling, object arrays will be updated in-place.
	 * @param CSVInfo The script will attempt to update the array using this struct. You can generate the struct using MakeSCV_InfoFromString() or MakeCSV_InfoFromFile().
	 * @param MatchStructMemberNames When true will attempt to match column names in your CSV with variables inside of your struct. This makes it so you don't have to have all variables in your struct represented sequentially in your CSV file. Name matching is slower than sequential updates so when working with very large data sets updates could take sometime longer to complete. This parameter has no effect when using an array of objects as objects will always use name matching.
	 * @param OwningObject The object or instantiation of a class that has the struct array as one of its variables. Defaults to the calling object or 'Self' and only applies to struct arrays.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable", CustomThunk,
		meta = (AdvancedDisplay = "MatchStructMemberNames, OwningObject", ArrayParm = "ArrayToUpdate",
			DefaultToSelf = "OwningObject", KeyWords = "Fill"))
	static void UpdateArrayFromCsvInfo(
		const TArray<int32>& ArrayToUpdate, bool& Successful, FEasyCsvInfo CSVInfo, bool MatchStructMemberNames, const UObject* OwningObject);

	DECLARE_FUNCTION(execUpdateArrayFromCsvInfo)
	{
		Stack.MostRecentPropertyAddress = nullptr;
		Stack.MostRecentProperty = nullptr;

		//Array parameter
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* ArrayPtr = Stack.MostRecentPropertyAddress;
		if (!ArrayPtr)
		{
			return;
		}
		auto ArrayProperty = (FArrayProperty*)(Stack.MostRecentProperty);

		//Success parameter
		Stack.StepCompiledIn<FBoolProperty>(NULL);
		void* SuccessBoolPtr = Stack.MostRecentPropertyAddress;
		if (!SuccessBoolPtr)
		{
			return;
		}
		auto SuccessBoolProp = (FBoolProperty*)(Stack.MostRecentProperty);

		//CSV_Info parameter
		P_GET_STRUCT(FEasyCsvInfo, CSV_Info);

		P_GET_PROPERTY(FBoolProperty, MatchStructMemberNames);

		//Owning object parameter
		P_GET_PROPERTY(FObjectProperty, OwningObject);

		// We need this to wrap up the stack
		P_FINISH;

		bool Successful = UpdateArrayFromCsvInfo_Internal(
			ArrayProperty, ArrayPtr, OwningObject, CSV_Info, MatchStructMemberNames);

		SuccessBoolProp->SetPropertyValue(SuccessBoolPtr, Successful);
	}

	/**
	 * Fills an array of structs/objects with matching variables using a CSV_Info struct from MakeCSV_InfoFromString() or MakeCSV_InfoFromFile().
	 * A bool is also returned reflecting whether the array could be updated.
	 * @return A bool indicating whether the array could be updated
	 * @param ArrayProperty Grab this by using the FindFProperty Method e.g. FindFProperty<FArrayProperty>(OwningObject->GetClass(), FName("{Name of Array Property}"));
	 * @param ArrayPtr A ref to your Array, e.g. &TestStructArray
	 * @param OwningObject Object which owns the struct
	 * @param CsvInfo The script will attempt to fill the struct array using this struct. You can generate the struct using MakeCSV_InfoFromString() or MakeCSV_InfoFromFile().
	 * @param bNameMatch When true will attempt to match column names in your CSV with variables inside of your struct. This makes it so you don't have to have all variables in your struct represented sequentially in your CSV file. Name matching is slower than sequential updates so when working with very large data sets updates could take sometime longer to complete. This parameter has no effect when using an array of objects as objects will always use name matching.
	 */
	static bool UpdateArrayFromCsvInfo_Internal(
		FArrayProperty* ArrayProperty, void* ArrayPtr, UObject* OwningObject, FEasyCsvInfo CsvInfo, bool bNameMatch = false);

	// Export

	/**
	 * Attempts to build a CSV from an array of structs/objects. Takes a set of Keys for the first column of the CSV and an array of FNames to act as a variable whitelist. Note that if you use a whitelist for a struct array, you'll need to always use MatchStructMemberNames when importing data for that struct in the future.
	 * Does not return an RDT actor or call a delegate. Returns a boolean reflecting whether successfully able to write to disk.
	 * @param ArrayToExport An array of the structs or objects you'd like to export.
	 * @param OutCSV_String A string representing the array data in CSV form.
	 * @param Keys A set of keys used in the first column of the CSV to uniquely identify rows. Does not enforce unique values, so be sure to do that prior to calling. An array is required, but you don't need to match the number of keys to the number of structs. They will be auto-generated if not supplied in matching numbers. For all generated keys, use "AutoGenerateKeys()."
	 * @param MembersToInclude Optional: Names of variables in your structs or objects that you want to export. Separate names by comma. Leave blank to include all variables, but be careful when using objects. Leaving this blank will include EVERY variable name including inherited and engine variables. For help creating this whitelist for objects, see GetAllObjectVariableNames().
	 * @param bSortColumnsAlphanumerically If true, sort columns 0->9, A->Z
	 * @param OwningObject The object or instantiation of a class that has the struct array as one of its variables. Defaults to the calling object or 'Self' and only applies to struct arrays.
	 */
	UFUNCTION(BlueprintCallable, Category = "Runtime DataTable", CustomThunk,
		meta = (AdvancedDisplay = "OwningObject", ArrayParm = "ArrayToExport", DefaultToSelf = "OwningObject", Keywords="Export, String"))
		static void GenerateCsvFromArray(
			const TArray<int32>& ArrayToExport, FString& OutCSV_String, TArray<FName> Keys,
			FString MembersToInclude, const bool bSortColumnsAlphanumerically, const UObject* OwningObject
		);

	DECLARE_FUNCTION(execGenerateCsvFromArray)
	{
		Stack.MostRecentPropertyAddress = nullptr;
		Stack.MostRecentProperty = nullptr;

		//Structs parameter
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* ArrayPtr = Stack.MostRecentPropertyAddress;
		if (!ArrayPtr)
		{
			return;
		}
		auto ArrayProperty = (FArrayProperty*)(Stack.MostRecentProperty);

		//Output String parameter
		Stack.StepCompiledIn<FStrProperty>(NULL);
		void* OutStringPtr = Stack.MostRecentPropertyAddress;
		if (!OutStringPtr)
		{
			return;
		}
		auto OutStringProp = (FStrProperty*)(Stack.MostRecentProperty);

		//Keys parameter
		TArray<FString> RowKeys;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* KeysPtr = Stack.MostRecentPropertyAddress;
		if (!KeysPtr)
		{
			return;
		}
		auto KeysProperty = (FArrayProperty*)(Stack.MostRecentProperty);
		FScriptArrayHelper KeysHelper(KeysProperty, KeysPtr);
		for (int32 i = 0, n = KeysHelper.Num(); i < n; ++i)
		{
			FNameProperty* Prop = CastField<FNameProperty>(KeysProperty->Inner);
			FName Key = Prop->GetPropertyValue(KeysHelper.GetRawPtr(i));
			RowKeys.Add(Key.ToString());
		}

		P_GET_PROPERTY(FStrProperty, MembersToInclude);

		P_GET_PROPERTY(FBoolProperty, bSortColumnsAlphabetically);

		//Owning object parameter
		P_GET_PROPERTY(FObjectProperty, OwningObject);

		// We need this to wrap up the stack
		P_FINISH;

		FString FinalCSV = GenerateCsvFromArray_Internal(
			ArrayProperty, ArrayPtr, RowKeys, OwningObject, MembersToInclude, bSortColumnsAlphabetically);

		OutStringProp->SetPropertyValue(OutStringPtr, FinalCSV);
	}

	/**
	 * Internal call for array export. Returns an FString representing a CSV made from the array stuck into the BP node.
	 * @param ArrayProperty The containing property for the struct or UObject array. Grab this by using the FindFProperty Method e.g. FindFProperty<FArrayProperty>(OwningObject->GetClass(), FName("{Name of Struct Array Property}"));
	 * @param ArrayPtr The actual data for ArrayProperty, e.g. &TestStructArray
	 * @param RowKeys A set of keys used in the first column of the CSV to uniquely identify rows. Does not enforce unique values, so be sure to do that prior to calling. An array is required, but you don't need to match the number of keys to the number of structs. They will be auto-generated if not supplied in matching numbers. For all generated keys, use "AutoGenerateKeys()."
	 * @param OwningObject Object which owns the data. Ignored for an array of objects.
	 * @param MembersToInclude Optional: Names of variables in your structs or objects that you want to export. Separate names by comma. Leave blank to include all variables, but be careful when using objects. Leaving this blank will include EVERY variable name including inherited and engine variables. For help creating this whitelist for objects, see GetAllObjectVariableNames().
	 * @param bSortColumnsAlphanumerically If true, sort columns 0->9, A->Z
	 */
	static FString GenerateCsvFromArray_Internal(
		FArrayProperty* ArrayProperty, void* ArrayPtr, TArray<FString> RowKeys,
		UObject* OwningObject = nullptr, FString MembersToInclude = "", const bool bSortColumnsAlphanumerically = false
);

	/**
	 * Is the given property supported by the Unreal Engine DataTable module?
	 */
	static bool IsPropertyDataTableSupported(const FProperty* Property);
	
	/**
	 * Returns all of the variables, including components, attached to a given object. Excludes "UberGraphFrame" & "DefaultSceneRoot" by default.
	 * @param Object The object with the variables you want to list. Defaults to the calling object or 'Self'.
	 * @param bIncludeOnlyConfigVariables If true, only members marked as "Config" in blueprint or given the CPF_Config PropertyFlag in C++ will be included, assuming they are not blacklisted. If none are marked as Config, no variables will be included.
	 * @param bIncludeInheritedVariables If true will include all variables from parent classes as well. Keep in mind this means the Super classes too, so you may end up with a lot of variables you don't want. You'll need to filter these out yourself. Try overloading a method from the desired base class all the way down.
	 * @param MemberBlacklist A comma-separated list of members you do NOT want to return. Useful for filtering out members that don't matter to you. Ex: "ActorScale, ActorColor, ActorRotation"
	 */
	UFUNCTION(BlueprintPure, Category = "Runtime DataTable", meta = (DefaultToSelf = "Object", AdvancedDisplay = "IncludeInheritedVariables, MemberBlacklist"))
	static FString GetAllObjectVariableNames(
		const UObject* Object, 
		const bool bIncludeOnlyConfigVariables = false, const bool bIncludeInheritedVariables = false,
		FString MemberBlacklist = "UberGraphFrame, DefaultSceneRoot");

protected:

	static URuntimeDataTableObject* CreateRuntimeDataTableObject()
	{
		URuntimeDataTableObject* RuntimeDataTableObject = NewObject<URuntimeDataTableObject>();
		return RuntimeDataTableObject;
	}

	static void CreateAndAuthenticateToken(FRuntimeDataTableTokenInfo InTokenInfo, const FRDTGetJWTDelegate& CallOnComplete)
	{
		if (URuntimeDataTableObject* RuntimeDataTableObject = CreateRuntimeDataTableObject())
		{
			RuntimeDataTableObject->CreateAndAuthenticateToken_Internal(InTokenInfo, CallOnComplete);
		}
	}

	/**
	 * Takes in a single property (not an array, not a whole struct or object but one by one) and CSV cell data (as FString) then populates the values with the strings, converting them as necessary to the correct data types.
	 * @param InnerProperty Single FProperty from a struct or UObject, like "IntValue" or something like that. Grab this by using the FindFProperty Method e.g. FindFProperty<FProperty>(OwningObject->GetClass(), FName("{Name of Property}"));
	 * @param ContainerPtr A ref to your FStruct or UObject, not the whole array but a single item from a single row. Also not a ref to the single property, e.g. &ContainerPtr
	 * @param ValueAsString: Information from the CSV cell as a string
	 * @param OwningObject: Object which owns the data
	 * @param IsUObject: Whether the container of the data is a struct or a UObject
	 */
	static void IterateThroughPropertyAndUpdateFromString(
		const FProperty* InnerProperty, void* ContainerPtr, const FString ValueAsString, UObject* OwningObject, bool IsUObject);

	/**
	 * Takes a struct property (not array, one by one) and converts each field to string. Then returns the entire struct as a stringified row to put in a CSV. UObjects can be casted to FStructProperty.
	 * @param StructProperty Grab this by using the FindFProperty Method e.g. FindFProperty<FArrayProperty>(OwningObject->GetClass(), FName("{Name of Struct Array Property}"));
	 * @param StructPtr A ref to your Struct Array, e.g. &TestStructArray
	 * @param RowKey The row identifier. It can be anything you want, just make it unique. No two rows should have the same identifier, but this script does not enforce unique values.
	 * @param OwningObject Object which owns the data
	 * @param bIsUObject: Whether the container of the data is a struct or a UObject
	 * @param bSortColumnsAlphanumerically If true, sort columns 0->9, A->Z
	 * @param OutNumValues Out: How many members are in the struct/object?
	 * @param OutTopRow Out: What are the headers?
	 * @param OutRowString Out: Row As String
	 * @param InMemberWhitelist Names of variables in your structs or objects that you want to include in the output string. 
	*/
	static void IterateThroughStructPropertyAndMakeRowString(
		const FStructProperty* StructProperty, void* StructPtr, const FString& RowKey, UObject* OwningObject, const bool bIsUObject,
		const bool bSortColumnsAlphanumerically,
		uint8& OutNumValues, FString& OutTopRow, FString& OutRowString, const TArray<FString>& InMemberWhitelist);

	// Do not call
	void BuildGoogleSheetDownloadLinkAndGetAsCsv_Internal(
			FRuntimeDataTableTokenInfo InTokenInfo, const FRuntimeDataTableOperationParams OperationParams, 
			const FRDTGetStringDelegate& CallOnComplete, const FString& InSheetURL, const bool bSheetIsPublic = false);

	// Do not call
	void BuildGoogleSheetDownloadLinkAndGetAsCsv_AfterToken(
		const FRuntimeDataTableCallbackInfo CallbackInfo, URuntimeDataTableWebToken* InToken,
		const FRuntimeDataTableOperationParams OperationParams, const FRDTGetStringDelegate CallOnComplete, const FString InSheetURL);

	// Do not call
	void WriteCsvToSheet_Internal(
		FRuntimeDataTableTokenInfo InTokenInfo, const FRuntimeDataTableOperationParams OperationParams,
		const FRDTGetStringDelegate& CallOnComplete, const FString& InSpreadsheetId, const int32 InSheetId,
		const FString& InCsv);
	// Do not call
	void WriteCsvToSheet_AfterToken(
		const FRuntimeDataTableCallbackInfo CallbackInfo, URuntimeDataTableWebToken* InToken,
		const FRuntimeDataTableOperationParams OperationParams, FRDTGetStringDelegate CallOnComplete,
		const FString InSpreadsheetId, const int32 InSheetId, const FString InCsv);
	// Do not call
	void WriteCsvToSheet_Internal_CompareColumnCounts(
		FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful,
		URuntimeDataTableWebToken* InToken, const FRuntimeDataTableOperationParams OperationParams,
		FRDTGetStringDelegate CallOnComplete,
		FString InSpreadsheetId, const int32 InSheetId, FString InCsv,
		FCsvToGoogleSheetsHandler SheetTabData);
	// Do not call
	void WriteCsvToSheet_Internal_ClearSheet(
		FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful,
		URuntimeDataTableWebToken* InToken, const FRuntimeDataTableOperationParams OperationParams,
		FRDTGetStringDelegate CallOnComplete,
		FString InSpreadsheetId, const int32 InSheetId, FString InCsv,
		FCsvToGoogleSheetsHandler SheetTabData);
	// Do not call
	void WriteCsvToSheet_Internal_SendCsvDataToSheet(
		FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful,
		URuntimeDataTableWebToken* InToken, const FRuntimeDataTableOperationParams OperationParams,
		FRDTGetStringDelegate CallOnComplete,
		FString InSpreadsheetId, const int32 InSheetId, FString InCsv,
		FCsvToGoogleSheetsHandler SheetTabData);

	/**
	 * Creates a download link for a Google Sheet from an edit/share link.
	 * Sheet Must be visible to or editable by anyone with the link.
	 */
	void DownloadPublicSheet(
		FString SheetURL, FRDTGetStringDelegate CallOnComplete, const FRuntimeDataTableOperationParams OperationParams);

	// Sends the actual request to Google for the Sheet download
	// Do not call
	void Request_GET_PublicSheetAsCSV(
		FString RequestURL, const FRDTGetStringDelegate& CallOnComplete, const FRuntimeDataTableOperationParams OperationParams);

	// Called when a response is received or the timeout threshold is reached. Handles what we do with the response.
	// Do not call
	void OnResponseReceived_GET_SheetAsCSV(
		FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful,
		FRDTGetStringDelegate CallOnComplete, const FRuntimeDataTableOperationParams OperationParams);
	
	// Do not call
	void OnResponseReceivedGenericReturnString(
		FHttpRequestPtr Request, FHttpResponsePtr Response,
		bool bWasSuccessful, FRuntimeDataTableOperationParams OperationParams,
		FRDTGetStringDelegate CallOnComplete);

	// Do not call
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateAuthorizedGenericRequest_Internal(
		const FString InTokenText, const FRuntimeDataTableOperationParams OperationParams,
		const FString InVerb, const FString InURL,
		const bool bShouldProcessRequest = true, const FString ContentType = GetMimeCsv());
	
	// Do not call
	void CreateAndAuthenticateToken_Internal(FRuntimeDataTableTokenInfo InTokenInfo, const FRDTGetJWTDelegate& CallOnComplete);
	
	// Do not call
	void Request_POST_ForToken(
		const FString InJavaWebToken, const FRDTGetJWTDelegate& CallOnComplete, const FRuntimeDataTableTokenInfo InTokenInfo);
	
	// Do not call
	void OnResponseReceivedReturnToken(
		FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FRuntimeDataTableTokenInfo InTokenInfo, FRDTGetJWTDelegate CallOnComplete);
	
	void GenericValidateHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, FRuntimeDataTableCallbackInfo& CallbackInfo);
	
	static FString CreateJavaWebToken(FRuntimeDataTableTokenInfo InTokenInfo);
	static bool ValidateTokenInfo(FRuntimeDataTableTokenInfo& InTokenInfo, FString& ErrorMessage);

	static FName GetTokenOperationName;
};
