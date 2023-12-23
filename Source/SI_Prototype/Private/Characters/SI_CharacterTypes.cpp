// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterTypes.h"


FSI_CharacterState::FSI_CharacterState()
{
}

FSI_CharacterState::FSI_CharacterState(const FGameplayTag& InCharacterTag) : CharacterTag(InCharacterTag)
{
}

const FGameplayTag& FSI_CharacterState::GetCharacterTag() const
{
	return CharacterTag;
}

FSI_PrimaryDialogueArray& FSI_CharacterState::GetPrimaryDialogueArray()
{
	return CurrentPrimaryDialogueArray;
}

void FSI_CharacterState::SetPrimaryDialogueArray(const FSI_PrimaryDialogueArray& InPrimaryDialogueArray)
{
	CurrentPrimaryDialogueArray = InPrimaryDialogueArray;
}
