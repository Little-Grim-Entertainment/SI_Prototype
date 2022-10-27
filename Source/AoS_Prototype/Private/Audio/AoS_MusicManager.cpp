// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AoS_MusicManager.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UAoS_MusicManager::PlayBackgroundMusicLoopWithIntro(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier, float PitchMultiplier, float StartTime, float LoopStart)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GetWorld(), MetaSoundSource, VolumeMultiplier, PitchMultiplier);
	if (IsValid(BackgroundMusic))
	{
		BackgroundMusic->SetObjectParameter("Wave Asset", MusicToPlay);
		BackgroundMusic->SetFloatParameter("Start Time", StartTime);
		BackgroundMusic->SetFloatParameter("Loop Start", LoopStart);
		BackgroundMusic->Play();
	}
}

void UAoS_MusicManager::StopBackgroundMusic(bool bShouldFade, float FadeOutDurration, float FadeVolumeLevel)
{
	if (IsValid(BackgroundMusic))
	{
		if (bShouldFade)
		{
			BackgroundMusic->FadeOut(FadeOutDurration, FadeVolumeLevel);
		}
		else
		{
			BackgroundMusic->Stop();
		}
	}
}
