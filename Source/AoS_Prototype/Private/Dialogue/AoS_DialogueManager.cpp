// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/AoS_DialogueManager.h"
#include "AoS_GameInstance.h"
#include "Characters/AoS_CharacterManager.h"
#include "Data/Cases/AoS_CaseManager.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "Kismet/GameplayStatics.h"
#include "Dialogue/DialogueSession.h"


void UAoS_DialogueManager::StartDialogue(UAoS_CharacterData* InCharacterData)
{
	// TO DO: Get GameInstance
	if (!IsValid(GameInstance)) return;
	UAoS_CharacterManager* CharacterManager = GameInstance->GetSubsystem<UAoS_CharacterManager>();
	if (!IsValid(CharacterManager))
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterManager not found!"));
		StartDefaultDialogue(InCharacterData);
		return;
	}

	// TO DO: need a function that updates the dialogue on the character
    UAoS_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	CurrentCharacterData = InCharacterData;
	if (!CurrentCharacterData || !CurrentCharacterData->GetCurrentDialogueData(CaseManager).RelevantDialogue)
	{
		StartDefaultDialogue(CurrentCharacterData);
		return;
	}

	CurrentDialogue = CurrentCharacterData->GetCurrentDialogueData(CaseManager).RelevantDialogue;
	CurrentDialogue->StartDialogue(CurrentCharacterData, this, CaseManager);
	//GameInstance->RequestNewPlayerMode(EPlayerMode::PM_DialogueMode);
}

void UAoS_DialogueManager::ExitDialogue(UDialogueSessionNode* NewSaveNode, int32 NewAngerLevel)
{
	check(CurrentCharacterData);
    UAoS_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	CurrentCharacterData->GetCurrentDialogueData(CaseManager).AngerLevel = NewAngerLevel;
	CurrentCharacterData->GetCurrentDialogueData(CaseManager).SavedNode = NewSaveNode;

	CurrentDialogue = nullptr;
	CurrentCharacterData = nullptr;

	//GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());
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


void UAoS_DialogueManager::StartDefaultDialogue(UAoS_CharacterData* InCharacterData)
{
	// TO DO: find default dialogue


	//GameInstance->RequestNewPlayerMode(EPlayerMode::PM_DialogueMode);
}

void UAoS_DialogueManager::OnInterrogationPressed()
{
	//GameInstance->RequestNewPlayerMode(EPlayerMode::PM_InterrogationMode);
}

UDialogueSession* UAoS_DialogueManager::GetCurrentDialogue()
{
	return CurrentDialogue;
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
	//return (GameInstance->GetPlayerMode() == EPlayerMode::PM_InterrogationMode && CurrentDialogue != nullptr && CurrentDialogue->bIsInterrogationDialogue);
	return false;
}

UDialogueSession* UAoS_DialogueManager::FindDialogue(UAoS_Case* Case, UAoS_Part* Part)
{
	return nullptr;
}
