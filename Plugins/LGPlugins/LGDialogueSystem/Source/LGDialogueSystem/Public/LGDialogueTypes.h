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
struct LGDIALOGUESYSTEM_API FLGDialogueArray
{
	GENERATED_BODY()

	FLGDialogueArray();
	virtual ~FLGDialogueArray(){}
	
	UPROPERTY(VisibleAnywhere)
	FGameplayTag DialogueStructTypeTag;

	UPROPERTY(VisibleAnywhere)
	FName PropertyName;

	UPROPERTY(VisibleAnywhere)
	FGuid DialogueArrayID;

	virtual void SetDataTable(UDataTable* InDataTable);
	
	virtual UScriptStruct* GetStructContainer();
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable);
	
	bool operator==(const FLGDialogueArray& OtherDialogue) const;
	bool operator!=(const FLGDialogueArray& OtherDialogue) const;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogue : public FTableRowBase
{
	GENERATED_BODY()

	FLGDialogue();
	
	UPROPERTY(VisibleAnywhere)
	FGuid DialogueID;

	bool operator==(const FLGDialogue& OtherDialogue) const;
	bool operator!=(const FLGDialogue& OtherDialogue) const;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGConversationDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag SpeakerTag;
	
	UPROPERTY(VisibleAnywhere)
	FText Dialogue;

	UPROPERTY(VisibleAnywhere)
	FString EmphasizedWordsString;

	UPROPERTY(VisibleAnywhere)
	FString EmphasizedColorsString;
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

	FLGCharacterDialogue();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULGDialogueDataAsset* CharacterDialogueData = nullptr;
};