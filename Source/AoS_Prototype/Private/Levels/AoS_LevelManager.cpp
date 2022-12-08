// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"
#include "AoS_GameInstance.h"
#include "Characters/AoS_GizboManager.h"
#include "Cinematics/AoS_CinematicsManager.h"
#include "Controllers/AoS_PlayerController.h"
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

void UAoS_LevelManager::OnInitGame()
{
	Super::OnInitGame();

	UWorld* World = GetWorld();
	if (!World){return;}
	
	FString MapName = World->GetName();
	MapName = UKismetStringLibrary::Replace(MapName, "M_", "DA_");
	UAoS_MapData* StartingMap = GetMapFromName(MapName);
	
	if (IsValid(StartingMap))
	{
		LevelToLoad = StartingMap;
	}
}

void UAoS_LevelManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	LevelLoaded();
}

void UAoS_LevelManager::OnPlayerStart()
{
	Super::OnPlayerStart();

	AAoS_PlayerController* PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(PlayerController))
	{
		PlayerController->PlayerCameraManager->StartCameraFade(0, 1, .01, FLinearColor::Black, false, true);
	}
	
}

void UAoS_LevelManager::LoadLevel(UAoS_MapData* InLevelToLoad,  FString InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	if (!InLevelToLoad) {return;}

	LevelToLoad = InLevelToLoad;
	bLoadShouldFade = bShouldFade;

	UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>();
	if(IsValid(GizboManager))
	{
		GizboManager->SetGizboStartTag(InPlayerStartTag + "Gizbo");
	}
	
	OnBeginLevelLoad.Broadcast(InLevelToLoad, bShouldFade);
	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_LevelLoadingMode);
	
	if (GetWorld() != InLevelToLoad->Map.Get())
	{
		if (bAllowDelay)
		{
			LoadDelayDelegate.BindUObject(this, &ThisClass::LoadLevel, InLevelToLoad, InPlayerStartTag, false, bShouldFade);
			GetWorld()->GetTimerManager().SetTimer(LoadDelayHandle, LoadDelayDelegate, LevelLoadDelay, false);
		}
		else
		{
			if (IsValid(InLevelToLoad))
			{
				UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),InLevelToLoad->Map, true, InPlayerStartTag);
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
	if (!IsValid(CurrentLevel)) {return "";}
	return CurrentLevel->MapName;
}

bool UAoS_LevelManager::GetLevelHasLoaded() const
{
	return bLevelHasLoaded;
}

void UAoS_LevelManager::LevelLoaded()
{
	if(!IsValid(LevelToLoad))
	{
		OnInitGame();
		if(!IsValid(LevelToLoad)){return;}
	}
	
	CurrentLevel = LevelToLoad;
	if (CurrentLevel->MapType == EMapType::MT_Menu)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_MainMenuMode);
	}
	else
	{
		if (LevelToLoad->HasOpeningVideo() && !LevelToLoad->OpeningVideoHasPlayed())
		{
			UAoS_CinematicsManager* CinematicsManager =  GetWorld()->GetSubsystem<UAoS_CinematicsManager>();
			if (IsValid(CinematicsManager))
			{
				CinematicsManager->PlayVideo(LevelToLoad->GetOpeningVideo(), false);
			}
		}
		else
		{
			GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);	
		}
	}
	
	bLevelHasLoaded = true;
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

void UAoS_LevelManager::UpdateMapType(EMapType InMapType)
{
	if (InMapType != CurrentMapType)
	{
		CurrentMapType = InMapType;
		OnMapTypeChanged.Broadcast(InMapType);
	}
}
