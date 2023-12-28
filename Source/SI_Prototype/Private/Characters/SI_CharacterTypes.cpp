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

FSI_DialogueState* FSI_CharacterState::GetDialogueStateByCase(const FGameplayTag& InCaseTag)
{
	return CaseDialogueStates.Find(InCaseTag);
}

void FSI_CharacterState::AddNewDialogueState(const FGameplayTag& InCaseTag, const FSI_DialogueState& InDialogueState)
{
	CaseDialogueStates.Add(InCaseTag, InDialogueState);
}


