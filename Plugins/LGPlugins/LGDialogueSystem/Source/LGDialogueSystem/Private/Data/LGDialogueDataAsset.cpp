// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LGDialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"

void ULGDialogueDataAsset::UpdateDialogue()
{
	UpdateDialogue_Internal();
}

void ULGDialogueDataAsset::UpdateDialogue_Internal()
{
}

void ULGDialogueDataAsset::OnCsvProcessComplete_Implementation(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr)
{
	UpdateDataTable(InCallbackInfo, InStructPtr);
	UE_LOG(LogLGDialogue, Warning, TEXT("Dilogue Asset Interaction Complete!"));
}

UScriptStruct* ULGDialogueDataAsset::GetStructContainerByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	return nullptr;
}

UScriptStruct* ULGDialogueDataAsset::GetStructTypeByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	return nullptr;
}

void* ULGDialogueDataAsset::GetDialogueStructArrayByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	return nullptr;
}

FName ULGDialogueDataAsset::GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag)
{
	return FName("NONE");
}

FName ULGDialogueDataAsset::GetStructTypeNameByTag(const FGameplayTag& InGameplayTag)
{
	return FName("NONE");
}

void ULGDialogueDataAsset::UpdateDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr)
{
	UE_LOG(LogLGDialogue, Warning, TEXT("Unable to generate new %s type data table."), *GetStructTypeNameByTag(InCallbackInfo.CsvArrayTypeTag).ToString());
}

void ULGDialogueDataAsset::InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	
}

UDataTable* ULGDialogueDataAsset::GenerateNewDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	return nullptr;
}

void ULGDialogueDataAsset::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo)
{
	FGuid& DialogueDataGuidPtr = InCallbackInfo.DialogueStructID;
	FGuid& DialogueArrayGuidPtr = InCallbackInfo.DialogueArrayID;
	
	const FGameplayTag& CsvArrayType = InCallbackInfo.CsvArrayTypeTag;
	const FName& PropertyName = GetStructPropertyNameByTag(CsvArrayType);
	void* DialogueStructArray = GetDialogueStructArrayByIDs(DialogueDataGuidPtr, DialogueArrayGuidPtr);
	
	ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(InCallbackInfo, DialogueStructArray, GetStructContainerByIDs(DialogueDataGuidPtr, DialogueArrayGuidPtr), PropertyName);
}

void ULGDialogueDataAsset::OnPayLoadReadyForImport(const FLGCsvInfoImportPayload& InImportPayload)
{
	FRDTGetStringDelegate CallbackDelegate;
	CallbackDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ULGDialogueDataAsset, OnSheetStructsDownloaded));
		
	ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(InImportPayload, CallbackDelegate);
}
