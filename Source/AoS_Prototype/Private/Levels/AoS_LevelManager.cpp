// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"

#include "Data/AoS_MapList.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"


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
		}
	}
}

TArray<FString> UAoS_LevelManager::GetMapNames()
{
	TArray<FString> MapNames;

	if (!GameInstance->MapList)
	{
		const FString NoMaps = "Map List Not Found.";
		MapNames.Add(NoMaps);
	}
	else
	{
		if (GameInstance->MapList->Maps.Num() > 0)
		{
			for (const TSoftObjectPtr<UWorld> CurrentMap : GameInstance->MapList->Maps)
			{
				MapNames.AddUnique(CurrentMap.GetAssetName());
			}
		}
	}

	return MapNames;
}

TSoftObjectPtr<UWorld> UAoS_LevelManager::GetMapFromName(FString MapName)
{
	if (!GameInstance) {return nullptr;}
	for (TSoftObjectPtr<UWorld> CurrentMap : GameInstance->MapList->Maps)
	{
		if (MapName == CurrentMap.GetAssetName())
		{
			return CurrentMap;
		}
	}
	return nullptr;
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
		}
	}
}
