// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "AoS_MusicManager.generated.h"

class UCurveFloat;

// This system is responsible for playing, stopping, and pausing the game music

UCLASS()
class AOS_PROTOTYPE_API UAoS_MusicManager : public UWorldSubsystem
{
	GENERATED_BODY()

	UAoS_MusicManager();

public:
	
	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayBackgroundMusic(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, bool bShouldFade = false, float FadeInDuration = 0.f);
	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayBackgroundMusicLoopWithIntro(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, float LoopStart = 0.f, bool bShouldFade = false, float FadeInDuration = 0.0f);
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PauseMusicWithFade(const float FadeOutDuration);
	UFUNCTION(BlueprintCallable, Category = "Music")
	void ResumeMusicWithFade(const float FadeInDuration);

	UFUNCTION(BlueprintCallable, Category = "Music")
	void StopBackgroundMusic(bool bShouldFade, float FadeOutDuration, float FadeVolumeLevel);

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	
	UPROPERTY()
	UAudioComponent* BackgroundMusic;
	UPROPERTY()
	UCurveFloat* FadeCurve;
	UPROPERTY()
	TSoftObjectPtr<USoundBase> MetaSoundSoftClassPtr;
	UPROPERTY()
	TSoftObjectPtr<USoundBase> MusicSoftClassPtr;

	FTimerHandle MusicTimecode;

	bool bMusicIsPaused;
	bool bMusicHasIntro;
	float MusicTimeAtPause;
	float MusicVolumeAtPause;
	float MusicPitchAtPause;
	float MusicLoopStart;

	UFUNCTION()
	void TickMusicTimecode();
};