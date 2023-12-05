// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LGDialogueTypes.h"
#include "LGProjectDialogueData.generated.h"

class ULGDialogueDataAsset;

UCLASS()
class LGDIALOGUESYSTEM_API ULGProjectDialogueData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UFUNCTION(CallInEditor)
	void UpdateAllDialogue();
	
private:

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TArray<FLGCharacterDialogue> CharacterDialogue; 
};
