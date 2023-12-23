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

	const FGameplayTag& GetCharacterTag()const;
	FSI_PrimaryDialogueArray& GetPrimaryDialogueArray();
	void SetPrimaryDialogueArray(const FSI_PrimaryDialogueArray& InPrimaryDialogueArray);

private:

	UPROPERTY()
	FGameplayTag CharacterTag;
	
	UPROPERTY()
	FSI_PrimaryDialogueArray CurrentPrimaryDialogueArray;
};
