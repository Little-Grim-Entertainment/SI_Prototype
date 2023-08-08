// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueManager.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"
#include "Characters/SI_CharacterManager.h"
#include "Data/Cases/SI_CaseManager.h"
#include "Data/Characters/SI_CharacterData.h"

void USI_DialogueManager::StartDialogue(USI_CharacterData* InCharacterData)
{
	// TO DO: Get GameInstance
	
	//GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	//if (!IsValid(GameInstance)) return;
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
	if (!CurrentCharacterData)
	{
		StartDefaultDialogue(CurrentCharacterData);
		return;
	}

	SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Dialogue, SITag_Player_State);
}

void USI_DialogueManager::ExitDialogue(int32 NewAngerLevel)
{
	check(CurrentCharacterData);
    USI_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	CurrentCharacterData->GetCurrentDialogueData(CaseManager).AngerLevel = NewAngerLevel;

	CurrentCharacterData = nullptr;

	//GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());
}

void USI_DialogueManager::OnNextPressed()
{

}

void USI_DialogueManager::OnPreviousPressed()
{

}

void USI_DialogueManager::OnPressPressed()
{

}

void USI_DialogueManager::OnTextOptionSelected(FText RelatedText)
{

}

void USI_DialogueManager::OnItemOptionSelected(UObject* RelatedItem)
{

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

void USI_DialogueManager::SetupBindings()
{
	// Get the HUD, get the dialogue box, bind u objects (need to make functions UFUNCTIONs)
}

bool USI_DialogueManager::HasNextOption()
{
	return false;
}

bool USI_DialogueManager::HasPreviousOption()
{
	return false;
}

bool USI_DialogueManager::HasPressOption()
{
	return false;
}

bool USI_DialogueManager::HasTextOptions()
{
	return false;
}

bool USI_DialogueManager::HasItemOptions()
{
	return false;
}

bool USI_DialogueManager::CanEnterInterrogation()
{
	//return (GameInstance->GetPlayerMode() == EPlayerMode::PM_InterrogationMode && CurrentDialogue != nullptr && CurrentDialogue->bIsInterrogationDialogue);
	return false;
}
