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

	virtual void OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath, const FString& InDialogueLabel, const FGuid& InDialogueID) override;
	
	virtual UScriptStruct* GetUStructContainerByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueStructID) override;
	virtual void* GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueID) override;
	virtual FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag) override;
	virtual FName GetStructTypeNameByTag(const FGameplayTag& InGameplayTag) override;

	FLGDialogue* GetDialogueStructByID(const FGuid& InDialogueStructID);
	FSI_DialogueArrays* GetDialogueDataByID(const FGuid& InDialogueDataID);

	bool IsMainStructType(const FGameplayTag& InGameplayTag) const;

private:

	UPROPERTY(EditAnywhere, Category = "CaseInfo")
	TArray<FSI_CaseDialogue> CaseDialogue;

	void InitializeDialogueLabels();
	void InitializeFileNames();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
