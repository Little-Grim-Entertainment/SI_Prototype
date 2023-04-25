// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AoS_MusicManager.h"
#include "AoS_GameInstance.h"
#include "AudioDevice.h"
#include "Components/AudioComponent.h"
#include "Data/Maps/AoS_MapData.h"
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

	UAoS_LevelManager* LevelManager = GameInstance->GetLevelManager();
	if (IsValid(LevelManager))
	{
		LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::OnLevelLoaded);
		LevelManager->OnLevelUnloaded.AddDynamic(this, &ThisClass::OnLevelUnloaded);
	}
}

void UAoS_MusicManager::OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode)
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
}

void UAoS_MusicManager::OnLevelLoaded(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	if (!LoadedLevel) {return;}

	LoadedLevel->PlayLevelBackgroundMusic(this);
}

void UAoS_MusicManager::OnLevelUnloaded(UAoS_MapData* UnloadedLevel)
{
	StopBackgroundMusic(true, 0);
}


UAudioComponent* UAoS_MusicManager::PlayBackgroundMusic(FMusicSettings InMusicSettings)
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
		
		if (CurrentMusicSettings.bShouldFade)
		{
			const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameInstance->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
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

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusicLoopWithIntro(FMusicSettings InMusicSettings)
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
			const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameInstance->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
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

	const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameInstance->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
	
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
			const float FadeOutDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameInstance->GlobalFadeOutDuration : CurrentMusicSettings.FadeOutDuration;
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
