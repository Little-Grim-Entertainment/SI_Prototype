// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"
#include "AoS_GameInstance.h"
#include "Data/AoS_MapData.h"
#include "Data/AoS_MapList.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"


UAoS_LevelManager::UAoS_LevelManager()
{
	static ConstructorHelpers::FObjectFinder<UAoS_MapData> MainMenuAsset(TEXT("/Game/AoS/Maps/Menus/DA_MainMenu"));
	MainMenu = MainMenuAsset.Object;
}

void UAoS_LevelManager::LoadLevel(UAoS_MapData* InLevelToLoad)
{
	if (!InLevelToLoad) {return;}
	
	if (World && GameInstance)
	{
		TArray<ULevelStreaming*> StreamingLevels = World->GetStreamingLevels();
		
		for (ULevelStreaming* CurrentLevel : StreamingLevels)
		{
			if (!CurrentStreamingLevel && CurrentLevel->IsLevelLoaded())
			{
				FLatentActionInfo UnloadInfo;
				UnloadInfo.UUID = 0;
				UnloadInfo.Linkage = 0;
				UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(World, CurrentLevel, UnloadInfo, false);
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
			OnBeginLevelLoad.Broadcast(InLevelToLoad);

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

void UAoS_LevelManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	World = GetWorld();
	if (World)
	{
		GameInstance = Cast<UAoS_GameInstance>(World->GetGameInstance());
		if (!CurrentStreamingLevel)
		{
			if (MainMenu)
			{
				LoadLevel(MainMenu);
			}
		}
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
			for (UAoS_MapData* CurrentMapData : GameInstance->MapList->GetAllMaps())
			{
				if (CurrentMapData->Map.GetAssetName() == CurrentLevel->GetWorldAsset().GetAssetName())
				{
					CurrentStreamingLevel = CurrentMapData;
					CurrentStreamingLevel->SetStreamingLevelRef(CurrentLevel);
					if (CurrentStreamingLevel->MapType == EMapType::MT_Menu)
					{
						GameInstance->SetIsInMenu(true);
					}
					else
					{
						GameInstance->SetIsInMenu(false);
					}
					OnLevelLoaded.Broadcast(CurrentStreamingLevel);
					return;
				}
			}
		}
	}
}
