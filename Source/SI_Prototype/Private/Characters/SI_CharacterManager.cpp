// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterManager.h"
#include "Characters/Data/SI_CharacterData.h"
#include "Characters/SI_Nick.h"
#include "Characters/SI_Gizbo.h"
#include "SI_GameInstance.h"
#include "Cases/SI_CaseManager.h"
#include "Cases/Data/SI_PartData.h"
#include "Characters/Data/SI_CharacterList.h"
#include "GameStates/SI_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "SaveData/SI_SaveData_CharacterStates.h"

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

ASI_Nick* USI_CharacterManager::GetNick()
{
	return NickRef.Get();
}

ASI_Gizbo* USI_CharacterManager::GetGizbo()
{
	return GizboRef.Get();
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

FSI_CharacterState* USI_CharacterManager::GetCharacterStateByTag(const FGameplayTag& InCharacterTag, const ASI_Character* InCharacter)
{
	FSI_CharacterState* CharacterStatePtr = LoadedCharacterStates.Find(InCharacterTag);
	if(!CharacterStatePtr)
	{
		USI_CharacterData* CharacterData = GetCharacterDataByTag(InCharacterTag);
		if(!IsValid(CharacterData)) {return nullptr;}

		FSI_CharacterState* NewCharacterState = new FSI_CharacterState(CharacterData, InCharacter);
		AddNewCharacterState(NewCharacterState);
		return NewCharacterState;
	}
	
	return CharacterStatePtr;
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

void USI_CharacterManager::AddNewCharacterState(FSI_CharacterState* InCharacterState)
{
	const TPair<FGameplayTag, FSI_CharacterState> NewCharacterStatePair = TPair<FGameplayTag, FSI_CharacterState>(InCharacterState->GetCharacterTag(), *InCharacterState);
	LoadedCharacterStates.Add(NewCharacterStatePair);
}

bool USI_CharacterManager::CreateCharacterStatesSaveFile()
{
	USI_SaveData_CharacterStates* CharacterStatesSave = Cast<USI_SaveData_CharacterStates>(UGameplayStatics::CreateSaveGameObject(USI_SaveData_CharacterStates::StaticClass()));
	if(!IsValid(CharacterStatesSave)) {return false;}

	LoadedCharacterStates = CharacterStatesSave->CharacterStates;
	return UGameplayStatics::SaveGameToSlot(CharacterStatesSave, "CharacterStates", 0);
}

bool USI_CharacterManager::SaveCharacterStates() const
{
	USI_SaveData_CharacterStates* CharacterStatesSave = Cast<USI_SaveData_CharacterStates>(UGameplayStatics::LoadGameFromSlot("CharacterStates", 0));
	if(!IsValid(CharacterStatesSave)) {return false;}

	CharacterStatesSave->CharacterStates = LoadedCharacterStates;
	return UGameplayStatics::SaveGameToSlot(CharacterStatesSave, "CharacterStates", 0);
}

bool USI_CharacterManager::LoadCharacterStates()
{
	const USI_SaveData_CharacterStates* CharacterStatesSave = Cast<USI_SaveData_CharacterStates>(UGameplayStatics::LoadGameFromSlot("CharacterStates", 0));
	if(!IsValid(CharacterStatesSave))
	{
		return CreateCharacterStatesSaveFile();
	}

	LoadedCharacterStates = CharacterStatesSave->CharacterStates;
	return true;
}

void USI_CharacterManager::SetNickRef(ASI_Nick* InNick)
{
	NickRef = InNick;
}

void USI_CharacterManager::SetGizboRef(ASI_Gizbo* InGizbo)
{
	GizboRef = InGizbo;
}

void USI_CharacterManager::OnPartActivated(USI_PartData* ActivatedPart)
{
	
}

void USI_CharacterManager::OnPartCompleted(USI_PartData* CompletedPart)
{
	
}
