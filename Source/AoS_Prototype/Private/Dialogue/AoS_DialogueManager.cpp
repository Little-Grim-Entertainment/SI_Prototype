// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/AoS_DialogueManager.h"
#include "DlgContext.h"
#include "DlgDialogue.h"
#include "DlgManager.h"
#include "AoS_GameInstance.h"
#include "Characters/AoS_CharacterManager.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "Kismet/GameplayStatics.h"


FOnBeginDialogue& UAoS_DialogueManager::GetOnBeginDialogue()
{
	return OnBeginDialogueDelegate;
}

void UAoS_DialogueManager::StartDialogue(FText CharacterName)
{
	if (!IsValid(GameInstance)) return;
	UAoS_CharacterManager* CharacterManager = GameInstance->GetSubsystem<UAoS_CharacterManager>();
	if (!IsValid(CharacterManager))
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterManager not found!"));
		StartDefaultDialogue(CharacterName);
		return;
	}

	UAoS_CharacterData* CharacterData = CharacterManager->GetActiveCharacterData(CharacterName);
	if (!CharacterData || !CharacterData->CurrentDialogueData.RelevantDialogue)
	{
		StartDefaultDialogue(CharacterName);
		return;
	}

	ActiveDialogueContext = UDlgManager::StartDialogueWithDefaultParticipants(GetWorld(), CharacterData->CurrentDialogueData.RelevantDialogue);
	if (!IsValid(ActiveDialogueContext))
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue not started correctly."));
		return;
	}

	GameInstance->SetPlayerMode(EPlayerMode::PM_DialogueMode);
	OnBeginDialogueDelegate.Broadcast(ActiveDialogueContext);
}


void UAoS_DialogueManager::StartDefaultDialogue(FText CharacterName)
{
	// find default dialogue


	GameInstance->SetPlayerMode(EPlayerMode::PM_DialogueMode);
	OnBeginDialogueDelegate.Broadcast(ActiveDialogueContext);
}

void UAoS_DialogueManager::OnInterrogationPressed()
{
	GameInstance->SetPlayerMode(EPlayerMode::PM_InterrogationMode);
}