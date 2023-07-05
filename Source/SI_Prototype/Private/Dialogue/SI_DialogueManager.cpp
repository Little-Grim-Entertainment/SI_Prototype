// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueManager.h"
#include "SI_GameInstance.h"
#include "Characters/SI_CharacterManager.h"
#include "Data/Cases/SI_CaseManager.h"
#include "Data/Characters/SI_CharacterData.h"
#include "Kismet/GameplayStatics.h"
#include "Dialogue/SI_DialogueSession.h"


void USI_DialogueManager::StartDialogue(USI_CharacterData* InCharacterData)
{
	// TO DO: Get GameInstance
	
	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)) return;
	USI_CharacterManager* CharacterManager = GameInstance->GetSubsystem<USI_CharacterManager>();
	if (!IsValid(CharacterManager))
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterManager not found!"));
		StartDefaultDialogue(InCharacterData);
		return;
	}

	// TO DO: need a function that updates the dialogue on the character
    USI_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	CurrentCharacterData = Cast<USI_CharacterData>(InCharacterData);
	if (!CurrentCharacterData || !CurrentCharacterData->GetCurrentDialogueData(CaseManager).RelevantDialogue)
	{
		StartDefaultDialogue(CurrentCharacterData);
		return;
	}

	CurrentDialogue = CurrentCharacterData->GetCurrentDialogueData(CaseManager).RelevantDialogue;
	CurrentDialogue->StartDialogue(CurrentCharacterData, this, CaseManager);
	//GameInstance->RequestNewPlayerMode(EPlayerMode::PM_DialogueMode);
}

void USI_DialogueManager::ExitDialogue(UDialogueSessionNode* NewSaveNode, int32 NewAngerLevel)
{
	check(CurrentCharacterData);
    USI_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	CurrentCharacterData->GetCurrentDialogueData(CaseManager).AngerLevel = NewAngerLevel;
	CurrentCharacterData->GetCurrentDialogueData(CaseManager).SavedNode = NewSaveNode;

	CurrentDialogue = nullptr;
	CurrentCharacterData = nullptr;

	//GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());
}

void USI_DialogueManager::OnNextPressed()
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::Next);
}

void USI_DialogueManager::OnPreviousPressed()
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::Previous);
}

void USI_DialogueManager::OnPressPressed()
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::Press);
}

void USI_DialogueManager::OnTextOptionSelected(FText RelatedText)
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::TextOption, nullptr, RelatedText);
}

void USI_DialogueManager::OnItemOptionSelected(UObject* RelatedItem)
{
	if (!CurrentDialogue) { return; }

	CurrentDialogue->SelectEdgeOfType(EEdgeType::ItemOption, RelatedItem);
}


void USI_DialogueManager::StartDefaultDialogue(USI_CharacterData* InCharacterData)
{
	// TO DO: find default dialogue


	//GameInstance->RequestNewPlayerMode(EPlayerMode::PM_DialogueMode);
}

void USI_DialogueManager::OnInterrogationPressed()
{
	//GameInstance->RequestNewPlayerMode(EPlayerMode::PM_InterrogationMode);
}

UDialogueSession* USI_DialogueManager::GetCurrentDialogue()
{
	return CurrentDialogue;
}

void USI_DialogueManager::SetupBindings()
{
	// Get the HUD, get the dialogue box, bind u objects (need to make functions UFUNCTIONs)
}

bool USI_DialogueManager::HasNextOption()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::Next);
}

bool USI_DialogueManager::HasPreviousOption()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::Previous);
}

bool USI_DialogueManager::HasPressOption()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::Press);
}

bool USI_DialogueManager::HasTextOptions()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::TextOption);
}

bool USI_DialogueManager::HasItemOptions()
{
	return (CurrentDialogue != nullptr) && CurrentDialogue->HasEdgeOfType(EEdgeType::ItemOption);
}

bool USI_DialogueManager::CanEnterInterrogation()
{
	//return (GameInstance->GetPlayerMode() == EPlayerMode::PM_InterrogationMode && CurrentDialogue != nullptr && CurrentDialogue->bIsInterrogationDialogue);
	return false;
}

UDialogueSession* USI_DialogueManager::FindDialogue(USI_CaseData* Case, USI_PartData* Part)
{
	return nullptr;
}
