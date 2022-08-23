// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"
#include "AoS_GameInstance.h"
#include "Data/AoS_MapList.h"
#include "Data/AoS_MapData.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"


UAoS_LevelManager::UAoS_LevelManager()
{
	static ConstructorHelpers::FObjectFinder<UAoS_MapData> MainMenuAsset(TEXT("/Game/AoS/Maps/Menus/DA_MainMenu"));
	MainMenu = MainMenuAsset.Object;
}

void UAoS_LevelManager::LoadLevel(UAoS_MapData* InLevelToLoad, bool bAllowDelay)
{
	if (!InLevelToLoad) {return;}

	OnBeginLevelLoad.Broadcast(InLevelToLoad);
	
	if (World && GameInstance)
	{
		TArray<ULevelStreaming*> StreamingLevels = World->GetStreamingLevels();
		
		for (ULevelStreaming* CurrentLevel : StreamingLevels)
		{
			if (!CurrentStreamingLevel && CurrentLevel->IsLevelLoaded())
			{
				if (UAoS_MapData* CurrentLevelData = GetMapDataFromStreamingLevel(CurrentLevel))
				{
					LevelToUnload = CurrentLevelData;
					ExecuteLevelUnload(LevelToUnload);
				}
			}
			if (CurrentLevel->GetWorldAsset().GetAssetName() == InLevelToLoad->Map.GetAssetName())
			{
				InLevelToLoad->SetStreamingLevelRef(CurrentLevel);
				LevelToLoad = InLevelToLoad;
				break;
			}
		}
		
		if (LevelToLoad)
		{
			if (bAllowDelay)
			{
				GetWorld()->GetTimerManager().SetTimer(LoadDelayHandle, this, &UAoS_LevelManager::PostLoadDelay, 0.5f);
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
		if (GameInstance->MapList->GetAllMaps().Num() > 0)
		{
			for (const TSoftObjectPtr<UWorld> CurrentMap : GameInstance->MapList->GetAllMaps())
			{
				MapNames.AddUnique(CurrentMap.GetAssetName());
			}
		}
	}

	return MapNames;
}

UAoS_MapData* UAoS_LevelManager::GetMapFromName(FString MapName)
{
	if (!GameInstance) {return nullptr;}
	for (UAoS_MapData* CurrentMap : GameInstance->MapList->GetAllMaps())
	{
		if (MapName == CurrentMap->GetName())
		{
			return CurrentMap;
		}
	}
	return nullptr;
}

EMapType UAoS_LevelManager::GetCurrentMapType()
{
	return CurrentMapType;
}

void UAoS_LevelManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	World = GetWorld();
	if (World)
	{
		GameInstance = Cast<UAoS_GameInstance>(World->GetGameInstance());
	}
}

void UAoS_LevelManager::ExecuteLevelLoad(const UAoS_MapData* InLevelToLoad)
{
	FLatentActionInfo LoadInfo;
	LoadInfo.CallbackTarget = this;
	LoadInfo.ExecutionFunction = "LevelLoaded";
	LoadInfo.UUID = 0;
	LoadInfo.Linkage = 0;
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(World, InLevelToLoad->GetStreamingLevelRef()->GetWorldAsset(), true, false, LoadInfo);
}

void UAoS_LevelManager::ExecuteLevelUnload(const UAoS_MapData* InLevelToUnload)
{
	FLatentActionInfo UnloadInfo;
	UnloadInfo.CallbackTarget = this;
	UnloadInfo.ExecutionFunction = "LevelUnloaded";
	UnloadInfo.UUID = 0;
	UnloadInfo.Linkage = 0;
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(World, InLevelToUnload->GetStreamingLevelRef()->GetWorldAsset(), UnloadInfo, false);
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
			if (UAoS_MapData* CurrentLevelData = GetMapDataFromStreamingLevel(CurrentLevel))
			{
				CurrentStreamingLevel = CurrentLevelData;
				UpdateMapType(CurrentStreamingLevel->MapType);
				OnLevelLoaded.Broadcast(CurrentStreamingLevel);
				return;
			}
		}
	}
}

UAoS_MapData* UAoS_LevelManager::GetMapDataFromStreamingLevel(ULevelStreaming* InStreamingLevel)
{
	for (UAoS_MapData* CurrentMapData : GameInstance->MapList->GetAllMaps())
	{
		if (CurrentMapData->Map.GetAssetName() == InStreamingLevel->GetWorldAsset().GetAssetName())
		{
			CurrentMapData->SetStreamingLevelRef(InStreamingLevel);
			return CurrentMapData;
		}
	}
	return nullptr;
}

void UAoS_LevelManager::PostLoadDelay()
{
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

void UAoS_LevelManager::LoadMainMenu()
{
	if(MainMenu)
	{
		GameInstance->GetLevelManager()->LoadLevel(MainMenu, false);
	}
}

void UAoS_LevelManager::LevelManagerOnGameInstanceInit()
{
	if (!GetCurrentStreamingLevel())
	{
		LoadMainMenu();
	}
}

void UAoS_LevelManager::UpdateMapType(EMapType InMapType)
{
	if (InMapType != CurrentMapType)
	{
		CurrentMapType = InMapType;
		OnMapTypeChanged.Broadcast(InMapType);
	}
}
