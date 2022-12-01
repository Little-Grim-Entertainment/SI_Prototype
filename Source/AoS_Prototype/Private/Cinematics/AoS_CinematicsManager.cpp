// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematics/AoS_CinematicsManager.h"

#include "AoS_GameInstance.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Controllers/AoS_PlayerController.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "MediaAssets/Public/MediaSource.h"

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

void UAoS_CinematicsManager::PlayVideo(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, UMediaTexture* InMediaTexture, float InVolume)
{
	if (!IsValid(InMediaPlayer) || !IsValid(InMediaSource)){return;}

	CurrentMediaPlayer = InMediaPlayer;
	CurrentMediaSource = InMediaSource;
	CurrentMediaTexture = InMediaTexture;

	if (InVolume != 1.0f)
	{
		CurrentMediaPlayer->SetNativeVolume(InVolume);
	}
	
	PreviousPlayerMode = GameInstance->GetPlayerMode();
	GameInstance->SetPlayerMode(EPlayerMode::PM_VideoMode);
}

ULevelSequencePlayer* UAoS_CinematicsManager::GetCurrentCinematic() const
{
	return CurrentCinematic;
}

UMediaPlayer* UAoS_CinematicsManager::GetCurrentMediaPlayer() const
{
	return CurrentMediaPlayer;
}

UMediaSource* UAoS_CinematicsManager::GetCurrentMediaSource() const
{
	return CurrentMediaSource;
}

UMediaTexture* UAoS_CinematicsManager::GetCurrentMediaTexture() const
{
	return CurrentMediaTexture;
}

void UAoS_CinematicsManager::OnCinematicEnd()
{
	if(!IsValid(GameInstance)){return;}

	GameInstance->SetPlayerMode(PreviousPlayerMode);
}

void UAoS_CinematicsManager::OnVideoEnd()
{
	if(!IsValid(GameInstance)){return;}

	GameInstance->SetPlayerMode(PreviousPlayerMode);
	OnVideoEnded.Broadcast();
}
	
