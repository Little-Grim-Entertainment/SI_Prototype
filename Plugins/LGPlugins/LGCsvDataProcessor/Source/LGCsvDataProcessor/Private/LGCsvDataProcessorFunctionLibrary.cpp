// Fill out your copyright notice in the Description page of Project Settings.


#include "LGCsvDataProcessorFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RuntimeDataTable.h"

void ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(const FString& InURL, const FString& InFilePath, const FString& InFileName)
{
	if(InURL.IsEmpty()){return;}
	
	FRuntimeDataTableTokenInfo TokenInfo;
	FRuntimeDataTableOperationParams RuntimeDataTableOperationParams;
	RuntimeDataTableOperationParams.OperationName = FName(TEXT("CsvUpdate"));
	RuntimeDataTableOperationParams.FilePath = InFilePath;
	RuntimeDataTableOperationParams.CvsName = InFileName;
	
	FRDTGetStringDelegate CallbackDelegate;
	CallbackDelegate.BindUFunction(StaticClass(), GET_FUNCTION_NAME_CHECKED(ULGCsvDataProcessorFunctionLibrary, OnSheetStructsDownloaded));
	
	URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv(TokenInfo, RuntimeDataTableOperationParams, CallbackDelegate, InURL, true);
}



void ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo)
{
	FEasyCsvInfo EasyCsvInfo;
	ERuntimeDataTableBackupResultCode RuntimeDataTableBackupResultCode;
	FString ProjectSavePath = UKismetSystemLibrary::GetProjectSavedDirectory();

	if(!URuntimeDataTableObject::ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded(InCallbackInfo, EasyCsvInfo, RuntimeDataTableBackupResultCode, ProjectSavePath, ProjectSavePath))
	{
		UE_LOG(LogCsvDataProcessor, Warning, TEXT("Google Sheet Validation Failed"));
		return;
	}

	FLGCsvInfo CSVInfo;
	CSVInfo.CSVToWrite = InCallbackInfo.ResponseAsString;
	CSVInfo.CSVInfoResults = EasyCsvInfo;
	FNameArrayToFStringArray(EasyCsvInfo.CSV_Keys, CSVInfo.ExportKeys);

	UStruct* CSVInfoStruct = CSVInfo.StaticStruct();
	if(!CSVInfoStruct){UE_LOG(LogCsvDataProcessor, Warning, TEXT("Failed to convert CSVInfo into StaticStruct.")); return;}
	
	FArrayProperty* CsvStringsArrayProperty = FindFProperty<FArrayProperty>(CSVInfoStruct, FName("CsvStrings"));
	if(!CsvStringsArrayProperty){UE_LOG(LogCsvDataProcessor, Warning, TEXT("Failed to find CsvStringsArrayProperty.")); return;}

	if(!URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(CsvStringsArrayProperty, &CSVInfo.CsvStrings, this, CSVInfo.CSVInfoResults, true)){UE_LOG(LogDemo, Warning, TEXT("UpdateArrayFromCsvInfo_Internal failed.")); return;}

	FString CSVString = URuntimeDataTableObject::GenerateCsvFromArray_Internal(CsvStringsArrayProperty, &CSVInfo.CsvStrings, CSVInfo.ExportKeys, this);
	
	if(!UEasyCsv::SaveStringToFile(CSVString,ProjectSavePath, InCallbackInfo.CvsName)){UE_LOG(LogDemo, Warning, TEXT("SaveStringToFile failed.")); return;}

	FEasyCsvInfo CsvInfoResults;
	if(!UEasyCsv::MakeCsvInfoStructFromFile(InCallbackInfo.FilePath, CsvInfoResults)){UE_LOG(LogDemo, Warning, TEXT("MakeCsvInfoStructFromFile failed.")); return;}

	URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(CsvStringsArrayProperty, &CSVInfo.CsvStrings, this, CsvInfoResults, true);
}

void ULGCsvDataProcessorFunctionLibrary::FNameArrayToFStringArray(const TArray<FName>& InNameArray, TArray<FString>& OutStringArray)
{
	for (const FName& CurrentName : InNameArray)
	{
		FString CurrentString = CurrentName.ToString();
		OutStringArray.Add(CurrentString);
	}
}


