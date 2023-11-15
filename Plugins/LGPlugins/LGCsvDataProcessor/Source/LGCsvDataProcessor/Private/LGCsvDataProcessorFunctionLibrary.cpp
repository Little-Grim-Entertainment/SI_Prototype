// Fill out your copyright notice in the Description page of Project Settings.

#include "LGCsvDataProcessorFunctionLibrary.h"

#include "EasyCsv.h"
#include "Interfaces/LGCsvProcessorInterface.h"
#include "Kismet/KismetSystemLibrary.h"


void ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(const FLGCsvInfoImportPayload& InImportPayload)
{
	if(InImportPayload.URL.IsEmpty()){return;}
	
	FRuntimeDataTableTokenInfo TokenInfo;
	FRuntimeDataTableOperationParams RuntimeDataTableOperationParams;
	RuntimeDataTableOperationParams.OperationName = FName(TEXT("CsvUpdate"));
	RuntimeDataTableOperationParams.FilePath = InImportPayload.FilePath;
	RuntimeDataTableOperationParams.CvsName = InImportPayload.FileName;
	RuntimeDataTableOperationParams.Caller = InImportPayload.Caller;
	
	FRDTGetStringDelegate CallbackDelegate;
	CallbackDelegate.BindUFunction(StaticClass(), GET_FUNCTION_NAME_CHECKED(ULGCsvDataProcessorFunctionLibrary, OnSheetStructsDownloaded));
	
	URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv(TokenInfo, RuntimeDataTableOperationParams, CallbackDelegate, InImportPayload.URL, true);
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

	CSVInfo.CSVInfoResults = CsvInfoResults;

	if(URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(CsvStringsArrayProperty, &CSVInfo.CsvStrings, this, CSVInfo.CSVInfoResults, true))
	{
		if (!IsValid(InCallbackInfo.Caller) || !InCallbackInfo.Caller->Implements<ULGCsvProcessorInterface>()) {return;}
		
		if (const ILGCsvProcessorInterface* DialogueProcessorObject = Cast<ILGCsvProcessorInterface>(InCallbackInfo.Caller))
		{
			DialogueProcessorObject->Execute_OnInteractComplete(InCallbackInfo.Caller, InCallbackInfo.Caller, CSVInfo);
		}
	}
}

void ULGCsvDataProcessorFunctionLibrary::FNameArrayToFStringArray(const TArray<FName>& InNameArray, TArray<FString>& OutStringArray)
{
	for (const FName& CurrentName : InNameArray)
	{
		FString CurrentString = CurrentName.ToString();
		OutStringArray.Add(CurrentString);
	}
}


