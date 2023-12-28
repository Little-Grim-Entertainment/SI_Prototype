// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterManager.h"
#include "Characters/Data/SI_CharacterData.h"
#include "SI_GameInstance.h"
#include "Cases/SI_CaseManager.h"
#include "Characters/Data/SI_CharacterList.h"

void USI_CharacterManager::OnGameInstanceInit()
{
	if(!IsValid(GameInstance)){return;}

	USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	if(CaseManager->OnPartActivated().IsAlreadyBound(this, &ThisClass::OnPartActivated) && CaseManager->OnPartComplete().IsAlreadyBound(this, &ThisClass::OnPartCompleted)) {return;}
	
	CaseManager->OnPartActivated().AddDynamic(this, &ThisClass::OnPartActivated);
	CaseManager->OnPartComplete().AddDynamic(this, &ThisClass::OnPartCompleted);
}

USI_CharacterData* USI_CharacterManager::GetActiveCharacterData(const FGameplayTag& CharacterTag)
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

TSubclassOf<ASI_Character> USI_CharacterManager::GetCharacterClassByTag(const FGameplayTag& InCharacterTag)
{
	static ConstructorHelpers::FObjectFinder<USI_CharacterList> CharacterListObj(TEXT("/Game/Content/SI/Data/DA_CharacterList"));
	USI_CharacterList* CharacterList = CharacterListObj.Object;
	if(!IsValid(CharacterList)){return nullptr;}

	USI_CharacterData* CharacterData = CharacterList->GetCharacterDataByTag(InCharacterTag);
	if(!IsValid(CharacterData)) {return nullptr;}

	return CharacterData->CharacterClass;
}

void USI_CharacterManager::OnPartActivated(USI_PartData* ActivatedPart)
{
	
}

void USI_CharacterManager::OnPartCompleted(USI_PartData* CompletedPart)
{
	
}
