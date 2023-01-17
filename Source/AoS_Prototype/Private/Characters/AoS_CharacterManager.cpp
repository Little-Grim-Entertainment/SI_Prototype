// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_CharacterManager.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "AoS_GameInstance.h"
#include "Data/Cases/AoS_CaseManager.h"

void UAoS_CharacterManager::OnGameInstanceInit()
{
	if(!IsValid(GameInstance)){return;}

	GameInstance->GetCaseManager()->OnPartActivated.AddDynamic(this, &ThisClass::OnPartActivated);
	GameInstance->GetCaseManager()->OnPartComplete.AddDynamic(this, &ThisClass::OnPartCompleted);
}

UAoS_CharacterData* UAoS_CharacterManager::GetActiveCharacterData(FText CharacterName)
{
	return nullptr;
}

bool UAoS_CharacterManager::GetIsActiveCharacter(UAoS_CharacterData* InCharacterData)
{
	for (UAoS_CharacterData* CurrentCharacterData : ActiveCharactersData)
	{
		if (InCharacterData == CurrentCharacterData)
		{
			return true;
		}
	}
	return false;
}

void UAoS_CharacterManager::OnPartActivated(UAoS_Part* ActivatedPart)
{
	
}

void UAoS_CharacterManager::OnPartCompleted(UAoS_Part* CompletedPart)
{
	
}
