// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LGDialogueDataAsset.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_DialogueDataAsset.generated.h"

UCLASS()
class SI_PROTOTYPE_API USI_DialogueDataAsset : public ULGDialogueDataAsset
{
	GENERATED_BODY()

	USI_DialogueDataAsset();

protected:

	virtual void UpdateDialogue_Internal() override;
	
	virtual void OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath, const FString& InDialogueLabel, FGuid& InDialogueDataID, FGuid& InDialogueArrayID) override;
	virtual bool StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType) override; 

	virtual void UpdateDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr) override;
	virtual void UpdateDataTableRows(UDataTable* InDataTable, FRuntimeDataTableCallbackInfo& InCallbackInfo) override;
	virtual void InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID) override;
	
	virtual UScriptStruct* GetStructContainerByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID) override;
	virtual UScriptStruct* GetStructTypeByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID) override;

	virtual void* GetDialogueStructArrayByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID) override;
	virtual FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag) override;
	virtual FName GetStructTypeNameByTag(const FGameplayTag& InGameplayTag) override;
	virtual UDataTable* GenerateNewDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo) override;

	virtual const FGameplayTag& GetCharacterTag() override;
	
	FSI_DialogueArrayData* GetDialogueDataByID(const FGuid& InDialogueDataID);
	FLGDialogueArray* GetDialogueArrayStructByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	
	template <class StructPtr, class ArrayPtr>
	TArray<ArrayPtr>* GetDialogueArrayFromStruct(FLGDialogueArray* InArrayPtr);

	template <class StructPtr, class ArrayPtr>
	void UpdateDataTableStructByType(UDataTable* InDataTable, FLGDialogueArray* InArrayPtr);

private:

	UPROPERTY(EditAnywhere, Category = "FileInfo", meta=(Categories="Character"))
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	FSI_DefaultDialogueData DefaultDialogue;

	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	FSI_DefaultBubbleDialogueData DefaultBubbleDialogue;
	
	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	TArray<FSI_CaseDialogueData> CaseDialogue;

	void UpdateDefaultDialogue();
	void UpdateBubbleDialogue();
	void UpdateCaseDialogue();
	
	void InitializeDialogueLabels(const ESI_MainDialogueTypes& InMainDialogueType);
	void InitializeFileNames(const ESI_MainDialogueTypes& InMainDialogueType);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};

template <class StructPtr, class ArrayPtr>
TArray<ArrayPtr>* USI_DialogueDataAsset::GetDialogueArrayFromStruct(FLGDialogueArray* InArrayPtr)
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
void USI_DialogueDataAsset::UpdateDataTableStructByType(UDataTable* InDataTable, FLGDialogueArray* InArrayPtr)
{
	TArray<StructType*> DialoguePtrs;
	InDataTable->GetAllRows(TEXT(""),DialoguePtrs);

	ArrayType* ArrayPtr = static_cast<ArrayType*>(InArrayPtr);
	if(!ArrayPtr) {return;}

	ArrayPtr->UpdateDataTableStructValues(DialoguePtrs);
	InDataTable->MarkPackageDirty();
}
