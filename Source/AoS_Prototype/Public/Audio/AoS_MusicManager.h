// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoS_GlobalStructs.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_MusicManager.generated.h"

class UCurveFloat;
class UAoS_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundMusicStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundMusicPaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundMusicStopped);


// This system is responsible for playing, stopping, and pausing the game music

UCLASS()
class AOS_PROTOTYPE_API UAoS_MusicManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

	UAoS_MusicManager();

public:

	UPROPERTY(BlueprintAssignable)
	FOnBackgroundMusicStarted OnBackgroundMusicStarted;
	UPROPERTY(BlueprintAssignable)
	FOnBackgroundMusicPaused OnBackgroundMusicPaused;
	UPROPERTY(BlueprintAssignable)
	FOnBackgroundMusicPaused OnBackgroundMusicStopped;
	
	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayBackgroundMusic(FMusicSettings InMusicSettings);
	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayBackgroundMusicLoopWithIntro(FMusicSettings InMusicSettings);
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PauseMusicWithFade();
	UFUNCTION(BlueprintCallable, Category = "Music")
	void ResumeMusicWithFade();

	UFUNCTION(BlueprintCallable, Category = "Music")
	void StopBackgroundMusic(bool bShouldFade, float FadeVolumeLevel);

	UFUNCTION(BlueprintPure, Category = "Music")
	bool GetBackgroundMusicIsPlaying() const {return bMusicIsPlaying;}

protected:

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode) override;

	UFUNCTION()
	void OnLevelLoaded(UAoS_MapData* LoadedLevel, bool bShouldFade);
	UFUNCTION()
	void OnLevelUnloaded(UAoS_MapData* UnloadedLevel);

private:
	
	FMusicSettings CurrentMusicSettings;
	
	UPROPERTY()
	UAudioComponent* BackgroundMusic;
	UPROPERTY()
	UCurveFloat* FadeCurve;
	UPROPERTY()
	TSoftObjectPtr<USoundBase> MetaSoundSoftClassPtr;
	UPROPERTY()
	TSoftObjectPtr<USoundBase> MusicSoftClassPtr;

	FTimerHandle MusicTimecode;

	bool bMusicIsPlaying;
	bool bMusicIsPaused;
	bool bMusicHasIntro;
	float MusicTimeAtPause;
	float MusicVolumeAtPause;
	float MusicPitchAtPause;
	float MusicLoopStart;

	UFUNCTION()
	void TickMusicTimecode();
};