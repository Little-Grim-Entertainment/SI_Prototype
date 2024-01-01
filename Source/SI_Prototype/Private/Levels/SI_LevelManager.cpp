// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/SI_LevelManager.h"
#include "SI_GameInstance.h"
#include "GameplayTag/SI_GameplayTagManager.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "LevelSequencePlayer.h"
#include "Levels/SI_MapGameplayTagLibrary.h"
#include "Characters/SI_GizboManager.h"
#include "Media/SI_MediaManager.h"
#include "Controllers/SI_PlayerController.h"
#include "Data/Maps/SI_MapList.h"
#include "Data/Media/SI_VideoDataAsset.h"
#include "Data/Media/SI_MediaDataAsset.h"
#include "GameModes/SI_GameMode.h"
#include "Data/Maps/SI_MapData.h"
#include "Data/Media/SI_CinematicDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/World.h"
#include "MediaPlayer.h"
#include "Data/Cases/SI_CaseManager.h"

using namespace SI_MapGameplayTagLibrary;
using namespace SI_NativeGameplayTagLibrary;

USI_LevelManager::USI_LevelManager()
{
	bMapStatesInitialized = false;
}

void USI_LevelManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	

	if(!bMapStatesInitialized)
	{
		InitializeMapStates();
	}
	
	LevelLoaded(GetWorld());
}

void USI_LevelManager::OnPlayerStart()
{
	Super::OnPlayerStart();
	
}

void USI_LevelManager::InitializeMapStates()
{
	if(MapStates.Num() > 0)
	{
		MapStates.Empty();
	}

	if (!IsValid(GameInstance) || !IsValid(GameInstance->MapList)) {return;}
	
	TArray<USI_MapData*> AllMaps = GameInstance->MapList->GetAllMaps();
	
	for (USI_MapData* CurrentMapData : AllMaps)
	{
		if (!IsValid(CurrentMapData)) {continue;}

		FSI_MapState* NewMapState = new FSI_MapState(CurrentMapData);
		MapStates.Add(NewMapState);
	}

	bMapStatesInitialized = true;
}

void USI_LevelManager::LoadLevelByTag(FGameplayTag InLevelToLoadTag,  FString InPlayerStartTag, bool bAllowDelay, bool bShouldFade, bool bShouldSkipMedia)
{
	ExecuteLoadLevelByTag(InLevelToLoadTag, InPlayerStartTag, bAllowDelay, bShouldFade, bShouldSkipMedia);
}

void USI_LevelManager::ExecuteLoadLevelByTag(const FGameplayTag& InLevelToLoadTag, const FString& InPlayerStartTag, bool bAllowDelay, bool bShouldFade, bool bShouldSkipMedia)
{
	if (LoadDelayDelegate.IsBound()){LoadDelayDelegate.Unbind();}

	if(LoadedLevel.IsValid())
	{
		FSI_MapState* LoadedMapState = GetMapStateByTag(LoadedLevel);
		if(LoadedMapState->IsStateValid())
		{
			if (LoadedMapState->GetMapData()->MapType == SITag_Map_Type_Menu)
			{
				SITagManager->RemoveTag(SITag_UI_Menu_Map);
			}

			if(!bShouldSkipMedia && LoadedMapState->HasOutroMedia())
			{
				USI_MediaManager* MediaManager =  GetWorld()->GetSubsystem<USI_MediaManager>();
				if (IsValid(MediaManager) && !MediaManager->HasMediaPlayed(LoadedMapState->GetLoadedOutroMedia()))
				{
					MediaManager->PlayMedia(LoadedMapState->GetLoadedOutroMedia(), LoadedMapState->GetOutroSettings());
					LoadLevelOnMediaComplete(InLevelToLoadTag, LoadedMapState->GetLoadedOutroMedia(), InPlayerStartTag, bAllowDelay, bShouldFade);
					return;
				}
			}
		}
	}

	LevelToLoad = InLevelToLoadTag;
	bLoadShouldFade = bShouldFade;
	bLevelHasLoaded = false;

	GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>();
	if(IsValid(GizboManager))
	{
		FString GizboStartTag = InPlayerStartTag;
		GizboStartTag = UKismetStringLibrary::Replace(GizboStartTag, "Nick_", "Gizbo_");
		GizboManager->SetGizboStartTag(GizboStartTag);
	}
	
	const ASI_GameMode* GameMode = GameInstance->GetGameMode();
	if (!IsValid(GameMode)) {return;}

	if(!SITagManager->HasGameplayTag(SITag_Game_State_Loading))
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Game_State_Loading, SITag_Game_State);
	}

	const FSI_MapState* LevelStateToLoad = GetMapStateByTag(LevelToLoad);
		
	if (GetWorld() != LevelStateToLoad->GetMapData()->Map.Get())
	{
		if (bAllowDelay)
		{
			LoadDelayDelegate.BindUObject(this, &ThisClass::LoadLevelByTag, LevelToLoad, InPlayerStartTag, false, bShouldFade, bShouldSkipMedia);
			GetWorld()->GetTimerManager().SetTimer(LoadDelayHandle, LoadDelayDelegate, GameMode->LevelLoadDelay, false);
			OnBeginLevelLoadDelegate.Broadcast(LevelStateToLoad->GetMapData(), bShouldFade);
		}
		else
		{
			if (IsValid(LevelStateToLoad->GetMapData()))
			{
				
				if (LoadedLevel.IsValid())
				{
					OnLevelUnloadedDelegate.Broadcast(GetMapStateByTag(LoadedLevel)->GetMapData());
				}
				
				UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),LevelStateToLoad->GetMapData()->Map, true, InPlayerStartTag);
				OnBeginLevelLoadDelegate.Broadcast(LevelStateToLoad->GetMapData(), bShouldFade);
			}
		}
	}
}

