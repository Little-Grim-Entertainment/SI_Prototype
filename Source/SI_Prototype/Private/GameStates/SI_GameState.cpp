// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/SI_GameState.h"

#include "Characters/SI_CharacterManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveData/SI_SaveData_CharacterStates.h"
#include "Characters/Data/SI_CharacterData.h"

FSI_CharacterState* ASI_GameState::GetCharacterStateByTag(const FGameplayTag& InCharacterTag)
{
	FSI_CharacterState* CharacterStatePtr = CharacterStates.Find(InCharacterTag);
	if(!CharacterStatePtr)
	{
		USI_CharacterManager* CharacterManager = GetWorld()->GetSubsystem<USI_CharacterManager>();
		if(!IsValid(CharacterManager)) {return nullptr;}

		USI_CharacterData* CharacterData = CharacterManager->GetCharacterDataByTag(InCharacterTag);
		if(!IsValid(CharacterData)) {return nullptr;}

		FSI_CharacterState* NewCharacterState = new FSI_CharacterState(CharacterData);
		AddNewCharacterState(NewCharacterState);
		return NewCharacterState;
	}
	
	return CharacterStatePtr;
}

void ASI_GameState::AddNewCharacterState(FSI_CharacterState* InCharacterState)
{
	const TPair<FGameplayTag, FSI_CharacterState> NewCharacterStatePair = TPair<FGameplayTag, FSI_CharacterState>(InCharacterState->GetCharacterTag(), *InCharacterState);
	CharacterStates.Add(NewCharacterStatePair);
}

void ASI_GameState::BeginPlay()
{
	Super::BeginPlay();

	if(!LoadCharacterStates())
	{
		CreateCharacterStatesSaveFile();
	}
}

void ASI_GameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SaveCharacterStates();
}

bool ASI_GameState::CreateCharacterStatesSaveFile() const
{
	USI_SaveData_CharacterStates* CharacterStatesSave = Cast<USI_SaveData_CharacterStates>(UGameplayStatics::CreateSaveGameObject(USI_SaveData_CharacterStates::StaticClass()));
	if(!IsValid(CharacterStatesSave)) {return false;}

	CharacterStatesSave->CharacterStates = CharacterStates;
	return UGameplayStatics::SaveGameToSlot(CharacterStatesSave, "CharacterStates", 0);
}

bool ASI_GameState::SaveCharacterStates() const
{
	
	USI_SaveData_CharacterStates* CharacterStatesSave = Cast<USI_SaveData_CharacterStates>(UGameplayStatics::LoadGameFromSlot("CharacterStates", 0));
	if(!IsValid(CharacterStatesSave))
	{
		return CreateCharacterStatesSaveFile();
	}

	CharacterStatesSave->CharacterStates = CharacterStates;
	return UGameplayStatics::SaveGameToSlot(CharacterStatesSave, "CharacterStates", 0);
}

bool ASI_GameState::LoadCharacterStates()
{
	const USI_SaveData_CharacterStates* CharacterStatesSave = Cast<USI_SaveData_CharacterStates>(UGameplayStatics::CreateSaveGameObject(USI_SaveData_CharacterStates::StaticClass()));
	if(!IsValid(CharacterStatesSave)) {return false;}
	
	CharacterStates = CharacterStatesSave->CharacterStates;
	return true;
}
