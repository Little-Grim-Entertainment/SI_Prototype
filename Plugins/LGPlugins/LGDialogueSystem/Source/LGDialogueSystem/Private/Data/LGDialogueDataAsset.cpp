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

void ULGDialogueDataAsset::OnCsvProcessComplete_Implementation(const FLGCsvInfo& InCvsInfo)
{
	UE_LOG(LogLGDialogue, Warning, TEXT("Dilogue Asset Interaction Complete!"));
}

UStruct* ULGDialogueDataAsset::GetUStructContainerByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueStructID)
{
	return nullptr;
}

void* ULGDialogueDataAsset::GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueID)
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

void ULGDialogueDataAsset::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo)
{
	const FGameplayTag& CsvArrayType = InCallbackInfo.CsvArrayTypeTag;
	const FName& PropertyName = GetStructPropertyNameByTag(CsvArrayType);
	void* DialogueStructArray = GetDialogueStructArrayByTag(CsvArrayType, InCallbackInfo.DialogueStructID);
	
	ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(InCallbackInfo, DialogueStructArray, GetUStructContainerByTag(CsvArrayType, InCallbackInfo.DialogueStructID), PropertyName);
}

void ULGDialogueDataAsset::OnPayLoadReadyForImport(const FLGCsvInfoImportPayload& InImportPayload)
{
	FRDTGetStringDelegate CallbackDelegate;
	CallbackDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ULGDialogueDataAsset, OnSheetStructsDownloaded));
		
	ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(InImportPayload, CallbackDelegate);
}
