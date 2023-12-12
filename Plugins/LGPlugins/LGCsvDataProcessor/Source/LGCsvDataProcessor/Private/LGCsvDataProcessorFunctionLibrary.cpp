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
	
	if(!InCallbackDelegate.IsBound()) {UE_LOG(LogCsvDataProcessor, Warning, TEXT("Delegate is not bound."));}
	
	URuntimeDataTableObject::BuildGoogleSheetDownloadLinkAndGetAsCsv(TokenInfo, RuntimeDataTableOperationParams, InCallbackDelegate, InImportPayload.URL, true);
}

void ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo, void* InArrayPtr, UStruct* InStructPtr, const FName& InPropertyName)
{
	FEasyCsvInfo EasyCsvInfo;
	ERuntimeDataTableBackupResultCode RuntimeDataTableBackupResultCode;
	FString ProjectSavePath = InCallbackInfo.FilePath;
	ProjectSavePath.Append(InCallbackInfo.FolderName);
	ProjectSavePath.Append("/");
	ProjectSavePath.Append(InCallbackInfo.FileName);
	ProjectSavePath.Append(".csv");

	if(!URuntimeDataTableObject::ValidateGoogleSheetsDownloadAndLoadBackupIfNeeded(InCallbackInfo, EasyCsvInfo, RuntimeDataTableBackupResultCode, ProjectSavePath, ProjectSavePath))
	{
		UE_LOG(LogCsvDataProcessor, Warning, TEXT("Google Sheet Validation Failed"));
		return;
	}

	FLGCsvInfo CSVInfo;
	CSVInfo.CSVToWrite = InCallbackInfo.ResponseAsString;
	CSVInfo.CSVInfoResults = EasyCsvInfo;
	ULGBlueprintFunctionLibrary::FNameArrayToFStringArray(EasyCsvInfo.CSV_Keys, CSVInfo.ExportKeys);

	if(!IsValid(InStructPtr)){UE_LOG(LogCsvDataProcessor, Error, TEXT("Failed to convert CSVInfo into StaticStruct.")); return;}
	
	FArrayProperty* CsvStringsArrayProperty = FindFProperty<FArrayProperty>(InStructPtr, InPropertyName);
	if(!CsvStringsArrayProperty){UE_LOG(LogCsvDataProcessor, Error, TEXT("Failed to find CsvStringsArrayProperty.")); return;}

	if(!URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(CsvStringsArrayProperty, InArrayPtr, InCallbackInfo.Caller, CSVInfo.CSVInfoResults, true)){UE_LOG(LogDemo, Warning, TEXT("UpdateArrayFromCsvInfo_Internal failed.")); return;}

	FString CSVString = URuntimeDataTableObject::GenerateCsvFromArray_Internal(CsvStringsArrayProperty, InArrayPtr, CSVInfo.ExportKeys, InCallbackInfo.Caller);
	
	if(!UEasyCsv::SaveStringToFile(CSVString,ProjectSavePath, InCallbackInfo.FileName)){UE_LOG(LogDemo, Warning, TEXT("SaveStringToFile failed.")); return;}

	FString CsvFilePath = ProjectSavePath + "/" + InCallbackInfo.FileName + ".csv";

	FEasyCsvInfo CsvInfoResults;
	if(!UEasyCsv::MakeCsvInfoStructFromFile(CsvFilePath, CsvInfoResults)){UE_LOG(LogDemo, Error, TEXT("MakeCsvInfoStructFromFile failed.")); return;}

	CSVInfo.CSVInfoResults = CsvInfoResults;

	if(URuntimeDataTableObject::UpdateArrayFromCsvInfo_Internal(CsvStringsArrayProperty, InArrayPtr, InCallbackInfo.Caller, CSVInfo.CSVInfoResults, true))
	{
		if (!IsValid(InCallbackInfo.Caller) || !InCallbackInfo.Caller->Implements<ULGCsvProcessorInterface>()) {return;}
		
		if (const ILGCsvProcessorInterface* DialogueProcessorObject = Cast<ILGCsvProcessorInterface>(InCallbackInfo.Caller))
		{
			DialogueProcessorObject->Execute_OnInteractComplete(InCallbackInfo.Caller, InCallbackInfo.Caller, CSVInfo);
		}
	}
}


