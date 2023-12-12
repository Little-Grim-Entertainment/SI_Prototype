// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LGDialogueDataAsset.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_DialogueDataAsset.generated.h"

USTRUCT()
struct FSI_DialogueArrays
{
	GENERATED_BODY()

	FSI_DialogueArrays();

	UPROPERTY()
	TArray<FSI_PrimaryDialogue> PrimaryDialogueArray;

	UPROPERTY()
	TArray<FSI_CorrectedDialogue> CorrectedDialogueArray;

	UPROPERTY()
	TArray<FSI_DefaultResponse> DefaultResponseArray;
};

UCLASS()
class SI_PROTOTYPE_API USI_DialogueDataAsset : public ULGDialogueDataAsset
{
	GENERATED_BODY()

	USI_DialogueDataAsset();

public:

	virtual UScriptStruct* GetUStructContainer() override;
	virtual void* GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag) override;
	virtual FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag) override;
	
	FSI_DialogueArrays DialogueData = FSI_DialogueArrays();
};
