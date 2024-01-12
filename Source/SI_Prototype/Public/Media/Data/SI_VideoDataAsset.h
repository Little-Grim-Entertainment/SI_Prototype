// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Media/Data/SI_MediaDataAsset.h"
#include "SI_VideoDataAsset.generated.h"

class UMediaTexture;
class UMediaSource;
class UMediaPlayer;

UCLASS()
class SI_PROTOTYPE_API USI_VideoDataAsset : public USI_MediaDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaPlayer* MediaPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaSource* MediaSource;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	UMediaTexture* MediaTexture;
};
