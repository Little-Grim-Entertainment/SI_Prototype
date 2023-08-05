// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_Types.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_MusicManager.generated.h"

class UCurveFloat;
class USI_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundMusicStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundMusicPaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundMusicStopped);

DECLARE_LOG_CATEGORY_EXTERN(LogSI_MusicManager, Log, All);

// This system is responsible for playing, stopping, and pausing the game music

UCLASS()
class SI_PROTOTYPE_API USI_MusicManager : public USI_WorldSubsystem
{
	GENERATED_BODY()

	USI_MusicManager();

public:

	UPROPERTY(BlueprintAssignable)
	FOnBackgroundMusicStarted OnBackgroundMusicStarted;
	UPROPERTY(BlueprintAssignable)
	FOnBackgroundMusicPaused OnBackgroundMusicPaused;
	UPROPERTY(BlueprintAssignable)
	FOnBackgroundMusicPaused OnBackgroundMusicStopped;

	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayLoadedLevelBackgroundMusic();
	
	UFUNCTION(BlueprintCallable, Category = "Music")
	UAudioComponent* PlayBackgroundMusic(FSI_MusicSettings InMusicSettings);
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
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag) override;

private:
	
	FSI_MusicSettings CurrentMusicSettings;
	
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
	
	float MusicTimeAtPause;
	float MusicVolumeAtPause;
	float MusicPitchAtPause;

	UFUNCTION()
	void TickMusicTimecode();
};