// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematics/AoS_CinematicsManager.h"

#include "AoS_GameInstance.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Controllers/AoS_PlayerController.h"
#include "Levels/AoS_LevelManager.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "MediaAssets/Public/MediaSource.h"
#include "Data/Videos/AoS_VideoDataAsset.h"


void UAoS_CinematicsManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	
}

void UAoS_CinematicsManager::PlayCinematic(ULevelSequence* LevelSequenceToPlay, bool bAutoPlay, int32 Loop, float PlayRate, float StartOffset, bool bRandomStartTime, bool bRestoreState, bool bDisableMovementInput, bool bDisableLookInput, bool bHidePlayer, bool bHideHud, bool bDisableCameraCuts, bool bPauseAtEnd)
{
	ALevelSequenceActor* LevelSequenceActor;
	
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	PlaybackSettings.bAutoPlay = bAutoPlay;
	PlaybackSettings.LoopCount.Value = Loop;
	PlaybackSettings.PlayRate = PlayRate;
	PlaybackSettings.StartTime = StartOffset;
	PlaybackSettings.bRandomStartTime = bRandomStartTime;
	PlaybackSettings.bRestoreState = bRestoreState;
	PlaybackSettings.bDisableMovementInput = bDisableMovementInput;
	PlaybackSettings.bDisableLookAtInput = bDisableLookInput;
	PlaybackSettings.bHidePlayer = bHidePlayer;
	PlaybackSettings.bHideHud = bHideHud;
	PlaybackSettings.bDisableCameraCuts = bDisableCameraCuts;
	PlaybackSettings.bPauseAtEnd = bPauseAtEnd;
	
	CurrentCinematic = ULevelSequencePlayer::CreateLevelSequencePlayer(this, LevelSequenceToPlay, PlaybackSettings, LevelSequenceActor);

	if(!IsValid(GameInstance) || !IsValid(CurrentCinematic)){return;}

	CurrentCinematic->OnFinished.AddDynamic(this, &ThisClass::OnCinematicEnd);
	CurrentCinematic->Play();		

	PreviousPlayerMode = GameInstance->GetPlayerMode();
	GameInstance->SetPlayerMode(EPlayerMode::PM_CinematicMode);
}

void UAoS_CinematicsManager::PlayVideo(UAoS_VideoDataAsset* InVideoToPlay, bool bShouldRepeat, float InVolume)
{
	if (!IsValid(InVideoToPlay)){return;}
	if (InVideoToPlay->GetVideoHasPlayed() && !bShouldRepeat) {return;}
	
	LoadedVideo = InVideoToPlay;
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

	PreviousPlayerMode = GameInstance->GetPlayerMode();
	GameInstance->SetPlayerMode(EPlayerMode::PM_VideoMode);

	LoadedVideo->StartVideo();
}

void UAoS_CinematicsManager::ResetVideoByName(FString InVideoName)
{
	for (UAoS_VideoDataAsset* CurrentVideo : PlayedVideos)
	{
		if (CurrentVideo->VideoName == InVideoName)
		{
			CurrentVideo->ResetVideoDefaults();
		}
	}
}

void UAoS_CinematicsManager::ResetAllVideos()
{
	for (UAoS_VideoDataAsset* CurrentVideo : PlayedVideos)
	{
		CurrentVideo->ResetVideoDefaults();
	}
}

ULevelSequencePlayer* UAoS_CinematicsManager::GetCurrentCinematic() const
{
	return CurrentCinematic;
}

UAoS_VideoDataAsset* UAoS_CinematicsManager::GetLoadedVideo() const
{
	return LoadedVideo;
}

void UAoS_CinematicsManager::OnCinematicEnd()
{
	if(!IsValid(GameInstance)){return;}

	GameInstance->SetPlayerMode(PreviousPlayerMode);
}

void UAoS_CinematicsManager::DelayedVideoPlay(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	if(!IsValid(LoadedVideo)){return;}
	
	PlayVideo(LoadedVideo, LoadedVideo->bCanRepeat, LoadedVideo->MediaPlayer->NativeAudioOut);
}

void UAoS_CinematicsManager::OnVideoEnded()
{
	if(!IsValid(GameInstance)){return;}

	PlayedVideos.AddUnique(LoadedVideo);
	LoadedVideo = nullptr;
	
	GameInstance->SetPlayerMode(PreviousPlayerMode);
}

void UAoS_CinematicsManager::OnVideoSkipped()
{
	if(!IsValid(GameInstance)){return;}

	LoadedVideo = nullptr;
	
	GameInstance->SetPlayerMode(PreviousPlayerMode);
}
	
