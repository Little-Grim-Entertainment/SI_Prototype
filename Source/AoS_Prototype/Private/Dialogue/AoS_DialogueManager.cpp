// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/AoS_DialogueManager.h"
#include "AoS_GameInstance.h"
#include "Characters/AoS_CharacterManager.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "Kismet/GameplayStatics.h"
#include "Dialogue/DialogueSession.h"


void UAoS_DialogueManager::StartDialogue(FText CharacterName)
{
	// TO DO: Get GameInstance
	if (!IsValid(GameInstance)) return;
	UAoS_CharacterManager* CharacterManager = GameInstance->GetSubsystem<UAoS_CharacterManager>();
	if (!IsValid(CharacterManager))
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterManager not found!"));
		StartDefaultDialogue(CharacterName);
		return;
	}

	// TO DO: need a function that updates the dialogue on the character
	CurrentCharacterData = CharacterManager->GetActiveCharacterData(CharacterName);
	if (!CurrentCharacterData || !CurrentCharacterData->CurrentDialogueData.RelevantDialogue)
	{
		StartDefaultDialogue(CharacterName);
		return;
	}

	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_DialogueMode);
	CurrentDialogue = CurrentCharacterData->CurrentDialogueData.RelevantDialogue;
	CurrentDialogue->StartDialogue(CharacterName, CurrentCharacterData->CurrentDialogueData.SavedNode, CurrentCharacterData->CurrentDialogueData.AngerLevel);
}

void UAoS_DialogueManager::ExitDialogue(UDialogueSessionNode* NewSaveNode, int32 NewAngerLevel)
{
	check(CurrentCharacterData);
	CurrentCharacterData->CurrentDialogueData.AngerLevel = NewAngerLevel;
	CurrentCharacterData->CurrentDialogueData.SavedNode = NewSaveNode;

	CurrentDialogue = nullptr;
	CurrentCharacterData = nullptr;
}


void UAoS_DialogueManager::StartDefaultDialogue(FText CharacterName)
{
	// TO DO: find default dialogue


	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_DialogueMode);
}

void UAoS_DialogueManager::OnInterrogationPressed()
{
	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_InterrogationMode);
}

bool UAoS_DialogueManager::CanEnterInterrogation()
{
	return (GameInstance->GetPlayerMode() == EPlayerMode::PM_InterrogationMode && CurrentDialogue != nullptr && CurrentDialogue->bIsInterrogationDialogue);
}

UDialogueSession* UAoS_DialogueManager::FindDialogue(UAoS_Case* Case, UAoS_Part* Part)
{
	return nullptr;
}
