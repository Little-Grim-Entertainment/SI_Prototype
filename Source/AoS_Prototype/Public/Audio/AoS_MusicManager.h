// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AoS_MusicManager.generated.h"

UCLASS()
class AOS_PROTOTYPE_API UAoS_MusicManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Music")
	void PlayBackgroundMusicLoopWithIntro(USoundBase* MetaSoundSource, USoundBase* MusicToPlay, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, float LoopStart = 0.f);

	UFUNCTION(BlueprintCallable, Category = "Music")
	void StopBackgroundMusic(bool bShouldFade, float FadeOutDurration, float FadeVolumeLevel);
	
private:

	UPROPERTY()
	UAudioComponent* BackgroundMusic;
};
