// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_CharacterTypes.generated.h"

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CharacterState
{
	GENERATED_BODY()

	FSI_CharacterState();
	FSI_CharacterState(const FGameplayTag& InCharacterTag);

	void AddNewDialogueState(const FGameplayTag& InCaseTag, const FSI_DialogueState& InDialogueState);
	
	const FGameplayTag& GetCharacterTag()const;
	FSI_DialogueState* GetDialogueStateByCase(const FGameplayTag& InCaseTag);
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo")
	FGameplayTag CharacterTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterInfo | Dialogue")
	TMap<FGameplayTag, FSI_DialogueState> CaseDialogueStates;
};
