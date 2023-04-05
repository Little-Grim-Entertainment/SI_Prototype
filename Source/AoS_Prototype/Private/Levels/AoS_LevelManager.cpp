// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/AoS_LevelManager.h"
#include "AoS_GameInstance.h"
#include "LevelSequencePlayer.h"
#include "Levels/AoS_MapGameplayTagLibrary.h"
#include "Characters/AoS_GizboManager.h"
#include "Media/AoS_MediaManager.h"
#include "Controllers/AoS_PlayerController.h"
#include "Data/Maps/AoS_MapList.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "GameModes/AoS_GameMode.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "MediaPlayer.h"


using namespace AoS_MapGameplayTagLibrary;

UAoS_LevelManager::UAoS_LevelManager()
{
	static ConstructorHelpers::FObjectFinder<UAoS_MapData> MainMenuAsset(TEXT("/Game/AoS/Maps/Menus/DA_MainMenu"));
	MainMenu = MainMenuAsset.Object;
}

void UAoS_LevelManager::OnInitGame()
{
	Super::OnInitGame();

	// MainMenu has been loaded at this point
	
	InitializeMapStates();
}

void UAoS_LevelManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	LevelLoaded();
}

void UAoS_LevelManager::OnPlayerStart()
{
	Super::OnPlayerStart();

	const AAoS_PlayerController* PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(PlayerController))
	{
		PlayerController->PlayerCameraManager->StartCameraFade(0, 1, .01, FLinearColor::Black, false, true);
	}
}

void UAoS_LevelManager::InitializeMapStates()
{
	const AAoS_GameMode* GameMode = Cast<AAoS_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) {return;}
	if (!IsValid(GameMode->MapList)) {return;}
	
	TArray<UAoS_MapData*> AllMaps = GameMode->MapList->GetAllMaps();
	
	for (UAoS_MapData* CurrentMapData : AllMaps)
	{
		if (!IsValid(CurrentMapData)) {continue;}

		MapStates.Add(FAoS_MapState(CurrentMapData));
	}
}

void UAoS_LevelManager::LoadLevelByTag(const FGameplayTag InLevelToLoadTag,  FString InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	FAoS_MapState& MapStateToLoad = GetMapStateByTag(InLevelToLoadTag);
	
	if (!MapStateToLoad.GetMapData()) {return;}
	if (LoadDelayDelegate.IsBound()){LoadDelayDelegate.Unbind();}

	UAoS_MediaManager* MediaManager =  GetWorld()->GetSubsystem<UAoS_MediaManager>();
	if (IsValid(MediaManager) && !MediaManager->HasMediaPlayed(LoadedMapState->GetLoadedOutroMedia()))
	{
		MediaManager->PlayMedia(LoadedMapState->GetLoadedOutroMedia(), LoadedMapState->GetOutroSettings());
		LoadLevelOnMediaComplete(MapStateToLoad, LoadedMapState->GetLoadedOutroMedia(), InPlayerStartTag, bAllowDelay, bShouldFade);

		return;
	}
	
	LevelStateToLoad = &MapStateToLoad;
	bLoadShouldFade = bShouldFade;
	bLevelHasLoaded = false;

	UAoS_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_GizboManager>();
	if(IsValid(GizboManager))
	{
		FString GizboStartTag = InPlayerStartTag;
		GizboStartTag = UKismetStringLibrary::Replace(GizboStartTag, "Nick_", "Gizbo_");
		GizboManager->SetGizboStartTag(GizboStartTag);
	}
	
	OnBeginLevelLoad.Broadcast(MapStateToLoad.GetMapData(), bShouldFade);
	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_LevelLoadingMode);
	
	if (GetWorld() != MapStateToLoad.GetMapData()->Map.Get())
	{
		if (bAllowDelay)
		{
			LoadDelayDelegate.BindUObject(this, &ThisClass::LoadLevelByTag, MapStateToLoad.GetMapData()->MapTag, InPlayerStartTag, false, bShouldFade);
			GetWorld()->GetTimerManager().SetTimer(LoadDelayHandle, LoadDelayDelegate, GameInstance->LevelLoadDelay, false);
		}
		else
		{
			if (IsValid(MapStateToLoad.GetMapData()))
			{
				
				if (LoadedMapState->IsStateValid())
				{
					OnLevelUnloaded.Broadcast(LoadedMapState->GetMapData());
				}
				
				UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),LevelStateToLoad->GetMapData()->Map, true, InPlayerStartTag);
			}
		}
	}
}

void UAoS_LevelManager::LoadLevelOnMediaComplete(const FAoS_MapState& InLevelToLoad, UAoS_MediaDataAsset* InMediaToPlay, FString InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	if (const UAoS_CinematicDataAsset* CinematicDataAsset = Cast<UAoS_CinematicDataAsset>(InMediaToPlay))
	{
		LoadLevelOnCinematicComplete(InLevelToLoad, CinematicDataAsset, InPlayerStartTag, bAllowDelay, bShouldFade);
	}
	else if (const UAoS_VideoDataAsset* VideoDataAsset = Cast<UAoS_VideoDataAsset>(InMediaToPlay))
	{
		LoadLevelOnVideoComplete(InLevelToLoad, VideoDataAsset, InPlayerStartTag, bAllowDelay, bShouldFade);
	}
}

