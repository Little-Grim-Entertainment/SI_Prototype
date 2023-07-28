// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/SI_LevelManager.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"
#include "SI_NativeGameplayTagLibrary.h"
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

USI_LevelManager::USI_LevelManager()
{

}

void USI_LevelManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	
	InitializeMapStates();
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
 	const ASI_GameMode* GameMode = Cast<ASI_GameMode>(GetWorld()->GetAuthGameMode());
	
	if (!IsValid(GameMode)) {return;}
	if (!IsValid(GameMode->MapList)) {return;}
	
	TArray<USI_MapData*> AllMaps = GameMode->MapList->GetAllMaps();
	
	for (USI_MapData* CurrentMapData : AllMaps)
	{
		if (!IsValid(CurrentMapData)) {continue;}

		MapStates.Add(FSI_MapState(CurrentMapData));
	}
}

void USI_LevelManager::LoadLevelByTag(FGameplayTag InLevelToLoadTag,  FString InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	FSI_MapState& MapStateToLoad = GetMapStateByTag(InLevelToLoadTag);
	
	if (!MapStateToLoad.GetMapData()) {return;}
	if (LoadDelayDelegate.IsBound()){LoadDelayDelegate.Unbind();}

	if(LoadedMapState != nullptr)
	{
		if (LoadedMapState->GetMapData()->MapType == SITag_Map_Type_Menu)
		{
			SITagManager->RemoveTag(SITag_UI_Menu_Map);
		}

		if(LoadedMapState->HasOutroMedia())
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
	
	LevelStateToLoad = &MapStateToLoad;
	bLoadShouldFade = bShouldFade;
	bLevelHasLoaded = false;

	USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>();
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
	
	if (GetWorld() != MapStateToLoad.GetMapData()->Map.Get())
	{
		if (bAllowDelay)
		{
			LoadDelayDelegate.BindUObject(this, &ThisClass::LoadLevelByTag, InLevelToLoadTag, InPlayerStartTag, false, bShouldFade);
			GetWorld()->GetTimerManager().SetTimer(LoadDelayHandle, LoadDelayDelegate, GameMode->LevelLoadDelay, false);
			OnBeginLevelLoad.Broadcast(MapStateToLoad.GetMapData(), bShouldFade);
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
				OnBeginLevelLoad.Broadcast(MapStateToLoad.GetMapData(), bShouldFade);
			}
		}
	}
}

void USI_LevelManager::LoadLevelOnMediaComplete(const FGameplayTag& InLevelToLoadTag, USI_MediaDataAsset* InMediaToPlay, const FString& InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
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

void USI_LevelManager::LoadLevelOnVideoComplete(const FGameplayTag& InLevelToLoadTag, const USI_VideoDataAsset* InVideoToPlay, const FString& InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	LoadDelayDelegate.BindUObject(this, &USI_LevelManager::LoadLevelByTag, InLevelToLoadTag, InPlayerStartTag, bAllowDelay, bShouldFade);
	InVideoToPlay->MediaPlayer->OnEndReached.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
	InVideoToPlay->MediaPlayer->OnMediaClosed.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
}

void USI_LevelManager::LoadLevelOnCinematicComplete(const FGameplayTag& InLevelToLoadTag, const USI_CinematicDataAsset* InCinematicToPlay, const FString& InPlayerStartTag, bool bAllowDelay, bool bShouldFade)
{
	//GameInstance->SetPreviousPlayerMode(EPlayerMode::PM_LevelLoadingMode);
	LoadDelayDelegate.BindUObject(this, &USI_LevelManager::LoadLevelByTag, InLevelToLoadTag, InPlayerStartTag, bAllowDelay, bShouldFade);
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

USI_MapData* USI_LevelManager::GetCurrentMap() const
{
	return LoadedMapState->GetMapData();
}

bool USI_LevelManager::GetLevelHasLoaded() const
{
	return bLevelHasLoaded;
}

FSI_MapState& USI_LevelManager::GetMapStateByTag(const FGameplayTag InMapTag)
{
	static FSI_MapState TempMapState = FSI_MapState(nullptr);
	
	for (FSI_MapState& CurrentMapState : MapStates)
	{
		const USI_MapData* CurrentMapData = CurrentMapState.GetMapData();
		if (!IsValid(CurrentMapData)) {return TempMapState;}
		
		if(CurrentMapState.GetMapData()->MapTag == InMapTag)
		{
			return CurrentMapState;
		}
	}

	return TempMapState;
}

FSI_MapState& USI_LevelManager::GetMapStateByWorld()
{
	const FString MapName = GetWorld()->GetName();
	return GetMapStateFromName(MapName);
}

const TArray<FSI_MapState>& USI_LevelManager::GetAllMapStates() const
{
	return MapStates;		
}

TArray<FString>& USI_LevelManager::GetMapNames()
{
	static TArray<FString> MapNames;
	for (const FSI_MapState& CurrentMapState : MapStates)
	{
		MapNames.AddUnique(CurrentMapState.GetMapData()->MapName);
	}
	
	return MapNames;
}

FSI_MapState& USI_LevelManager::GetMapStateFromName(FString InMapName)
{
	for (FSI_MapState& CurrentMapState : MapStates)
	{
		FString CurrentMapDataName = CurrentMapState.GetMapData()->GetName();
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
	return EmptyMapState;
}


void USI_LevelManager::LevelLoaded(UWorld* LoadedWorld)
{
	LoadedMapState = LevelStateToLoad;

	if (LoadedMapState == nullptr)
	{
		LoadedMapState = &GetMapStateByWorld();
		if (!LoadedMapState->IsStateValid()) {return;}
	}
			
	SITagManager->ReplaceTagWithSameParent(LoadedMapState->MapData->MapTag, SITag_Map_Title);

	if (LoadedMapState->GetMapData()->MapType == SITag_Map_Type_Menu)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_UI_Menu_Map, SITag_UI_Menu);
	}
	else
	{
		USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>();
		USI_CaseManager* CaseManager = GetGameInstance()->GetSubsystem<USI_CaseManager>();
		if(IsValid(CaseManager))
		{
			CaseManager->AssignMedia();
		}
		if (IsValid(MediaManager) && LoadedMapState->HasIntroMedia() && !MediaManager->HasMediaPlayed(LoadedMapState->GetLoadedIntroMedia()) && !SITagManager->HasGameplayTag(SITag_Debug_DisableAllMedia))
		{
			MediaManager->PlayMedia(LoadedMapState->GetLoadedIntroMedia(), LoadedMapState->GetOutroSettings());
		}
		else
		{
			SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
			SITagManager->ReplaceTagWithSameParent(SITag_UI_HUD, SITag_UI);
		}
	}
	
	bLevelHasLoaded = true;
	SITagManager->ReplaceTagWithSameParent(SITag_Game_State_Playing, SITag_Game_State);

	OnLevelLoaded.Broadcast(LoadedMapState->GetMapData(), bLoadShouldFade);
}

FSI_MapState& USI_LevelManager::GetCurrentLoadedMapState() const
{
	return *LoadedMapState;
}
