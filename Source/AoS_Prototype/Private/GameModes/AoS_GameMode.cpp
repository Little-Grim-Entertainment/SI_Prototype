// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/AoS_GameMode.h"

#include "Levels/AoS_LevelManager.h"

AAoS_GameMode::AAoS_GameMode()
{

}

void AAoS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (IsValid(LevelManager))
	{
		LevelManager->LevelLoaded();
	}
}
