// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterManager.h"
#include "Characters/Data/SI_CharacterData.h"
#include "SI_GameInstance.h"
#include "Cases/SI_CaseManager.h"
#include "Cases/Data/SI_PartData.h"
#include "Characters/Data/SI_CharacterList.h"
#include "GameStates/SI_GameState.h"

void USI_CharacterManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

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

USI_CharacterData* USI_CharacterManager::GetCharacterDataByTag(const FGameplayTag& InCharacterTag)
{
	if(!IsValid(GameInstance)){return nullptr;}

	USI_CharacterList* CharacterList = GameInstance->CharacterList;
	if(!IsValid(CharacterList)){return nullptr;}

	return CharacterList->GetCharacterDataByTag(InCharacterTag);
}

FSI_CharacterState* USI_CharacterManager::GetCharacterStateByTag(const FGameplayTag& InCharacterTag)
{
	UWorld* World = GetWorld();
	if(!IsValid(World)){return nullptr;}
	
	ASI_GameState* GameState = Cast<ASI_GameState>(World->GetGameState());
	if(!IsValid(GameState)) {return nullptr;}

	return GameState->GetCharacterStateByTag(InCharacterTag);
}

bool USI_CharacterManager::IsActiveCharacter(USI_CharacterData* InCharacterData)
{
	USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	if(!IsValid(CaseManager)) {return false;}
	
	USI_PartData* CurrentPart = CaseManager->GetActivePart();
	if(!IsValid(CurrentPart)) {return false;}
	
	for (TSoftObjectPtr<USI_CharacterData> CurrentCharacterData : CurrentPart->ActiveCharacters)
	{
		USI_CharacterData* CurrentCharacterDataPtr = CurrentCharacterData.Get();
		if (CurrentCharacterDataPtr == InCharacterData)
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
