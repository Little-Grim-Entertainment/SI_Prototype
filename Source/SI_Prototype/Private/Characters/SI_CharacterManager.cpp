// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterManager.h"
#include "Data/Characters/SI_CharacterData.h"
#include "SI_GameInstance.h"
#include "Data/Cases/SI_CaseManager.h"

DEFINE_LOG_CATEGORY(LogSI_CharacterManager);

void USI_CharacterManager::OnGameInstanceInit()
{
	if(!IsValid(GameInstance)){return;}

	USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	if(CaseManager->OnPartActivated().IsAlreadyBound(this, &ThisClass::OnPartActivated) && CaseManager->OnPartComplete().IsAlreadyBound(this, &ThisClass::OnPartCompleted)) {return;}
	
	CaseManager->OnPartActivated().AddDynamic(this, &ThisClass::OnPartActivated);
	CaseManager->OnPartComplete().AddDynamic(this, &ThisClass::OnPartCompleted);
}

USI_CharacterData* USI_CharacterManager::GetActiveCharacterData(FText CharacterName)
{
	return nullptr;
}

bool USI_CharacterManager::GetIsActiveCharacter(USI_CharacterData* InCharacterData)
{
	for (USI_CharacterData* CurrentCharacterData : ActiveCharactersData)
	{
		if (InCharacterData == CurrentCharacterData)
		{
			return true;
		}
	}
	return false;
}

void USI_CharacterManager::OnPartActivated(USI_PartData* ActivatedPart)
{
	
}

void USI_CharacterManager::OnPartCompleted(USI_PartData* CompletedPart)
{
	
}
