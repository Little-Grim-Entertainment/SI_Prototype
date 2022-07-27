// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"

#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "UI/AoS_UIManager.h"


UAoS_LevelManager::UAoS_LevelManager()
{
	
}

void UAoS_LevelManager::LoadLevel(const TSoftObjectPtr<UWorld> InLevelToLoad)
{
	if (World && GameInstance)
	{
		TArray<ULevelStreaming*> StreamingLevels = World->GetStreamingLevels();
		
		for (ULevelStreaming* CurrentLevel : StreamingLevels)
		{
			if (CurrentLevel->GetWorldAsset().GetAssetName() == InLevelToLoad.GetAssetName())
			{
				LevelToLoad = CurrentLevel;
				break;
			}
		}
		
		if (LevelToLoad)
		{
			OnBeginLevelLoad.Broadcast(LevelToLoad);

			if (CurrentStreamingLevel)
			{
				LevelToUnload = CurrentStreamingLevel;
				ExecuteLevelUnload(LevelToUnload);
			}
			else
			{
				ExecuteLevelLoad(LevelToLoad);
			}
			UIManager->DisplayLoadingScreen(true);
		}
	}
}

void UAoS_LevelManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	World = GetWorld();
	if (World)
	{
		GameInstance = Cast<UAoS_GameInstance>(World->GetGameInstance());
		if (GameInstance)
		{
			
			UIManager = GameInstance->GetSubsystem<UAoS_UIManager>();
		}
	}
}

void UAoS_LevelManager::ExecuteLevelLoad(const ULevelStreaming* InLevelToLoad)
{
	FLatentActionInfo LoadInfo;
	LoadInfo.CallbackTarget = this;
	LoadInfo.ExecutionFunction = "LevelLoaded";
	LoadInfo.UUID = 0;
	LoadInfo.Linkage = 0;
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(World, InLevelToLoad->GetWorldAsset(), true, false, LoadInfo);
}

void UAoS_LevelManager::ExecuteLevelUnload(const ULevelStreaming* InLevelToUnload)
{
	FLatentActionInfo UnloadInfo;
	UnloadInfo.CallbackTarget = this;
	UnloadInfo.ExecutionFunction = "LevelUnloaded";
	UnloadInfo.UUID = 0;
	UnloadInfo.Linkage = 0;
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(World, InLevelToUnload->GetWorldAsset(), UnloadInfo, false);
}

void UAoS_LevelManager::LevelUnloaded()
{
	OnLevelUnloaded.Broadcast(LevelToUnload);
	ExecuteLevelLoad(LevelToLoad);
}

void UAoS_LevelManager::LevelLoaded()
{
	TArray<ULevelStreaming*> StreamingLevels = World->GetStreamingLevels();
	for (ULevelStreaming* CurrentLevel : StreamingLevels)
	{
		if (CurrentLevel->IsLevelLoaded())
		{
			CurrentStreamingLevel = CurrentLevel;
			OnLevelLoaded.Broadcast(CurrentLevel);
			GameInstance->SpawnPlayer();
		}
	}
	UIManager->DisplayLoadingScreen(false);
}
