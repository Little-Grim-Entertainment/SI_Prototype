// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"
#include "AoS_GameInstance.h"
#include "Data/Maps/AoS_MapList.h"
#include "Data/Maps/AoS_MapData.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"


UAoS_LevelManager::UAoS_LevelManager()
{
	static ConstructorHelpers::FObjectFinder<UAoS_MapData> MainMenuAsset(TEXT("/Game/AoS/Maps/Menus/DA_MainMenu"));
	MainMenu = MainMenuAsset.Object;
}

void UAoS_LevelManager::OnGameInstanceInit()
{
	Super::OnGameInstanceInit();
	OnGameLoaded();
}

void UAoS_LevelManager::LoadLevel(UAoS_MapData* InLevelToLoad, bool bAllowDelay, bool bShouldFade, FString InPlayerStartTag)
{
	if (!InLevelToLoad) {return;}
	
	bLoadShouldFade = bShouldFade;
	PlayerStartTag = InPlayerStartTag;
	LevelToLoad = InLevelToLoad;
	LevelLoadDelay = GameInstance->LevelLoadDelay;
	
	OnBeginLevelLoad.Broadcast(InLevelToLoad, bLoadShouldFade);
	GameInstance->SetPlayerMode(EPlayerMode::PM_LevelLoadingMode);

	if (GetWorld() != InLevelToLoad->Map.Get())
	{
		if (bAllowDelay)
		{
			GetWorld()->GetTimerManager().SetTimer(LoadDelayHandle, this, &UAoS_LevelManager::ExecuteLevelLoad, LevelLoadDelay);
		}
		else
		{
			ExecuteLevelLoad();
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

EMapType UAoS_LevelManager::GetCurrentMapType() const
{
	return CurrentMapType;
}

UAoS_MapData* UAoS_LevelManager::GetCurrentMap() const
{
	return CurrentLevel;
}

FString UAoS_LevelManager::GetCurrentMapName() const
{
	return CurrentLevel->MapName;
}

void UAoS_LevelManager::ExecuteLevelLoad()
{
	if (IsValid(LevelToLoad))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),LevelToLoad->Map, true, PlayerStartTag);
	}
}

void UAoS_LevelManager::LevelLoaded()
{
	if(!IsValid(LevelToLoad))
	{
		OnGameLoaded();
		if(!IsValid(LevelToLoad)){return;}
	}
	
	CurrentLevel = LevelToLoad;
	if (CurrentLevel->MapType == EMapType::MT_Menu)
	{
		GameInstance->SetPlayerMode(EPlayerMode::PM_MainMenuMode);
	}
	else
	{
		GameInstance->SetPlayerMode(EPlayerMode::PM_ExplorationMode);
	}
	
	OnLevelLoaded.Broadcast(CurrentLevel, bLoadShouldFade);
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

void UAoS_LevelManager::OnGameLoaded()
{
	UWorld* World = GetWorld();
	FString MapName = World->GetName();
	MapName = UKismetStringLibrary::Replace(MapName, "M_", "DA_");
	UAoS_MapData* StartingMap = GetMapFromName(MapName);
	
	if (IsValid(StartingMap))
	{
		LevelToLoad = StartingMap;
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
