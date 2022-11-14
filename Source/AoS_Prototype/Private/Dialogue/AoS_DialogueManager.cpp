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
	check(CharacterManager);

	UAoS_CharacterData* CharacterData = CharacterManager->GetActiveCharacterData(CharacterName);
	if (!CharacterData || !CharacterData->CurrentDialogueData.RelevantDialogue)
	{
		StartDefaultDialogue(CharacterName);
		return;
	}

	ActiveDialogueContext = UDlgManager::StartDialogueWithDefaultParticipants(GetWorld(), CharacterData->CurrentDialogueData.RelevantDialogue);
	check(ActiveDialogueContext);
}


void UAoS_DialogueManager::StartDefaultDialogue(FText CharacterName)
{

}
