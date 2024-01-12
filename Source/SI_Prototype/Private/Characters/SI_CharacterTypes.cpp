// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterTypes.h"
#include "Characters/Data/SI_CharacterData.h"
#include "Dialogue/Data/SI_DialogueDataAsset.h"

void FSI_CharacterCaseState::InitializeDefaultCaseDialogue()
{
	USI_CaseData* CaseDataPtr = CaseData.Get();
	if(!IsValid(CaseDataPtr)){return;}

	
}

FSI_CharacterState::FSI_CharacterState(const USI_CharacterData* InCharacterData, const ASI_Character* InCharacter) :
	CharacterData(InCharacterData),
	CharacterPtr(InCharacter)
{
	InitializeDefaultDialogue();
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
	if(!IsValid(CharacterData.Get())) {return FGameplayTag::EmptyTag;}
	
	return CharacterData->CharacterTag;
}

FSI_CharacterCaseState* FSI_CharacterState::AddNewCaseState(const USI_CaseData* InCurrentCaseData, const UDataTable* InCurrentPartDialogueTable)
{
	if(!IsValid(InCurrentCaseData)) {return nullptr;}
	
	FSI_CharacterCaseState* CaseState = new FSI_CharacterCaseState(InCurrentCaseData, InCurrentPartDialogueTable);
	CharacterCaseStates.Add(InCurrentCaseData->CaseTag, *CaseState);
	return CaseState; 
}

void FSI_CharacterState::InitializeDefaultDialogue()
{
	const USI_CharacterData* CharacterDataPtr = CharacterData.Get();
	if(!IsValid(CharacterDataPtr)) {return;}

	const USI_DialogueDataAsset* CharacterDialogueData = CharacterDataPtr->CharacterDialogue;
	if(!IsValid(CharacterDialogueData)) {return;}

	const UDataTable* DefaultDialogueTable = CharacterDialogueData->DefaultPrimaryDialogueDataTable;
	if(!IsValid(DefaultDialogueTable)) {return;}
	
	TArray<FSI_PrimaryDialogue*> DefaultPrimaryDialogueArray;
	DefaultDialogueTable->GetAllRows(nullptr, DefaultPrimaryDialogueArray);
	
	for(const FSI_PrimaryDialogue* CurrentPrimaryDialogue : DefaultPrimaryDialogueArray)
	{
		DefaultDialogueState.CurrentPrimaryDialogueArray.Add(*CurrentPrimaryDialogue);
	}
}


FSI_CharacterCaseState::FSI_CharacterCaseState(const USI_CaseData* InCaseCaseData, const UDataTable* InCurrentPartDialogueTable)  : CaseData(InCaseCaseData)
{	
	CaseDialogueState = FSI_DialogueState(InCurrentPartDialogueTable);
	CaseData = InCaseCaseData->GetPathName();
	InitializeDefaultCaseDialogue();
}

USI_CharacterData* FSI_CharacterState::GetCharacterData() const
{
	return CharacterData.Get();
}


