// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematics/AoS_CinematicsManager.h"

#include "AoS_GameInstance.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Controllers/AoS_PlayerController.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Levels/AoS_LevelManager.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Data/Media/AoS_WatchedMedia.h"


void UAoS_CinematicsManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	
}

void UAoS_CinematicsManager::PlayCinematic(UAoS_CinematicDataAsset* InCinematicToPlay)
{
	if (!IsValid(InCinematicToPlay)) {return;}
	if (InCinematicToPlay->GetMediaHasPlayed() && !InCinematicToPlay->bCanRepeat) {return;}
	
	InCinematicToPlay->CinematicPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, InCinematicToPlay->LevelSequence, InCinematicToPlay->PlaybackSettings, InCinematicToPlay->LevelSequenceActor);
	ULevelSequencePlayer* CurrentCinematic = InCinematicToPlay->CinematicPlayer;

	LoadedCinematic = InCinematicToPlay;

	if(!IsValid(GameInstance) || !IsValid(InCinematicToPlay->CinematicPlayer)){return;}

	if (!GameInstance->GetLevelManager()->GetLevelHasLoaded())
	{
		GameInstance->GetLevelManager()->OnLevelLoaded.AddDynamic(this, &ThisClass::DelayedCinematicPlay);
		return;
	}

	CurrentCinematic->OnFinished.AddDynamic(this, &ThisClass::OnCinematicEnded);
	CurrentCinematic->OnPause.AddDynamic(this, &ThisClass::OnCinematicSkipped);

	CurrentCinematic->Play();

	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_CinematicMode);
	LoadedCinematic->StartMedia();
}

void UAoS_CinematicsManager::PlayVideo(UAoS_VideoDataAsset* InVideoToPlay, bool bShouldRepeat, float InVolume)
{
	if (!IsValid(InVideoToPlay)){return;}
	if (InVideoToPlay->GetMediaHasPlayed() && !bShouldRepeat) {return;}
	
	LoadedVideo = InVideoToPlay;

	if (!IsValid(GameInstance) || !IsValid(LoadedVideo)){return;}

	LoadedVideo->bCanRepeat = bShouldRepeat;
	LoadedVideo->MediaPlayer->SetNativeVolume(InVolume);
	
	if (!GameInstance->GetLevelManager()->GetLevelHasLoaded())
	{
		GameInstance->GetLevelManager()->OnLevelLoaded.AddDynamic(this, &ThisClass::DelayedVideoPlay);
		return;
	}
	
	if (LoadedVideo->MediaPlayer->OnEndReached.IsBound())
	{
		LoadedVideo->MediaPlayer->OnEndReached.RemoveAll(this);
	}

	const AAoS_PlayerController* PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(PlayerController))
	{
		PlayerController->GetMediaSoundComponent()->SetMediaPlayer(LoadedVideo->MediaPlayer);
	}
	
	LoadedVideo->OnVideoEnded.AddDynamic(this, &ThisClass::UAoS_CinematicsManager::OnVideoEnded);
	LoadedVideo->OnVideoSkipped.AddDynamic(this, &ThisClass::UAoS_CinematicsManager::OnVideoSkipped);

	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_VideoMode);

	// Note: Playing the actual video file happens in the widget blueprint
	LoadedVideo->StartMedia();
}

void UAoS_CinematicsManager::ResetCinematicByName(FString InCinematicName)
{
	if (GetWatchedCinematics().Num() <= 0){return;}
	for (UAoS_VideoDataAsset* CurrentVideo : GetWatchedVideos())
	{
		if(IsValid(CurrentVideo) && CurrentVideo->MediaName == InCinematicName)
		{
			CurrentVideo->ResetMediaDefaults();
		}
	}
}

void UAoS_CinematicsManager::ResetAllCinematics()
{
	if (GetWatchedCinematics().Num() <= 0){return;}
	for (UAoS_VideoDataAsset* CurrentVideo : GetWatchedVideos())
	{
		if (IsValid(CurrentVideo))
		{
			CurrentVideo->ResetMediaDefaults();
		}
	}
	GetWatchedCinematics().Empty();
}

void UAoS_CinematicsManager::ResetVideoByName(FString InVideoName)
{
	if (GetWatchedVideos().Num() <= 0){return;}
	for (UAoS_VideoDataAsset* CurrentVideo : GetWatchedVideos())
	{
		if(IsValid(CurrentVideo) && CurrentVideo->MediaName == InVideoName)
		{
			CurrentVideo->ResetMediaDefaults();
		}
	}
}

