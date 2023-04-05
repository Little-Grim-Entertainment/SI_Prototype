// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "AoS_VideoDataAsset.generated.h"

class UMediaTexture;
class UMediaSource;
class UMediaPlayer;

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
};
