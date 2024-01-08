// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cases/Data/SI_CaseData.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_CharacterTypes.generated.h"

class USI_CharacterData;

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CharacterMapState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Map")
	FGameplayTag CurrentMapTag;

	UPROPERTY(VisibleAnywhere, Category = "Map")
	FTransform CurrentMapTransform;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CharacterCaseState
{
	GENERATED_BODY()

	FSI_CharacterCaseState(){}
	FSI_CharacterCaseState(USI_CaseData* InCaseCaseData);
	
	// Case Dialogue by Case Tag
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo | Dialogue")
	FSI_DialogueState CaseDialogueState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo | Location")
	FSI_CharacterMapState CaseMapState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo | Data")
	USI_CaseData* CaseData = nullptr;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CharacterState
{
	GENERATED_BODY()

	FSI_CharacterState(){}
	FSI_CharacterState(USI_CharacterData* InCharacterData);

	FSI_CharacterMapState* GetMapStateByCaseTag(const FGameplayTag& InCaseTag);
	FSI_DialogueState* GetDialogueStateByCaseTag(const FGameplayTag& InCaseTag);
	FSI_CharacterCaseState* GetCaseStateByTag(const FGameplayTag& InCaseTag);
	USI_CharacterData* GetCharacterData() const; 
	const FGameplayTag& GetCharacterTag() const;

	FSI_CharacterCaseState* AddNewCaseState(USI_CaseData* InCurrentCaseData);
	void AddNewDialogueState(const FGameplayTag& InCaseTag, FSI_DialogueState* InDialogueState);

	// Case States by Case Tag
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo | Dialogue")
	TMap<FGameplayTag, FSI_CharacterCaseState> CharacterCaseStates;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	USI_CharacterData* CharacterData = nullptr;
};