void UAoS_LevelManager::LoadLevelOnVideoComplete(const FAoS_MapState& InLevelToLoad, const UAoS_VideoDataAsset* InVideoToPlay, FString InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	GameInstance->SetPreviousPlayerMode(EPlayerMode::PM_LevelLoadingMode);

	const FGameplayTag& LevelToLoadTag = InLevelToLoad.GetMapData()->MapTag;
	
	LoadDelayDelegate.BindUObject(this, &UAoS_LevelManager::LoadLevelByTag, LevelToLoadTag, InPlayerStartTag, bAllowDelay, bShouldFade);
	InVideoToPlay->MediaPlayer->OnEndReached.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
	InVideoToPlay->MediaPlayer->OnMediaClosed.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
}

void UAoS_LevelManager::LoadLevelOnCinematicComplete(const FAoS_MapState& InLevelToLoad, const UAoS_CinematicDataAsset* InCinematicToPlay, FString InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	GameInstance->SetPreviousPlayerMode(EPlayerMode::PM_LevelLoadingMode);

	const FGameplayTag& LevelToLoadTag = InLevelToLoad.GetMapData()->MapTag;

	LoadDelayDelegate.BindUObject(this, &UAoS_LevelManager::LoadLevelByTag, LevelToLoadTag, InPlayerStartTag, bAllowDelay, bShouldFade);
	InCinematicToPlay->CinematicPlayer->OnFinished.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnCinematicComplete);
	InCinematicToPlay->CinematicPlayer->OnStop.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnCinematicComplete);
}

void UAoS_LevelManager::ExecuteLoadLevelOnVideoComplete()
{
	LoadDelayDelegate.Execute();
	LoadDelayDelegate.Unbind();
}

void UAoS_LevelManager::ExecuteLoadLevelOnCinematicComplete()
{
	LoadDelayDelegate.Execute();
	LoadDelayDelegate.Unbind();
}

UAoS_MapData* UAoS_LevelManager::GetCurrentMap() const
{
	return LoadedMapState->GetMapData();
}

bool UAoS_LevelManager::GetLevelHasLoaded() const
{
	return bLevelHasLoaded;
}

FAoS_MapState& UAoS_LevelManager::GetMapStateByTag(const FGameplayTag InMapTag)
{
	static FAoS_MapState TempMapState = FAoS_MapState(nullptr);
	
	for (FAoS_MapState& CurrentMapState : MapStates)
	{
		const UAoS_MapData* CurrentMapData = CurrentMapState.GetMapData();
		if (!IsValid(CurrentMapData)) {return TempMapState;}
		
		if(CurrentMapState.GetMapData()->MapTag == InMapTag)
		{
			return CurrentMapState;
		}
	}

	return TempMapState;
}

const TArray<FAoS_MapState>& UAoS_LevelManager::GetAllMapStates() const
{
	return MapStates;		
}

TArray<FString>& UAoS_LevelManager::GetMapNames()
{
	static TArray<FString> MapNames;
	for (const FAoS_MapState& CurrentMapState : MapStates)
	{
		MapNames.AddUnique(CurrentMapState.GetMapData()->MapName);
	}
	
	return MapNames;
}

FAoS_MapState& UAoS_LevelManager::GetMapStateFromName(FString InMapName)
{
	for (FAoS_MapState& CurrentMapState : MapStates)
	{
		if (CurrentMapState.GetMapData()->MapName == InMapName)
		{
			return CurrentMapState;
		}
	}
	
	static FAoS_MapState EmptyMapState;
	return EmptyMapState;
}


void UAoS_LevelManager::LevelLoaded()
{
	if(LevelStateToLoad == nullptr)
	{
		OnInitGame();
		if(LevelStateToLoad == nullptr){return;}
	}
	
	LoadedMapState = LevelStateToLoad;
	if (LoadedMapState->GetMapData()->MapType == AOSTag_Map_Type_Menu)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_MainMenuMode);
	}
	else
	{
		UAoS_MediaManager* MediaManager =  GetWorld()->GetSubsystem<UAoS_MediaManager>();
		if (IsValid(MediaManager) && LoadedMapState->HasIntroMedia() && !MediaManager->HasMediaPlayed(LoadedMapState->GetLoadedIntroMedia()))
		{
			MediaManager->PlayMedia(LoadedMapState->GetLoadedIntroMedia(), LoadedMapState->GetOutroSettings());
		}
		else
		{
			GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);	
		}
	}
	
	bLevelHasLoaded = true;
	OnLevelLoaded.Broadcast(LoadedMapState->GetMapData(), bLoadShouldFade);
}

FAoS_MapState& UAoS_LevelManager::GetCurrentLoadedMapState() const
{
	return *LoadedMapState;
}
