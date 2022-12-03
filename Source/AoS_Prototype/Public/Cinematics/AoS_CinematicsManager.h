// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_CinematicsManager.generated.h"


class UAoS_VideoDataAsset;
class UAoS_MapData;
class UMediaTexture;
class UMediaSource;
class UMediaPlayer;
class ULevelSequence;
class ULevelSequencePlayer;

UCLASS()
class AOS_PROTOTYPE_API UAoS_CinematicsManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void PlayCinematic(ULevelSequence* LevelSequenceToPlay, bool bAutoPlay = false, int32 Loop = 0, float PlayRate = 1.0f, float StartOffset = 0.0f, bool bRandomStartTime = false, bool bRestoreState = false, bool bDisableMovementInput = false, bool bDisableLookInput = false, bool bHidePlayer = false, bool bHideHud = false, bool bDisableCameraCuts = false, bool bPauseAtEnd = false);
	UFUNCTION(BlueprintCallable)
	void PlayVideo(UAoS_VideoDataAsset* InVideoToPlay, bool bShouldRepeat, float InVolume = 1.0f);

	UFUNCTION(BlueprintCallable)
	void ResetVideoByName(FString InVideoName);
	UFUNCTION(BlueprintCallable)
	void ResetAllVideos();

	UFUNCTION(BlueprintPure)
	ULevelSequencePlayer* GetCurrentCinematic() const;
	UFUNCTION(BlueprintPure)
	UAoS_VideoDataAsset* GetLoadedVideo() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_VideoDataAsset*>& GetWatchedVideos();
	
	UFUNCTION()
	void OnVideoSkipped();
	UFUNCTION()
	void OnVideoEnded();

protected:

	virtual void OnGameModeBeginPlay() override;
	
private:

	UPROPERTY()
	ULevelSequencePlayer* CurrentCinematic;
	UPROPERTY()
	UAoS_VideoDataAsset* LoadedVideo;
	
	EPlayerMode PreviousPlayerMode;
	
	UFUNCTION()
	void OnCinematicEnd();
	UFUNCTION()
	void DelayedVideoPlay(UAoS_MapData* LoadedLevel, bool bShouldFade);
	
};