void UAoS_CinematicsManager::ResetAllVideos()
{
	if (GetWatchedVideos().Num() <= 0){return;}
	for (UAoS_VideoDataAsset* CurrentVideo : GetWatchedVideos())
	{
		if (IsValid(CurrentVideo))
		{
			CurrentVideo->ResetMediaDefaults();
		}
	}
	GetWatchedVideos().Empty();
}

void UAoS_CinematicsManager::LoadLevelOnVideoComplete(UAoS_MapData* InLevelToLoad, bool bAllowDelay, bool bShouldFade, FString InPlayerStartTag)
{
	UAoS_LevelManager* LevelManager = GameInstance->GetLevelManager();
	if (IsValid(LevelManager))
	{
		GameInstance->SetPreviousPlayerMode(EPlayerMode::PM_LevelLoadingMode);
		DelayedLevelLoad.BindUObject(LevelManager, &UAoS_LevelManager::LoadLevel, InLevelToLoad, bAllowDelay, bShouldFade, InPlayerStartTag);
		LoadedVideo->OnVideoEnded.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
		LoadedVideo->OnVideoSkipped.AddDynamic(this, &ThisClass::ExecuteLoadLevelOnVideoComplete);
	}
}

TArray<UAoS_CinematicDataAsset*> UAoS_CinematicsManager::GetWatchedCinematics()
{
	TArray<UAoS_CinematicDataAsset*> EmptyArray;
	if (!IsValid(GameInstance) || !GameInstance->WatchedMediaData) {return EmptyArray;}

	return  GameInstance->WatchedMediaData->GetWatchedCinematics();
}

UAoS_CinematicDataAsset* UAoS_CinematicsManager::GetLoadedCinematic() const
{
	return LoadedCinematic;
}

UAoS_VideoDataAsset* UAoS_CinematicsManager::GetLoadedVideo() const
{
	return LoadedVideo;
}

TArray<UAoS_VideoDataAsset*> UAoS_CinematicsManager::GetWatchedVideos()
{
	TArray<UAoS_VideoDataAsset*> EmptyArray;
	if (!IsValid(GameInstance) || !GameInstance->WatchedMediaData) {return EmptyArray;}

	return  GameInstance->WatchedMediaData->GetWatchedVideos();
}

void UAoS_CinematicsManager::ExecuteLoadLevelOnVideoComplete()
{
	DelayedLevelLoad.Execute();
	DelayedLevelLoad.Unbind();
}

void UAoS_CinematicsManager::OnCinematicSkipped()
{
	if(!IsValid(GameInstance)){return;}
	EPlayerMode PreviousPlayerMode = GameInstance->GetPreviousPlayerMode();
	if(PreviousPlayerMode == EPlayerMode::PM_LevelLoadingMode)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);	
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
}

void UAoS_CinematicsManager::OnCinematicEnded()
{
	if(!IsValid(GameInstance)){return;}

	GameInstance->WatchedMediaData->AddToWatchedCinematics(LoadedCinematic);
	if (LoadedCinematic->bIsOpeningMedia)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
}

void UAoS_CinematicsManager::DelayedCinematicPlay(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	if(!IsValid(LoadedCinematic)){return;}
	
	PlayCinematic(LoadedCinematic);
}

void UAoS_CinematicsManager::DelayedVideoPlay(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	if(!IsValid(LoadedVideo)){return;}
	
	PlayVideo(LoadedVideo, LoadedVideo->bCanRepeat, LoadedVideo->MediaPlayer->NativeAudioOut);
}

void UAoS_CinematicsManager::OnVideoEnded()
{
	if(!IsValid(GameInstance)){return;}

	GameInstance->WatchedMediaData->AddToWatchedVideos(LoadedVideo);
	if (LoadedVideo->bIsOpeningMedia)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
}

void UAoS_CinematicsManager::OnVideoSkipped()
{
	if(!IsValid(GameInstance)){return;}
	EPlayerMode PreviousPlayerMode = GameInstance->GetPreviousPlayerMode();
	if(PreviousPlayerMode == EPlayerMode::PM_LevelLoadingMode)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);	
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
}
	
