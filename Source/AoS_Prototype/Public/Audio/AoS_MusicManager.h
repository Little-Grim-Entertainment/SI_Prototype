// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_MusicManager.generated.h"

class UCurveFloat;

// This system is responsible for playing, stopping, and pausing the game music

UCLASS()
class AOS_PROTOTYPE_API UAoS_MusicManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

	UAoS_MusicManager();

public:
	
	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayBackgroundMusic(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, bool bShouldFade = false);
	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayBackgroundMusicLoopWithIntro(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, float LoopStart = 0.f, bool bShouldFade = false);
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PauseMusicWithFade();
	UFUNCTION(BlueprintCallable, Category = "Music")
	void ResumeMusicWithFade();

	UFUNCTION(BlueprintCallable, Category = "Music")
	void StopBackgroundMusic(bool bShouldFade, float FadeVolumeLevel);

protected:

	virtual void OnPlayerModeChanged(EPlayerMode NewPlayerMode) override;

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