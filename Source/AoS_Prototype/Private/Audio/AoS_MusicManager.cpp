// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AoS_MusicManager.h"
#include "AoS_GameInstance.h"
#include "AudioDevice.h"
#include "Components/AudioComponent.h"
#include "Data/Maps/AoS_MapData.h"
#include "GameModes/AoS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/AoS_LevelManager.h"


UAoS_MusicManager::UAoS_MusicManager()
{
	bMusicIsPlaying = false;
	bMusicIsPaused = false;
	bMusicHasIntro = false;
	MusicTimeAtPause = 0.f;
	MusicVolumeAtPause = 1.f;
	MusicPitchAtPause = 1.f;
	MusicLoopStart = 0.f;
}

void UAoS_MusicManager::TickMusicTimecode()
{
	MusicTimeAtPause += .001;
}

void UAoS_MusicManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (IsValid(LevelManager))
	{
		LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::OnLevelLoaded);
		LevelManager->OnLevelUnloaded.AddDynamic(this, &ThisClass::OnLevelUnloaded);
	}
}

/*void UAoS_MusicManager::OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode)
{
	Super::OnPlayerModeChanged(NewPlayerMode, InPreviousPlayerMode);
	
	switch (NewPlayerMode)
	{
		case EPlayerMode::PM_CinematicMode:
		{
			if(!bMusicIsPaused)
			{
				PauseMusicWithFade();
			}
			break;	
		}
		case EPlayerMode::PM_VideoMode:
		{
			if(!bMusicIsPaused)
			{
				PauseMusicWithFade();
			}
			break;
		}
		case EPlayerMode::PM_TitleCardMode:
		{
			if(!bMusicIsPaused)
			{
				PauseMusicWithFade();
			}
			break;
		}
		default:
		{
			if(bMusicIsPaused)
			{
				ResumeMusicWithFade();
			}
			break;
		}
	}
}*/

void UAoS_MusicManager::OnLevelLoaded(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();

	if (!IsValid(LoadedLevel) || !IsValid(LevelManager)) {return;}

	FAoS_MapState& LoadedMapState = LevelManager->GetMapStateByTag(LoadedLevel->MapTag);
	
	PlayLevelBackgroundMusic(LoadedMapState);
}

void UAoS_MusicManager::OnLevelUnloaded(UAoS_MapData* UnloadedLevel)
{
	StopBackgroundMusic(true, 0);
}

UAudioComponent* UAoS_MusicManager::PlayLevelBackgroundMusic(FAoS_MapState& InMapState)
{
	if (!InMapState.IsStateValid() || IsValid(InMapState.GetMapData())){return nullptr;}
	
	if(InMapState.GetMapData()->BackgroundMusicSettings.bHasIntro)
	{
		return  PlayBackgroundMusicLoopWithIntro(InMapState.GetMapData()->BackgroundMusicSettings);
	}

	return PlayBackgroundMusic(InMapState.GetMapData()->BackgroundMusicSettings);
}

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusic(FAoS_MusicSettings InMusicSettings)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GameInstance, InMusicSettings.MetaSoundSource, InMusicSettings.VolumeMultiplier, InMusicSettings.PitchMultiplier, InMusicSettings.StartTime, nullptr, true);	

	CurrentMusicSettings = InMusicSettings;
	
	MetaSoundSoftClassPtr = CurrentMusicSettings.MetaSoundSource;
	MusicSoftClassPtr = CurrentMusicSettings.MusicSource;
	
	if (IsValid(BackgroundMusic))
	{
		bMusicHasIntro = false;

		BackgroundMusic->SetObjectParameter("Wave Asset", CurrentMusicSettings.MusicSource);
		BackgroundMusic->SetFloatParameter("Start Time", CurrentMusicSettings.StartTime);

		GetWorld()->GetTimerManager().SetTimer(MusicTimecode, this, &ThisClass::TickMusicTimecode, 0.001f, true);

		const AAoS_GameMode* GameMode = GameInstance->GetGameMode();
		if (!IsValid(GameMode)) {return nullptr;}
		
		if (CurrentMusicSettings.bShouldFade)
		{
			const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameMode->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
			BackgroundMusic->FadeIn(FadeInDuration);
		}
		else
		{
			BackgroundMusic->Play();
		}
		OnBackgroundMusicStarted.Broadcast();
		bMusicIsPlaying = true;
		bMusicIsPaused = false;
		return BackgroundMusic;
	}
	return nullptr;
}

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusicLoopWithIntro(FAoS_MusicSettings InMusicSettings)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GameInstance, InMusicSettings.MetaSoundSource, InMusicSettings.VolumeMultiplier, InMusicSettings.PitchMultiplier, InMusicSettings.StartTime, nullptr, true);

	CurrentMusicSettings = InMusicSettings;
	
	MetaSoundSoftClassPtr = CurrentMusicSettings.MetaSoundSource;
	MusicSoftClassPtr = CurrentMusicSettings.MusicSource;
	
	if (IsValid(BackgroundMusic))
	{
		bMusicHasIntro = true;
		MusicLoopStart = CurrentMusicSettings.LoopStart;
		
		BackgroundMusic->SetObjectParameter("Wave Asset", CurrentMusicSettings.MusicSource);
		BackgroundMusic->SetFloatParameter("Start Time", CurrentMusicSettings.StartTime);
		BackgroundMusic->SetFloatParameter("Loop Start", CurrentMusicSettings.LoopStart);

		GetWorld()->GetTimerManager().SetTimer(MusicTimecode, this, &ThisClass::TickMusicTimecode, 0.001f, true);

		if (CurrentMusicSettings.bShouldFade)
		{
			const AAoS_GameMode* GameMode = GameInstance->GetGameMode();
			if (!IsValid(GameMode)) {return nullptr;}
			
			const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameMode->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
			BackgroundMusic->FadeIn(FadeInDuration);
		}
		else
		{
			BackgroundMusic->Play();
		}
		OnBackgroundMusicStarted.Broadcast();
		bMusicIsPlaying = true;
		bMusicIsPaused = false;
		return BackgroundMusic;
	}
	return nullptr;
}

