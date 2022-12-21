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

void UAoS_DialogueManager::OnNextPressed()
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::Next);
}

void UAoS_DialogueManager::OnPreviousPressed()
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::Previous);
}

void UAoS_DialogueManager::OnPressPressed()
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::Press);
}

void UAoS_DialogueManager::OnTextOptionSelected(FText RelatedText)
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::TextOption, nullptr, RelatedText);
}

void UAoS_DialogueManager::OnItemOptionSelected(UObject* RelatedItem)
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::ItemOption, RelatedItem);
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

void UAoS_DialogueManager::SetupBindings()
{
	// Get the HUD, get the dialogue box, bind u objects (need to make functions UFUNCTIONs)
}

bool UAoS_DialogueManager::HasNextOption()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::Next);
}

bool UAoS_DialogueManager::HasPreviousOption()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::Previous);
}

bool UAoS_DialogueManager::HasPressOption()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::Press);
}

bool UAoS_DialogueManager::HasTextOptions()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::TextOption);
}

bool UAoS_DialogueManager::HasItemOptions()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::ItemOption);
}

bool UAoS_DialogueManager::CanEnterInterrogation()
{
	return (GameInstance->GetPlayerMode() == EPlayerMode::PM_InterrogationMode && CurrentDialogue != nullptr && CurrentDialogue->bIsInterrogationDialogue);
}

UDialogueSession* UAoS_DialogueManager::FindDialogue(UAoS_Case* Case, UAoS_Part* Part)
{
	return nullptr;
}
