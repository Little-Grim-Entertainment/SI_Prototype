// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RuntimeDataTable.h"
#include "LGDialogueTypes.generated.h"

class ULGDialogueDataAsset;

DECLARE_LOG_CATEGORY_EXTERN(LogLGDialogue, Log, All);

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogue
{
	GENERATED_BODY()

	FLGDialogue();

	UPROPERTY(VisibleAnywhere)
	FGuid DialogueID;

	bool operator==(const FLGDialogue& OtherDialogue) const;
	bool operator!=(const FLGDialogue& OtherDialogue) const;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogueURL
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString FileName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString URL;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag DialogueStructType;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGCharacterDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ULGDialogueDataAsset*> DialogueData; 
};