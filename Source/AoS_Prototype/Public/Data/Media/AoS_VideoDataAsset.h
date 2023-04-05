// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "AoS_VideoDataAsset.generated.h"

class UMediaTexture;
class UMediaSource;
class UMediaPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoSkipped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoEnd);

UCLASS()
class AOS_PROTOTYPE_API UAoS_VideoDataAsset : public UAoS_MediaDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaPlayer* MediaPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaSource* MediaSource;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaTexture* MediaTexture;
	

	UPROPERTY(BlueprintAssignable, Category = "Videos")
	FOnVideoStart OnVideoStarted;
	UPROPERTY(BlueprintAssignable, Category = "Videos")
	FOnVideoSkipped OnVideoSkipped;
	UPROPERTY(BlueprintAssignable, Category = "Videos")
	FOnVideoEnd OnVideoEnded;

	virtual void StartMedia() override;
	virtual void SkipMedia() override;

protected:

	virtual void ClearDelegates() override;

private:

	UFUNCTION()
	void OnVideoEnd();
};
