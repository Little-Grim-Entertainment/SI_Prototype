// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_CsvDataTypes.h"
#include "RuntimeDataTable.h"
#include "SI_EditorUtilityWidget.h"
#include "Cases/Data/SI_CaseData.h"
#include "Dialogue/Data/SI_CaseDialogueDataTable.h"
#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "Interfaces/LGCsvProcessorInterface.h"
#include "SI_UpdateDialogueEditorUtilityWidget.generated.h"

class USI_DialogueDataAsset;
class USI_CaseDialogueDataTable;

UCLASS(Abstract, meta = (ShowWorldContextPin), config = Editor)
class SI_EDITOR_API USI_UpdateDialogueEditorUtilityWidget : public USI_EditorUtilityWidget, public ILGCsvProcessorInterface
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueData")
	USI_DialogueDataAsset* DialogueData;
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void UpdateDialogue();

private:

	FString GetFilePath();
	FString GetContentPath();

	void UpdateDefaultDialogue();
	void UpdateBubbleDialogue();
	void UpdateCaseDialogue();

	TArray<FLGDialogueArrayData*> DialogueDataArray;
	
protected:
	
	virtual void OnRequestCheckForEmbeddedCsv_Implementation(const FRuntimeDataTableCallbackInfo& InCallbackInfo, const FString& InSavePath) override;
	virtual void OnCsvProcessComplete_Implementation(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr) override;
	virtual bool StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType) override;
	bool IsEmbeddedStructType(const FGameplayTag& InStructType);

	USI_CaseDialogueDataTable* GenerateNewCaseDataTable(const FString& InPackagePath, const FString& InFileName);
	void AddNewCaseToTable(UDataTable* InCaseDataTable, const USI_CaseData* InCaseData);
	
	bool IsCaseInTable(const FGameplayTag& InCaseTag, const UDataTable* InCaseDialogueDataTable) const;
	
	bool IsPartInTable(const FGameplayTag& InCaseTag, const FName& InPartTag, const UDataTable* InCaseDialogueDataTable) const;
	void AddNewPartToTable(const UDataTable* InCaseDialogueDataTable, const FGameplayTag& InCaseTag, const FSI_PartDialogueData* InPartDialogueData);

	FSI_PartDialogueData* GetPartDialogueDataByID(const FGuid& InPartID);
	FSI_PartDialogueData* GetPartDialogueDataByTag(const FName& InPartTag);
	
	void UpdateDialogueDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr);
	void UpdateDialogueDataTableRows(UDataTable* InDataTable, FRuntimeDataTableCallbackInfo& InCallbackInfo);
	void InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	
	UScriptStruct* GetStructContainerByID(const FGuid& InDialogueArrayID);
	UScriptStruct* GetStructTypeByID(const FGuid& InDialogueArrayID);

	void* GetDialogueStructArrayByID(const FGuid& InDialogueArrayID);
	FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag);
	FName GetStructTypeNameByTag(const FGameplayTag& InGameplayTag);
	UDataTable* GenerateNewDialogueDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo);
	void BeginCsvImport(const FString& InFilePath, const FLGDialogueURL& InUrl, const FString& InFileName, const FGuid& InDataTableOwnerID = FGuid());

	void InitializedDialogueArrayTag(const FRuntimeDataTableCallbackInfo& InCallbackInfo);
	
	UFUNCTION()
	void OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo);
	
	template <class StructPtr>
	StructPtr* GetDialogueDataTypeByID(const FGuid& InStructID);
	
	template <class ArrayPtr>
	ArrayPtr* GetDialogueArrayTypeByID(const FGuid& InDialogueArrayID);

	template <class StructPtr, class ArrayPtr>
	TArray<ArrayPtr>* GetDialogueArrayFromStruct(FLGDialogueArray* InArrayPtr);

	template <class ArrayPtr>
	UScriptStruct* GetScriptStructTypeByID(const FGuid& InStructID);
	
	template <class StructPtr, class ArrayPtr>
	void UpdateDataTableStructByType(UDataTable* InDataTable, FLGDialogueArray* InArrayPtr);
};

template <class StructPtr>
StructPtr* USI_UpdateDialogueEditorUtilityWidget::GetDialogueDataTypeByID(const FGuid& InStructID)
{
	for (FLGDialogueArrayData* CurrentDialogueData : DialogueDataArray)
	{
		if(!CurrentDialogueData) {continue;}
		if(CurrentDialogueData->DialogueDataID == InStructID)
		{
			StructPtr* DialogueDataPtr = static_cast<StructPtr*>(CurrentDialogueData);
			return DialogueDataPtr;
		}
	}
	
	return nullptr;
}

template <class ArrayPtr>
ArrayPtr* USI_UpdateDialogueEditorUtilityWidget::GetDialogueArrayTypeByID(const FGuid& InDialogueArrayID)
{
	for (FLGDialogueArrayData* CurrentDialogueData : DialogueDataArray)
	{
		if(!CurrentDialogueData) {continue;}
		for (FLGDialogueArray* CurrentDialogueArray : CurrentDialogueData->DialogueArrays)
		{
			if(!CurrentDialogueArray) {continue;}
			if(CurrentDialogueArray->DialogueArrayID == InDialogueArrayID)
			{
				ArrayPtr* DialogueArrayPtr = static_cast<ArrayPtr*>(CurrentDialogueArray);
				return DialogueArrayPtr;
			}
		}
	}
	
	return nullptr;
}

template <class StructPtr, class ArrayPtr>
TArray<ArrayPtr>* USI_UpdateDialogueEditorUtilityWidget::GetDialogueArrayFromStruct(FLGDialogueArray* InArrayPtr)
{
	StructPtr* DialogueArrayPtr = static_cast<StructPtr*>(InArrayPtr);
	if(DialogueArrayPtr)
	{
		TArray<ArrayPtr>* DialogueArray = DialogueArrayPtr->GetDialogueArray();
		return DialogueArray;
	}
	return nullptr;
}

template <class ArrayPtr>
UScriptStruct* USI_UpdateDialogueEditorUtilityWidget::GetScriptStructTypeByID(const FGuid& InStructID)
{
	ArrayPtr* DialogueArrayPtr = GetDialogueArrayTypeByID<ArrayPtr>(InStructID);
	if(!DialogueArrayPtr) {return nullptr;}

	return ArrayPtr::StaticStruct();
}

template <class StructType, class ArrayType>
void USI_UpdateDialogueEditorUtilityWidget::UpdateDataTableStructByType(UDataTable* InDataTable, FLGDialogueArray* InArrayPtr)
{
	TArray<StructType*> DialoguePtrs;
	InDataTable->GetAllRows(TEXT(""),DialoguePtrs);

	ArrayType* ArrayPtr = static_cast<ArrayType*>(InArrayPtr);
	if(!ArrayPtr) {return;}

	ArrayPtr->UpdateDataTableStructValues(DialoguePtrs);
	InDataTable->MarkPackageDirty();
}
