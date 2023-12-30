// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterTypes.h"
#include "Characters/Data/SI_CharacterData.h"

FSI_CharacterState::FSI_CharacterState(USI_CharacterData* InCharacterData) : CharacterData(InCharacterData)
{
}

FSI_CharacterMapState* FSI_CharacterState::GetMapStateByCaseTag(const FGameplayTag& InCaseTag)
{
	FSI_CharacterCaseState* CharacterCaseState = CharacterCaseStates.Find(InCaseTag);
	if(!CharacterCaseState) {return nullptr;}

	return &CharacterCaseState->CaseMapState;
}

FSI_DialogueState* FSI_CharacterState::GetDialogueStateByCaseTag(const FGameplayTag& InCaseTag)
{
	FSI_CharacterCaseState* CharacterCaseState = CharacterCaseStates.Find(InCaseTag);
	if(!CharacterCaseState) {return nullptr;}

	return &CharacterCaseState->CaseDialogueState;
}

FSI_CharacterCaseState* FSI_CharacterState::GetCaseStateByTag(const FGameplayTag& InCaseTag)
{
	return CharacterCaseStates.Find(InCaseTag);
}

const FGameplayTag& FSI_CharacterState::GetCharacterTag() const
{
	if(!IsValid(CharacterData)) {return FGameplayTag::EmptyTag;}
	
	return CharacterData->CharacterTag;
}

FSI_CharacterCaseState* FSI_CharacterState::AddNewCaseState(USI_CaseData* InCurrentCaseData)
{
	if(!IsValid(InCurrentCaseData)) {return nullptr;}
	
	FSI_CharacterCaseState* CaseState = new FSI_CharacterCaseState(InCurrentCaseData);
	CharacterCaseStates.Add(InCurrentCaseData->CaseTag, *CaseState);
	return CaseState; 
}

void FSI_CharacterState::AddNewDialogueState(const FGameplayTag& InCaseTag, FSI_DialogueState* InDialogueState)
{
	FSI_CharacterCaseState* CharacterCaseState = CharacterCaseStates.Find(InCaseTag);
	if(!CharacterCaseState) {return;}

	CharacterCaseState->CaseDialogueState = *InDialogueState;
}

FSI_CharacterCaseState::FSI_CharacterCaseState(USI_CaseData* InCaseCaseData)  : CaseData(InCaseCaseData)
{
}

USI_CharacterData* FSI_CharacterState::GetCharacterData() const
{
	return CharacterData;
}


