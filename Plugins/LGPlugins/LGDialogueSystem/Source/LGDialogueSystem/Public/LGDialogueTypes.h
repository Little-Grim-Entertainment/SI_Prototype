// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
//#include "LGCoreTypes.h"
#include "LGDialogueTypes.generated.h"

class ULGDialogueDataAsset;

DECLARE_LOG_CATEGORY_EXTERN(LogLGDialogue, Log, All);

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGEmphasizedWord
{
	GENERATED_BODY()

	
};

/*USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogueGuid : public FLGGuid
{
	GENERATED_BODY()

};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogueArrayGuid : public FLGDialogueGuid
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogueDataGuid : public FLGDialogueGuid
{
	GENERATED_BODY()
	
};*/

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

	UPROPERTY(EditAnywhere, meta = (RequiredAssetDataTags = "RowStructure=/Script/SI_Prototype.SI_PrimaryDialogue, /Script/SI_Prototype.SI_CorrectedDialogue, /Script/SI_Prototype.SI_DefaultResponse, /Script/SI_Prototype.SI_PressDialogue, /Script/SI_Prototype.SI_ResponseDialogue, /Script/SI_Prototype.SI_BubbleDialogue"))
	TSoftObjectPtr<UDataTable> ConnectedDataTable;

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