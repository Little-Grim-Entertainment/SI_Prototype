// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"

#include "Kismet/GameplayStatics.h"
#include "UI/AoS_UIManager.h"

UAoS_LevelManager::UAoS_LevelManager()
{
	
}

void UAoS_LevelManager::LoadLevel(TSoftObjectPtr<UWorld> LevelToLoad)
{
	if (World)
	{
		UIManager->DisplayLoadingScreen();
		const FLatentActionInfo LatentActionInfo;
		LatentActionInfo.CallbackTarget = *this;
		
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(World, CurrentStreamingLevel, LatentActionInfo, false);
		
	}
}

void UAoS_LevelManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	World = GetWorld();
	if (World)
	{
		GameInstance = World->GetGameInstance();
		if (GameInstance)
		{
			UIManager = GameInstance->GetSubsystem<UAoS_UIManager>();
		}
	}
}

void UAoS_LevelManager::SetCurrentStreamingLevel(TSoftObjectPtr<UWorld> LevelToSet)
{
	CurrentStreamingLevel = LevelToSet;
}
