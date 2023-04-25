// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_CinematicsManager.generated.h"


class UAoS_CinematicDataAsset;
class UAoS_VideoDataAsset;
class UAoS_MapData;
class UMediaTexture;
class UMediaSource;
class UMediaPlayer;
class ULevelSequence;
class ULevelSequencePlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVideoBeginPlay, UAoS_VideoDataAsset*, PlayedVideo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVideoEndPlay, UAoS_VideoDataAsset*, EndedVideo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinematicBeginPlay, UAoS_CinematicDataAsset*, PlayedCinematic);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinematicEndPlay, UAoS_CinematicDataAsset*, EndedCinematic);

UCLASS()
class AOS_PROTOTYPE_API UAoS_CinematicsManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnVideoBeginPlay OnVideoBeginPlay;
	UPROPERTY(BlueprintAssignable)
	FOnVideoEndPlay OnVideoEndPlay;
	UPROPERTY(BlueprintAssignable)
	FOnCinematicBeginPlay OnCinematicBeginPlay;
	UPROPERTY(BlueprintAssignable)
	FOnCinematicEndPlay OnCinematicEndPlay;
	
	
	UFUNCTION(BlueprintCallable)
	void PlayCinematic(UAoS_CinematicDataAsset* InCinematicToPlay);
	UFUNCTION(BlueprintCallable)
	void PlayVideo(UAoS_VideoDataAsset* InVideoToPlay, bool bShouldRepeat = false, float InVolume = 1.0f);

	UFUNCTION(BlueprintCallable)
	void ResetCinematicByName(FString InCinematicName);
	UFUNCTION(BlueprintCallable)
	void ResetAllCinematics();
	
	UFUNCTION(BlueprintCallable)
	void ResetVideoByName(FString InVideoName);
	UFUNCTION(BlueprintCallable)
	void ResetAllVideos();

	UFUNCTION(BlueprintCallable)
	void LoadLevelOnVideoComplete(UAoS_MapData* InLevelToLoad, FString InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);
	UFUNCTION(BlueprintCallable)
	void LoadLevelOnCinematicComplete(UAoS_MapData* InLevelToLoad, FString InPlayerStartTag = FString(TEXT("NickSpawn")), bool bAllowDelay = true, bool bShouldFade = true);

	UFUNCTION(BlueprintPure)
	TArray<UAoS_CinematicDataAsset*> GetWatchedCinematics();
	UFUNCTION(BlueprintPure)
	UAoS_CinematicDataAsset* GetLoadedCinematic() const;
	UFUNCTION(BlueprintPure)
	UAoS_VideoDataAsset* GetLoadedVideo() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_VideoDataAsset*> GetWatchedVideos();
	
	UFUNCTION()
	void OnVideoSkipped();
	UFUNCTION()
	void OnVideoEnded();

	UFUNCTION()
	void OnCinematicSkipped();	
	UFUNCTION()
	void OnCinematicEnded();

protected:

	virtual void OnGameModeBeginPlay() override;
	
private:

	UPROPERTY()
	UAoS_CinematicDataAsset* LoadedCinematic;	
	UPROPERTY()
	UAoS_VideoDataAsset* LoadedVideo;

	FSimpleDelegate DelayedLevelLoad;

	UFUNCTION()
	void ExecuteLoadLevelOnVideoComplete();
	UFUNCTION()
	void ExecuteLoadLevelOnCinematicComplete();
	UFUNCTION()
	void DelayedVideoPlay(UAoS_MapData* LoadedLevel, bool bShouldFade);
	UFUNCTION()
	void DelayedCinematicPlay(UAoS_MapData* LoadedLevel, bool bShouldFade);
	
};
