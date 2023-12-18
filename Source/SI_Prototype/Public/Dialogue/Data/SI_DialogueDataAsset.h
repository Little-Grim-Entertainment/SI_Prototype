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

	virtual void OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath, const FString& InDialogueLabel, const FGuid& InDialogueDataID) override;
	virtual bool StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType) override; 
	
	virtual FArrayProperty* GetArrayPropertyByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueDataID) override;
	virtual void* GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueDataID, bool bReturnUScriptContainer = false) override;
	virtual FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag) override;
	virtual FName GetStructTypeNameByTag(const FGameplayTag& InGameplayTag) override;
	
	FSI_DialogueArrayData* GetDialogueDataByID(const FGuid& InDialogueDataID);

	FLGDialogueArray* GetDialogueStructArrayByTagAndID(const FGameplayTag& InStructTypeTag, const FGuid& InDialogueDataID);

	template <class StructPtr, class ArrayPtr>
	TArray<ArrayPtr>* GetDialogueArrayFromStruct(FLGDialogueArray* InArrayPtr);

private:

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	FSI_DefaultDialogue DefaultDialogue;
	
	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TArray<FSI_CaseDialogue> CaseDialogue;

	void InitializeDialogueLabels();
	void InitializeFileNames();

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
