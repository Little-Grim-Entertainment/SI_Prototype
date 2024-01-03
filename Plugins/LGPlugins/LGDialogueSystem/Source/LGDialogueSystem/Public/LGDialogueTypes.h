// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LGDialogueTypes.generated.h"

class ULGDialogueDataAsset;
class UDataTable;

DECLARE_LOG_CATEGORY_EXTERN(LogLGDialogue, Log, All);

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGEmphasizedWord
{
	GENERATED_BODY()

	
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogue : public FTableRowBase
{
	GENERATED_BODY()

	FLGDialogue();
	
	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	FGuid DialogueID;

	bool operator==(const FLGDialogue& OtherDialogue) const;
	bool operator!=(const FLGDialogue& OtherDialogue) const;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGConversationDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FGameplayTag SpeakerTag;
	
	UPROPERTY(VisibleAnywhere, Category = "Dialogue", meta=(DisplayAfter="SpeakerTag"))
	FText Dialogue;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue", meta=(DisplayAfter="SpeakerTag"))
	FString EmphasizedWordsString;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue", meta=(DisplayAfter="SpeakerTag"))
	FString EmphasizedColorsString;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogueURL
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString URL;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag DialogueStructType;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGCharacterDialogue
{
	GENERATED_BODY()

	FLGCharacterDialogue();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULGDialogueDataAsset* CharacterDialogueData = nullptr;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogueState
{
	GENERATED_BODY()
	
	
};