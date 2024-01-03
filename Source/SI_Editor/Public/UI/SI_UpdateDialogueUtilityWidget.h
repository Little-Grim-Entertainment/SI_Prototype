// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_EditorUtilityWidget.h"
#include "SI_CsvDataTypes.h"
#include "RuntimeDataTable.h"
#include "Cases/Data/SI_CaseData.h"
#include "SI_UpdateDialogueUtilityWidget.generated.h"

UCLASS()
class SI_EDITOR_API USI_UpdateDialogueUtilityWidget : public USI_EditorUtilityWidget
{
	GENERATED_BODY()

public:

	template<class StructType>
	StructType* GetDialogueArrayStructByCaseAndLabel(const FGameplayTag& InCaseTag, const FString& InDialogueLabel);
	
protected:
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void UpdateDialogue();

private:

	void UpdateDefaultDialogue();
	void UpdateBubbleDialogue();
	void UpdateCaseDialogue();

	TArray<FLGDialogueArrayData*> DialogueArrayData;
	
protected:
	
	void OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath, const FString& InFileName, FGuid& InDialogueDataID, FGuid& InDialogueArrayID);
	bool StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType); 

	void UpdateDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr);
	void UpdateDataTableRows(UDataTable* InDataTable, FRuntimeDataTableCallbackInfo& InCallbackInfo);
	void InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	
	UScriptStruct* GetStructContainerByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	UScriptStruct* GetStructTypeByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);

	void* GetDialogueStructArrayByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag);
	FName GetStructTypeNameByTag(const FGameplayTag& InGameplayTag);
	FLGDialogueArrayData* GetDialogueDataByID(const FGuid& InDialogueDataID);
	FLGDialogueArray* GetDialogueArrayStructByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	UDataTable* GenerateNewDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo);
	void BeginCsvImport(const FString& InFilePath, const FString& InUrl, const FGameplayTag& InStructType, const FString& InFileName);
	void OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo);


	template <class StructPtr, class ArrayPtr>
	TArray<ArrayPtr>* GetDialogueArrayFromStruct(FLGDialogueArray* InArrayPtr);

	template <class StructPtr, class ArrayPtr>
	void UpdateDataTableStructByType(UDataTable* InDataTable, FLGDialogueArray* InArrayPtr);
};

template <class StructPtr, class ArrayPtr>
TArray<ArrayPtr>* USI_UpdateDialogueUtilityWidget::GetDialogueArrayFromStruct(FLGDialogueArray* InArrayPtr)
{
	StructPtr* DialogueArrayPtr = static_cast<StructPtr*>(InArrayPtr);
	if(DialogueArrayPtr)
	{
		TArray<ArrayPtr>* DialogueArray = DialogueArrayPtr->GetDialogueArray();
		return DialogueArray;
	}
	return nullptr;
}

template <class StructType, class ArrayType>
void USI_UpdateDialogueUtilityWidget::UpdateDataTableStructByType(UDataTable* InDataTable, FLGDialogueArray* InArrayPtr)
{
	TArray<StructType*> DialoguePtrs;
	InDataTable->GetAllRows(TEXT(""),DialoguePtrs);

	ArrayType* ArrayPtr = static_cast<ArrayType*>(InArrayPtr);
	if(!ArrayPtr) {return;}

	ArrayPtr->UpdateDataTableStructValues(DialoguePtrs);
	InDataTable->MarkPackageDirty();
}

template <class StructType>
StructType* USI_UpdateDialogueUtilityWidget::GetDialogueArrayStructByCaseAndLabel(const FGameplayTag& InCaseTag, const FString& InDialogueLabel)
{
	for(FSI_CaseDialogueData& CurrentCaseDialogueData : CaseDialogue)
	{
		if(!IsValid(CurrentCaseDialogueData.CaseReference) || CurrentCaseDialogueData.CaseReference->CaseTag != InCaseTag) {continue;}

		for(FSI_PartDialogueData& CurrentPartDialogueData : CurrentCaseDialogueData.PartDialogue)
		{
			for (FLGDialogueArray& CurrentDialogueArray : CurrentPartDialogueData.DialogueData.DialogueArrays)
			{
				StructType* StructArray = static_cast<StructType*>(&CurrentDialogueArray);
				if(!StructArray || StructArray->DialogueArrayLabel != InDialogueLabel) {continue;}
								
				return StructArray;
			}
		}
	}

	return nullptr;
}