void UAoS_MusicManager::PauseMusicWithFade()
{
	if (!IsValid(BackgroundMusic))
	{
		return;
	}
	
	const AAoS_GameMode* GameMode = GameInstance->GetGameMode();
	if (!IsValid(GameMode)) {return;}

	const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameMode->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
	
	MusicTimeAtPause += FadeInDuration;
	MusicVolumeAtPause = CurrentMusicSettings.VolumeMultiplier;
	MusicPitchAtPause = CurrentMusicSettings.PitchMultiplier;

	bMusicIsPaused = true;
	OnBackgroundMusicPaused.Broadcast();

	GetWorld()->GetTimerManager().PauseTimer(MusicTimecode);
	
	StopBackgroundMusic(true, 0);
	
}

void UAoS_MusicManager::ResumeMusicWithFade()
{
	CurrentMusicSettings.MetaSoundSource = MetaSoundSoftClassPtr.Get();
	CurrentMusicSettings.MusicSource = MusicSoftClassPtr.Get();
	if (IsValid(CurrentMusicSettings.MetaSoundSource) && IsValid(CurrentMusicSettings.MusicSource))
	{
		bMusicIsPaused = false;
		GetWorld()->GetTimerManager().UnPauseTimer(MusicTimecode);

		if (bMusicHasIntro)
		{
			PlayBackgroundMusicLoopWithIntro(CurrentMusicSettings);
		}
		else
		{
			PlayBackgroundMusic(CurrentMusicSettings);
		}
	}
}

void UAoS_MusicManager::StopBackgroundMusic(bool bShouldFade, float FadeVolumeLevel)
{
	if (IsValid(BackgroundMusic))
	{
		if (bShouldFade)
		{
			const AAoS_GameMode* GameMode = GameInstance->GetGameMode();
			if (!IsValid(GameMode)) {return;}
			
			const float FadeOutDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameMode->GlobalFadeOutDuration : CurrentMusicSettings.FadeOutDuration;
			BackgroundMusic->FadeOut(FadeOutDuration, FadeVolumeLevel);
		}
		else
		{
			BackgroundMusic->Stop();
		}
		if (!bMusicIsPaused)
		{
			GetWorld()->GetTimerManager().ClearTimer(MusicTimecode);
			OnBackgroundMusicStopped.Broadcast();
		}
		BackgroundMusic->DestroyComponent();
		bMusicIsPlaying = false;
	}
}
