// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_CinematicsManager.generated.h"


class UMediaTexture;
class UMediaSource;
class UMediaPlayer;
class ULevelSequence;
class ULevelSequencePlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoEnd);

UCLASS()
class AOS_PROTOTYPE_API UAoS_CinematicsManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Videos")
	FOnVideoEnd OnVideoEnded;
	
	UFUNCTION(BlueprintCallable)
	void PlayCinematic(ULevelSequence* LevelSequenceToPlay, bool bAutoPlay = false, int32 Loop = 0, float PlayRate = 1.0f, float StartOffset = 0.0f, bool bRandomStartTime = false, bool bRestoreState = false, bool bDisableMovementInput = false, bool bDisableLookInput = false, bool bHidePlayer = false, bool bHideHud = false, bool bDisableCameraCuts = false, bool bPauseAtEnd = false);
	UFUNCTION(BlueprintCallable)
	void PlayVideo(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, UMediaTexture* InMediaTexture, float InVolume = 1.0f);

	UFUNCTION(BlueprintPure)
	ULevelSequencePlayer* GetCurrentCinematic() const;
	UFUNCTION(BlueprintPure)
	UMediaPlayer* GetCurrentMediaPlayer() const;
	UFUNCTION(BlueprintPure)
	UMediaSource* GetCurrentMediaSource() const;
	UFUNCTION(BlueprintPure)
	UMediaTexture* GetCurrentMediaTexture() const;

	UFUNCTION()
	void OnVideoEnd();

private:

	UPROPERTY()
	ULevelSequencePlayer* CurrentCinematic;
	UPROPERTY()
	UMediaPlayer* CurrentMediaPlayer;
	UPROPERTY()
	UMediaSource* CurrentMediaSource;
	UPROPERTY()
	UMediaTexture* CurrentMediaTexture;

	EPlayerMode PreviousPlayerMode;
	
	UFUNCTION()
	void OnCinematicEnd();
	
};
