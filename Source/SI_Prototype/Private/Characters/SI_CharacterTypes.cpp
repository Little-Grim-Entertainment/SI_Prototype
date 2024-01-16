// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterTypes.h"
#include "Characters/Data/SI_CharacterData.h"
#include "Dialogue/Data/SI_DialogueDataAsset.h"

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

bool FSI_CharacterState::HasCaseDialogue(const FGameplayTag& InCaseTag) const
{
	if(CharacterCaseStates.Num() <= 0) {return false;}
	
	const FSI_CharacterCaseState* FoundCharacterCaseState = CharacterCaseStates.Find(InCaseTag);
	return FoundCharacterCaseState != nullptr;
}

FSI_CharacterCaseState* FSI_CharacterState::AddNewCaseState(const USI_CaseData* InCurrentCaseData, const UDataTable* InCurrentPrimaryDialogueTable, const UDataTable* InCurrentCorrectedDialogueTable, const UDataTable* InCurrentDefaultResponseTable)
{
	if(!IsValid(InCurrentCaseData)) {return nullptr;}
	
	FSI_CharacterCaseState* CaseState = new FSI_CharacterCaseState(InCurrentCaseData, InCurrentPrimaryDialogueTable, InCurrentCorrectedDialogueTable, InCurrentDefaultResponseTable);
	CharacterCaseStates.Add(InCurrentCaseData->CaseTag, *CaseState);
	return CaseState; 
}

void FSI_CharacterState::InitializeDefaultDialogue()
{
	const USI_CharacterData* CharacterDataPtr = CharacterData.Get();
	if(!IsValid(CharacterDataPtr)) {return;}

	const USI_DialogueDataAsset* CharacterDialogueData = CharacterDataPtr->CharacterDialogue;
	if(!IsValid(CharacterDialogueData)) {return;}

	const UDataTable* DefaultPrimaryDialogueTable = CharacterDialogueData->DefaultPrimaryDialogueDataTable;
	const UDataTable* DefaultCorrectedDialogueTable = CharacterDialogueData->DefaultCorrectedDialogueDataTable;
	const UDataTable* DefaultResponseTable = CharacterDialogueData->DefaultResponseDialogueDataTable;

	DefaultDialogueState = FSI_DialogueState(DefaultPrimaryDialogueTable, DefaultCorrectedDialogueTable, DefaultResponseTable);
}


FSI_CharacterCaseState::FSI_CharacterCaseState(const USI_CaseData* InCurrentCaseData, const UDataTable* InCurrentPrimaryDialogueTable, const UDataTable* InCurrentCorrectedDialogueTable, const UDataTable* InCurrentDefaultResponseTable)  : CaseData(InCurrentCaseData)
{	
	CaseDialogueState = FSI_DialogueState(InCurrentPrimaryDialogueTable, InCurrentCorrectedDialogueTable, InCurrentDefaultResponseTable);
	CaseData = InCurrentCaseData;
}

USI_CharacterData* FSI_CharacterState::GetCharacterData() const
{
	return CharacterData.Get();
}


