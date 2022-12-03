// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_VideoDataAsset.generated.h"

class UMediaTexture;
class UMediaSource;
class UMediaPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoSkipped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoEnd);

UCLASS()
class AOS_PROTOTYPE_API UAoS_VideoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	FString VideoName;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaPlayer* MediaPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaSource* MediaSource;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaTexture* MediaTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	bool bCanRepeat = false;

	UPROPERTY(BlueprintAssignable, Category = "Videos")
	FOnVideoStart OnVideoStarted;
	UPROPERTY(BlueprintAssignable, Category = "Videos")
	FOnVideoSkipped OnVideoSkipped;
	UPROPERTY(BlueprintAssignable, Category = "Videos")
	FOnVideoEnd OnVideoEnded;

	UFUNCTION(BlueprintPure, Category = "Videos")
	bool GetVideoIsPlaying() const;
	UFUNCTION(BlueprintPure, Category = "Videos")
    bool GetVideoHasPlayed() const;
	UFUNCTION(BlueprintPure, Category = "Videos")
	bool GetVideoWasSkipped() const;

	UFUNCTION(BlueprintCallable)
	void StartVideo();
	UFUNCTION(BlueprintCallable)
	void SkipVideo();

	UFUNCTION(BlueprintCallable)
	void ResetVideoDefaults();


private:
	
	bool bIsPlaying = false;
	bool bHasPlayed = false;
	bool bWasSkipped = false;

	UFUNCTION()
	void OnVideoSkip();
	UFUNCTION()
	void OnVideoEnd();

	void ClearDelegates();

};
