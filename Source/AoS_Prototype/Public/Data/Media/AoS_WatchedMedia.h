// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_WatchedMedia.generated.h"

class UAoS_CinematicDataAsset;
class UAoS_VideoDataAsset;

UCLASS()
class AOS_PROTOTYPE_API UAoS_WatchedMedia : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Videos")
	void AddToWatchedVideos(UAoS_VideoDataAsset* InVideoToAdd);
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void AddToWatchedCinematics(UAoS_CinematicDataAsset* InCinematicToAdd);
	
	UFUNCTION(BlueprintPure, Category = "Videos")
	TArray<UAoS_VideoDataAsset*>& GetWatchedVideos();
	UFUNCTION(BlueprintPure, Category = "Cinematics")
	TArray<UAoS_CinematicDataAsset*>& GetWatchedCinematics();
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Videos")
	TArray<UAoS_VideoDataAsset*> WatchedVideos;
	UPROPERTY(VisibleAnywhere, Category = "Videos")
	TArray<UAoS_CinematicDataAsset*> WatchedCinematics;
};
