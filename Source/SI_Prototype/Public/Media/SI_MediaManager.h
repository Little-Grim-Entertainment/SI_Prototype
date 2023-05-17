// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "Media/SI_MediaTypes.h"

#include "SI_MediaManager.generated.h"


class USI_MediaDataAsset;
class USI_CinematicDataAsset;
class USI_VideoDataAsset;
class USI_MapData;
class UMediaTexture;
class UMediaSource;
class UMediaPlayer;
class ULevelSequence;
class ULevelSequencePlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVideoBeginPlay, USI_VideoDataAsset*, PlayedVideo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVideoEndPlay, USI_VideoDataAsset*, EndedVideo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinematicBeginPlay, USI_CinematicDataAsset*, PlayedCinematic);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinematicEndPlay, USI_CinematicDataAsset*, EndedCinematic);

#if !UE_BUILD_SHIPPING
static TAutoConsoleVariable<int32> CvarDisableAllMedia(
	TEXT("CheatDisableAllMedia"),
	0,
	TEXT("Disables all videos and cinematics.\n")
	TEXT("<=0: enabled\n")
	TEXT("  1: disabled\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);
#endif

UCLASS()
class SI_PROTOTYPE_API USI_MediaManager : public USI_WorldSubsystem
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
	void PlayMedia(USI_MediaDataAsset* InMediaToPlay, FSI_MediaSettings& InMediaSettings);
	UFUNCTION(BlueprintCallable)
	void PlayCinematic(USI_CinematicDataAsset* InCinematicToPlay, FSI_CinematicSettings InCinematicSettings = FSI_CinematicSettings());
	UFUNCTION(BlueprintCallable)
	void PlayVideo(USI_VideoDataAsset* InVideoToPlay, FSI_VideoSettings InVideoSettings = FSI_VideoSettings());

	UFUNCTION(BlueprintCallable)
	void SkipMedia(USI_MediaDataAsset* InMediaToSkip);
	
	UFUNCTION(BlueprintCallable)
	void ResetCinematicByTag(FGameplayTag InCinematicTag);
	UFUNCTION(BlueprintCallable)
	void ResetAllCinematics();
	
	UFUNCTION(BlueprintCallable)
	void ResetVideoByTag(FGameplayTag InVideoTag);
	UFUNCTION(BlueprintCallable)
	void ResetAllVideos();
	
	UFUNCTION(BlueprintCallable, Category = "Videos")
	void AddToWatchedVideos(USI_VideoDataAsset* InVideoToAdd);
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void AddToWatchedCinematics(USI_CinematicDataAsset* InCinematicToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "Videos")
	void RemoveFromWatchedVideos(USI_VideoDataAsset* InVideoToRemove);
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void RemoveFromWatchedCinematics(USI_CinematicDataAsset* InCinematicToRemove);

	UFUNCTION(BlueprintPure)
	bool HasMediaPlayed(USI_MediaDataAsset* InMediaDataAsset);
	
	UFUNCTION(BlueprintPure)
	TArray<USI_CinematicDataAsset*> GetWatchedCinematics();
	UFUNCTION(BlueprintPure)
	USI_CinematicDataAsset* GetLoadedCinematic() const;
	UFUNCTION(BlueprintPure)
	USI_VideoDataAsset* GetLoadedVideo() const;
	UFUNCTION(BlueprintPure)
	TArray<USI_VideoDataAsset*> GetWatchedVideos();
	
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
	USI_CinematicDataAsset* LoadedCinematic;	
	UPROPERTY()
	USI_VideoDataAsset* LoadedVideo;
	
	UPROPERTY()
	TArray<USI_VideoDataAsset*> WatchedVideos;

	UPROPERTY()
	TArray<USI_CinematicDataAsset*> WatchedCinematics;

	FSimpleDelegate DelayedCinematicDelegate;
	FSimpleDelegate DelayedVideoDelegate;

	UFUNCTION()
	void DelayedVideoPlay(USI_MapData* LoadedLevel, bool bShouldFade);
	UFUNCTION()
	void DelayedCinematicPlay(USI_MapData* LoadedLevel, bool bShouldFade);
};
