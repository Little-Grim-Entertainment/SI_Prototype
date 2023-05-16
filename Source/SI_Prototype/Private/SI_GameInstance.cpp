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
	
	OnGameInstanceInit.Broadcast();

	/*USI_LevelManager* LevelManager = GetSubsystem<USI_LevelManager>();
	if(IsValid(LevelManager))
	{
		FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(LevelManager, &USI_LevelManager::LevelLoaded);
	}*/
}

FOnTagManagerInitialized& USI_GameInstance::OnTagManagerInitialized()
{
	return OnTagManagerInitializedDelegate;
}

ASI_GameMode* USI_GameInstance::GetGameMode()
{
	return Cast<ASI_GameMode>(GetWorld()->GetAuthGameMode());
}
