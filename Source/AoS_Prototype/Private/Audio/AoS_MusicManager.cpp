// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AoS_MusicManager.h"
#include "AoS_GameInstance.h"
#include "AudioDevice.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


UAoS_MusicManager::UAoS_MusicManager()
{
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

void UAoS_MusicManager::OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode)
{
	Super::OnPlayerModeChanged(NewPlayerMode, InPreviousPlayerMode);
	
	switch (NewPlayerMode)
	{
		case EPlayerMode::PM_CinematicMode:
		{
			if(IsValid(BackgroundMusic) && !bMusicIsPaused)
			{
				PauseMusicWithFade();
			}
			break;	
		}
		case EPlayerMode::PM_VideoMode:
		{
			if(IsValid(BackgroundMusic) && !bMusicIsPaused)
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

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusic(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier, float PitchMultiplier, float StartTime, bool bShouldFade)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GameInstance, MetaSoundSource, VolumeMultiplier, PitchMultiplier, StartTime, nullptr, true);	

	MetaSoundSoftClassPtr = MetaSoundSource;
	MusicSoftClassPtr = MusicToPlay;
	
	if (IsValid(BackgroundMusic))
	{
		bMusicHasIntro = false;

		BackgroundMusic->SetObjectParameter("Wave Asset", MusicToPlay);
		BackgroundMusic->SetFloatParameter("Start Time", StartTime);

		GetWorld()->GetTimerManager().SetTimer(MusicTimecode, this, &ThisClass::TickMusicTimecode, 0.001f, true);
		
		if (bShouldFade)
		{
			BackgroundMusic->FadeIn(GameInstance->AudioFadeInDuration);
		}
		else
		{
			BackgroundMusic->Play();
		}
		
		return BackgroundMusic;
	}
	return nullptr;
}

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusicLoopWithIntro(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier, float PitchMultiplier, float StartTime, float LoopStart, bool bShouldFade)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GameInstance, MetaSoundSource, VolumeMultiplier, PitchMultiplier, StartTime, nullptr, true);
	
	MetaSoundSoftClassPtr = MetaSoundSource;
	MusicSoftClassPtr = MusicToPlay;
	
	if (IsValid(BackgroundMusic))
	{
		bMusicHasIntro = true;
		MusicLoopStart = LoopStart;
		
		BackgroundMusic->SetObjectParameter("Wave Asset", MusicToPlay);
		BackgroundMusic->SetFloatParameter("Start Time", StartTime);
		BackgroundMusic->SetFloatParameter("Loop Start", LoopStart);

		GetWorld()->GetTimerManager().SetTimer(MusicTimecode, this, &ThisClass::TickMusicTimecode, 0.001f, true);

		if (bShouldFade)
		{
			BackgroundMusic->FadeIn(GameInstance->AudioFadeInDuration);
		}
		else
		{
			BackgroundMusic->Play();
		}
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

	MusicTimeAtPause += GameInstance->AudioFadeInDuration;
	MusicVolumeAtPause = BackgroundMusic->VolumeMultiplier;
	MusicPitchAtPause = BackgroundMusic->PitchMultiplier;

	bMusicIsPaused = true;
	GetWorld()->GetTimerManager().PauseTimer(MusicTimecode);
	
	StopBackgroundMusic(true, 0);
}

void UAoS_MusicManager::ResumeMusicWithFade()
{
	USoundBase* CurrentMetaSound = MetaSoundSoftClassPtr.Get();
	USoundBase* CurrentMusic = MusicSoftClassPtr.Get();
	if (IsValid(CurrentMetaSound) && IsValid(CurrentMusic))
	{
		bMusicIsPaused = false;
		GetWorld()->GetTimerManager().UnPauseTimer(MusicTimecode);

		if (bMusicHasIntro)
		{
			PlayBackgroundMusicLoopWithIntro(CurrentMetaSound, CurrentMusic, MusicVolumeAtPause, MusicPitchAtPause, MusicTimeAtPause, MusicLoopStart, true);
		}
		else
		{
			PlayBackgroundMusic(CurrentMetaSound, CurrentMusic, MusicVolumeAtPause, MusicPitchAtPause, MusicTimeAtPause, true);
		}
	}
}

void UAoS_MusicManager::StopBackgroundMusic(bool bShouldFade, float FadeVolumeLevel)
{
	if (IsValid(BackgroundMusic))
	{
		if (bShouldFade)
		{
			BackgroundMusic->FadeOut(GameInstance->AudioFadeInDuration, FadeVolumeLevel);
		}
		else
		{
			BackgroundMusic->Stop();
		}
		if (!bMusicIsPaused)
		{
			GetWorld()->GetTimerManager().ClearTimer(MusicTimecode);
		}
	}
}
