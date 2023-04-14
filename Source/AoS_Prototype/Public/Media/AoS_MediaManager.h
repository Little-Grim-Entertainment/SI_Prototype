// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "Media/AoS_MediaTypes.h"

#include "AoS_MediaManager.generated.h"


class UAoS_MediaDataAsset;
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
class AOS_PROTOTYPE_API UAoS_MediaManager : public UAoS_WorldSubsystem
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
	void PlayMedia(UAoS_MediaDataAsset* InMediaToPlay, FAoS_MediaSettings& InMediaSettings);
	UFUNCTION(BlueprintCallable)
	void PlayCinematic(UAoS_CinematicDataAsset* InCinematicToPlay, FAoS_CinematicSettings InCinematicSettings = FAoS_CinematicSettings());
	UFUNCTION(BlueprintCallable)
	void PlayVideo(UAoS_VideoDataAsset* InVideoToPlay, FAoS_VideoSettings InVideoSettings = FAoS_VideoSettings());

	UFUNCTION(BlueprintCallable)
	void SkipMedia(UAoS_MediaDataAsset* InMediaToSkip);
	
	UFUNCTION(BlueprintCallable)
	void ResetCinematicByTag(FGameplayTag InCinematicTag);
	UFUNCTION(BlueprintCallable)
	void ResetAllCinematics();
	
	UFUNCTION(BlueprintCallable)
	void ResetVideoByTag(FGameplayTag InVideoTag);
	UFUNCTION(BlueprintCallable)
	void ResetAllVideos();
	
	UFUNCTION(BlueprintCallable, Category = "Videos")
	void AddToWatchedVideos(UAoS_VideoDataAsset* InVideoToAdd);
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void AddToWatchedCinematics(UAoS_CinematicDataAsset* InCinematicToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "Videos")
	void RemoveFromWatchedVideos(UAoS_VideoDataAsset* InVideoToRemove);
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void RemoveFromWatchedCinematics(UAoS_CinematicDataAsset* InCinematicToRemove);

	UFUNCTION(BlueprintPure)
	bool HasMediaPlayed(UAoS_MediaDataAsset* InMediaDataAsset);
	
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
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag) override;
	
private:

	UPROPERTY()
	UAoS_CinematicDataAsset* LoadedCinematic;	
	UPROPERTY()
	UAoS_VideoDataAsset* LoadedVideo;
	
	UPROPERTY()
	TArray<UAoS_VideoDataAsset*> WatchedVideos;

	UPROPERTY()
	TArray<UAoS_CinematicDataAsset*> WatchedCinematics;

	FSimpleDelegate DelayedCinematicDelegate;
	FSimpleDelegate DelayedVideoDelegate;

	UFUNCTION()
	void DelayedVideoPlay(UAoS_MapData* LoadedLevel, bool bShouldFade);
	UFUNCTION()
	void DelayedCinematicPlay(UAoS_MapData* LoadedLevel, bool bShouldFade);
};
