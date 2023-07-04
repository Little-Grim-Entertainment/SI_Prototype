// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_GameInstance.h"
#include "GameModes/SI_GameMode.h"
#include "Levels/SI_LevelManager.h"

USI_GameInstance::USI_GameInstance()
{	
	GameMode = nullptr;
}

void USI_GameInstance::Init()
{
	Super::Init();
	
	OnGameInstanceInitDelegate.Broadcast();
}


FOnGameInstanceInit& USI_GameInstance::OnGameInstanceInit()
{
	return OnGameInstanceInitDelegate;
}

FOnGameModeBeginPlay& USI_GameInstance::OnGameModeBeginPlay()
{
	return OnOnGameModeBeginPlayDelegate;
}

FOnPlayerStart& USI_GameInstance::OnPlayerStart()
{
	return OnOnPlayerStartDelegate;
}

FOnTagManagerInitialized& USI_GameInstance::OnTagManagerInitialized()
{
	return OnTagManagerInitializedDelegate;
}

ASI_GameMode* USI_GameInstance::GetGameMode()
{
	GameMode = Cast<ASI_GameMode>(GetWorld()->GetAuthGameMode());
	return GameMode;
}
