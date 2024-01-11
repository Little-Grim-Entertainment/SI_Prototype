// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/SI_GameState.h"

#include "Characters/SI_CharacterManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveData/SI_SaveData_CharacterStates.h"
#include "Characters/Data/SI_CharacterData.h"


void ASI_GameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);
}
