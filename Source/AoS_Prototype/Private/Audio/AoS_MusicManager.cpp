// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AoS_MusicManager.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


UAoS_MusicManager::UAoS_MusicManager()
{
	/*const ConstructorHelpers::FObjectFinder<UCurveFloat>Curve(TEXT("/Game/AoS/Curves/C_MusicFadeTimeline.C_MusicFadeTimeline"));
	FadeCurve = Curve.Object;*/
}

TStatId UAoS_MusicManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UAoS_MusicManager, STATGROUP_Tickables);
}

void UAoS_MusicManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UAoS_MusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FadeTimeline.IsPlaying())
	{
		FadeTimeline.TickTimeline(DeltaTime);
	}
}

UAudioComponent* UAoS_MusicManager::PlayBackgroundMusic(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier, float PitchMultiplier, float StartTime, bool bShouldFade, float FadeInDuration)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GetWorld(), MetaSoundSource, VolumeMultiplier, PitchMultiplier);
	if (IsValid(BackgroundMusic))
	{
		BackgroundMusic->SetObjectParameter("Wave Asset", MusicToPlay);
		BackgroundMusic->SetFloatParameter("Start Time", StartTime);

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
	if (IsValid(BackgroundMusic))
	{
		BackgroundMusic->SetObjectParameter("Wave Asset", MusicToPlay);
		BackgroundMusic->SetFloatParameter("Start Time", StartTime);
		BackgroundMusic->SetFloatParameter("Loop Start", LoopStart);
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
	SetFadeCurve(BackgroundMusic->VolumeMultiplier);

	if (!IsValid(FadeCurve))
	{
		return;
	}
	
	FOnTimelineFloat FadeTick;
	FOnTimelineEvent FadeOutComplete;
	
	FadeTick.BindDynamic(this, &ThisClass::TickMusicFade);
	FadeOutComplete.BindDynamic(this, &ThisClass::OnFadeOutComplete);
	
	FadeTimeline.AddInterpFloat(FadeCurve, FadeTick);
	FadeTimeline.SetTimelineFinishedFunc(FadeOutComplete);
	FadeTimeline.SetPlayRate(FadeOutDuration + 1.0f);

	FadeTimeline.ReverseFromEnd();
}

void UAoS_MusicManager::ResumeMusicWithFade(const float FadeInDuration)
{
	if (!IsValid(FadeCurve))
	{
		return;
	}
	
	FOnTimelineFloat FadeTick;
	FOnTimelineEvent FadeOutComplete;
	
	FadeTick.BindDynamic(this, &ThisClass::TickMusicFade);
	FadeOutComplete.BindDynamic(this, &ThisClass::OnFadeOutComplete);

	FadeTimeline.AddInterpFloat(FadeCurve, FadeTick);
	FadeTimeline.SetTimelineFinishedFunc(FadeOutComplete);
	FadeTimeline.SetPlayRate(FadeInDuration + 1.0f);

	if (IsValid(PausedMusic))
	{
		PausedMusic->SetPaused(false);
		BackgroundMusic = PausedMusic;
		PausedMusic = nullptr;
	}
	
	FadeTimeline.PlayFromStart();
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
	}
}

void UAoS_MusicManager::TickMusicFade(float Value)
{
	if (IsValid(BackgroundMusic))
	{
		BackgroundMusic->SetVolumeMultiplier(Value);
	}
}

void UAoS_MusicManager::OnFadeOutComplete()
{
	if (IsValid(PausedMusic))
	{
		PausedMusic->SetPaused(false);
		BackgroundMusic = PausedMusic;
		PausedMusic = nullptr;
	}
	else
	{
		BackgroundMusic->SetPaused(true);
		PausedMusic = BackgroundMusic;
	}
}

void UAoS_MusicManager::SetFadeCurve(float InMaxVolume)
{
	FadeCurve = nullptr;
	FadeCurve = NewObject<UCurveFloat>();
	if (IsValid(FadeCurve))
	{
		FadeCurve->FloatCurve.AddKey(0,0);
		FadeCurve->FloatCurve.AddKey(1, InMaxVolume);
	}
}