void USI_LevelManager::LoadLevelOnMediaComplete(const FGameplayTag& InLevelToLoadTag, USI_MediaDataAsset* InMediaToPlay, const FString& InPlayerStartTag, bool bAllowDelay, bool bShouldFade, bool bShouldSkipMedia)
{
	if (const USI_CinematicDataAsset* CinematicDataAsset = Cast<USI_CinematicDataAsset>(InMediaToPlay))
	{
		LoadLevelOnCinematicComplete(InLevelToLoadTag, CinematicDataAsset, InPlayerStartTag, bAllowDelay, bShouldFade);
	}
	else if (const USI_VideoDataAsset* VideoDataAsset = Cast<USI_VideoDataAsset>(InMediaToPlay))
	{
		LoadLevelOnVideoComplete(InLevelToLoadTag, VideoDataAsset, InPlayerStartTag, bAllowDelay, bShouldFade);
	}
}

void USI_LevelManager::LoadLevelOnVideoComplete(const FGameplayTag& InLevelToLoadTag, const USI_VideoDataAsset* InVideoToPlay, const FString& InPlayerStartTag, bool bAllowDelay, bool bShouldFade, bool bShouldSkipMedia)
{
	LoadDelayDelegate.BindUObject(this, &USI_LevelManager::LoadLevelByTag, InLevelToLoadTag, InPlayerStartTag, bAllowDelay, bShouldFade, bShouldSkipMedia);
	InVideoToPlay->MediaPlayer->OnEndReached.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
	InVideoToPlay->MediaPlayer->OnMediaClosed.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
}

void USI_LevelManager::LoadLevelOnCinematicComplete(const FGameplayTag& InLevelToLoadTag, const USI_CinematicDataAsset* InCinematicToPlay, const FString& InPlayerStartTag, bool bAllowDelay, bool bShouldFade, bool bShouldSkipMedia)
{
	LoadDelayDelegate.BindUObject(this, &USI_LevelManager::LoadLevelByTag, InLevelToLoadTag, InPlayerStartTag, bAllowDelay, bShouldFade, bShouldSkipMedia);
	InCinematicToPlay->CinematicPlayer->OnFinished.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnCinematicComplete);
	InCinematicToPlay->CinematicPlayer->OnStop.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnCinematicComplete);
}

void USI_LevelManager::ExecuteLoadLevelOnVideoComplete()
{
	LoadDelayDelegate.Execute();
	LoadDelayDelegate.Unbind();
}

void USI_LevelManager::ExecuteLoadLevelOnCinematicComplete()
{
	LoadDelayDelegate.Execute();
	LoadDelayDelegate.Unbind();
}

