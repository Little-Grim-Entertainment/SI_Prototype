// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematics/AoS_CinematicsManager.h"

#include "AoS_GameInstance.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"





void UAoS_CinematicsManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
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
	if(!IsValid(GameInstance) || !IsValid(CurrentCinematic))
	{
		return;
	}

	CurrentCinematic->OnFinished.AddDynamic(this, &ThisClass::OnCinematicEnd);
	CurrentCinematic->Play();		

	PreviousPlayerMode = GameInstance->GetPlayerMode();
	GameInstance->SetPlayerMode(EPlayerMode::PM_CinematicMode);
}

void UAoS_CinematicsManager::OnCinematicEnd()
{
	if(!IsValid(GameInstance))
	{
		return;
	}

	GameInstance->SetPlayerMode(PreviousPlayerMode);
}
	
