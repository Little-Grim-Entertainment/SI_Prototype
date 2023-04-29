// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"
#include "GameModes/AoS_GameMode.h"
#include "Levels/AoS_LevelManager.h"

UAoS_GameInstance::UAoS_GameInstance()
{	
	GameMode = nullptr;
}

void UAoS_GameInstance::Init()
{
	Super::Init();
	
	OnGameInstanceInit.Broadcast();

	/*UAoS_LevelManager* LevelManager = GetSubsystem<UAoS_LevelManager>();
	if(IsValid(LevelManager))
	{
		FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(LevelManager, &UAoS_LevelManager::LevelLoaded);
	}*/
}

FOnTagManagerInitialized& UAoS_GameInstance::OnTagManagerInitialized()
{
	return OnTagManagerInitializedDelegate;
}

AAoS_GameMode* UAoS_GameInstance::GetGameMode()
{
	return Cast<AAoS_GameMode>(GetWorld()->GetAuthGameMode());
}
