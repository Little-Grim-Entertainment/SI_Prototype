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

void UAoS_MusicManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstance))
	{
		GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
	}
}

void UAoS_MusicManager::TickMusicTimecode()
{
	MusicTimeAtPause += .001;
}

void UAoS_MusicManager::OnPlayerModeChanged(EPlayerMode NewPlayerMode)
{
	switch (NewPlayerMode)
	{
		case EPlayerMode::PM_CinematicMode:
			{
				if(IsValid(BackgroundMusic) && !bMusicIsPaused)
				{
					PauseMusicWithFade(.5);
				}
				break;	
			}
		default:
			{
				if(bMusicIsPaused)
				{
					ResumeMusicWithFade(.5);
				}
				break;
			}
	}
}

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusic(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier, float PitchMultiplier, float StartTime, bool bShouldFade, float FadeInDuration)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GetWorld(), MetaSoundSource, VolumeMultiplier, PitchMultiplier);	

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
			BackgroundMusic->FadeIn(FadeInDuration);
		}
		else
		{
			BackgroundMusic->Play();
		}
		
		return BackgroundMusic;
	}
	return nullptr;
}

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusicLoopWithIntro(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier, float PitchMultiplier, float StartTime, float LoopStart, bool bShouldFade, float FadeInDuration)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GetWorld(), MetaSoundSource, VolumeMultiplier, PitchMultiplier);
	
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
			BackgroundMusic->FadeIn(FadeInDuration);
		}
		else
		{
			BackgroundMusic->Play();
		}
		return BackgroundMusic;
	}
	return nullptr;
}

void UAoS_MusicManager::PauseMusicWithFade(const float FadeOutDuration)
{
	if (!IsValid(BackgroundMusic))
	{
		return;
	}
	
	TArray<FActiveSound*> ActiveSounds = BackgroundMusic->GetAudioDevice()->GetActiveSounds();
	

	MusicTimeAtPause += FadeOutDuration;
	MusicVolumeAtPause = BackgroundMusic->VolumeMultiplier;
	MusicPitchAtPause = BackgroundMusic->PitchMultiplier;

	bMusicIsPaused = true;
	GetWorld()->GetTimerManager().PauseTimer(MusicTimecode);
	
	StopBackgroundMusic(true, FadeOutDuration, 0);
}

void UAoS_MusicManager::ResumeMusicWithFade(const float FadeInDuration)
{
	USoundBase* CurrentMetaSound = MetaSoundSoftClassPtr.Get();
	USoundBase* CurrentMusic = MusicSoftClassPtr.Get();
	if (IsValid(CurrentMetaSound) && IsValid(CurrentMusic))
	{
		bMusicIsPaused = false;
		GetWorld()->GetTimerManager().UnPauseTimer(MusicTimecode);

		if (bMusicHasIntro)
		{
			PlayBackgroundMusicLoopWithIntro(CurrentMetaSound, CurrentMusic, MusicVolumeAtPause, MusicPitchAtPause, MusicTimeAtPause, MusicLoopStart, true, FadeInDuration);
		}
		else
		{
			PlayBackgroundMusic(CurrentMetaSound, CurrentMusic, MusicVolumeAtPause, MusicPitchAtPause, MusicTimeAtPause, true, FadeInDuration);
		}
	}
}

void UAoS_MusicManager::StopBackgroundMusic(bool bShouldFade, float FadeOutDuration, float FadeVolumeLevel)
{
	if (IsValid(BackgroundMusic))
	{
		if (bShouldFade)
		{
			BackgroundMusic->FadeOut(FadeOutDuration, FadeVolumeLevel);
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