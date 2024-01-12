// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueManager.h"
#include "Characters/Data/SI_CharacterData.h"

void USI_DialogueManager::StartDialogue(const FGameplayTag& InCharacterTag)
{
	
}

void USI_DialogueManager::ExitDialogue(int32 NewAngerLevel)
{
	
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
