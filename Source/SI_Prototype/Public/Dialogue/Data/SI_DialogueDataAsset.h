// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LGDialogueDataAsset.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_DialogueDataAsset.generated.h"

class USI_CsvDataProcessorObject;

UCLASS()
class SI_PROTOTYPE_API USI_DialogueDataAsset : public ULGDialogueDataAsset
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = "FileInfo", meta=(Categories="Character"))
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	FSI_DefaultDialogueData DefaultDialogue;

	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	FSI_DefaultBubbleDialogueData DefaultBubbleDialogue;
	
	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	TArray<FSI_CaseDialogueData> CaseDialogue;
};