USI_MapData* USI_LevelManager::GetCurrentMap()
{
	if(LoadedLevel.IsValid())
	{
		return GetMapStateByTag(LoadedLevel)->GetMapData();
	}
	
	return nullptr;
}

bool USI_LevelManager::GetLevelHasLoaded() const
{
	return bLevelHasLoaded;
}

FSI_MapState* USI_LevelManager::GetMapStateByTag(const FGameplayTag InMapTag)
{
	static FSI_MapState TempMapState = FSI_MapState(nullptr);
	
	for (FSI_MapState* CurrentMapState : MapStates)
	{
		const USI_MapData* CurrentMapData = CurrentMapState->GetMapData();
		if (!IsValid(CurrentMapData)) {return &TempMapState;}
		
		if(CurrentMapState->GetMapData()->MapTag == InMapTag)
		{
			return CurrentMapState;
		}
	}

	return &TempMapState;
}

FSI_MapState* USI_LevelManager::GetMapStateByWorld()
{
	const FString MapName = GetWorld()->GetName();
	return GetMapStateFromName(MapName);
}

const TArray<FSI_MapState*>& USI_LevelManager::GetAllMapStates() const
{
	return MapStates;		
}

TArray<FString>& USI_LevelManager::GetMapNames()
{
	static TArray<FString> MapNames;
	for (const FSI_MapState* CurrentMapState : MapStates)
	{
		MapNames.AddUnique(CurrentMapState->GetMapData()->MapName);
	}
	
	return MapNames;
}

USI_MapData* USI_LevelManager::GetMapDataFromName(const FString& InMapName)
{
	const FSI_MapState* FoundMapState = GetMapStateFromName(InMapName);
	return FoundMapState->GetMapData();
}

FSI_MapState* USI_LevelManager::GetMapStateFromName(const FString& InMapName)
{
	for (FSI_MapState* CurrentMapState : MapStates)
	{
		FString CurrentMapDataName = CurrentMapState->GetMapData()->GetName();
		if(CurrentMapDataName == InMapName)
		{
			return CurrentMapState;
		}
		
		FString CurrentMapName = CurrentMapDataName.Replace(TEXT("DA"), TEXT("M"));
		
		if (CurrentMapName == InMapName)
		{
			return CurrentMapState;
		}
	}
	
	static FSI_MapState EmptyMapState;
	return &EmptyMapState;
}

FOnBeginLevelLoad& USI_LevelManager::OnBeginLevelLoad()
{
	return OnBeginLevelLoadDelegate;
}

FOnLevelLoaded& USI_LevelManager::OnLevelLoaded()
{
	return OnLevelLoadedDelegate;
}

FOnLevelUnloaded& USI_LevelManager::OnLevelUnloaded()
{
	return OnLevelUnloadedDelegate;
}


void USI_LevelManager::LevelLoaded(UWorld* LoadedWorld)
{
	LoadedLevel = LevelToLoad;

	FSI_MapState* LoadedMapState = LoadedLevel.IsValid() ? GetMapStateByTag(LoadedLevel) : GetMapStateByWorld();

	if (!LoadedMapState->IsStateValid()) {return;}
	
	if(!LoadedLevel.IsValid())
	{
		LoadedLevel = LoadedMapState->MapData->MapTag;
	}
			
	SITagManager->ReplaceTagWithSameParent(LoadedMapState->MapData->MapTag, SITag_Map_Title);

	if (LoadedMapState->GetMapData()->MapType == SITag_Map_Type_Menu)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_UI_Menu_Map, SITag_UI_Menu);
	}
	else if(SITagManager->HasGameplayTag(SITag_UI_Menu_Map))
	{
		SITagManager->RemoveTag(SITag_UI_Menu_Map);
	}
	
	bLevelHasLoaded = true;
	SITagManager->ReplaceTagWithSameParent(SITag_Game_State_Playing, SITag_Game_State);

	OnLevelLoadedDelegate.Broadcast(LoadedMapState->GetMapData(), bLoadShouldFade);
}

FSI_MapState* USI_LevelManager::GetCurrentLoadedMapState()
{
	return GetMapStateByTag(LoadedLevel);
}
