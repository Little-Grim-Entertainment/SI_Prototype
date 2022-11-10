// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Components/TimelineComponent.h"

#include "AoS_MusicManager.generated.h"

class UCurveFloat;

UCLASS()
class AOS_PROTOTYPE_API UAoS_MusicManager : public UTickableWorldSubsystem
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

	TStatId GetStatId() const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;

	FTimeline FadeTimeline;

	UFUNCTION()
	void TickMusicFade(float Value);
	UFUNCTION()
	void OnFadeOutComplete();

private:
	
	UPROPERTY()
	UAudioComponent* BackgroundMusic;
	UPROPERTY()
	UAudioComponent* PausedMusic;
	UPROPERTY()
	UCurveFloat* FadeCurve;

	void SetFadeCurve(float InMaxVolume);
};
