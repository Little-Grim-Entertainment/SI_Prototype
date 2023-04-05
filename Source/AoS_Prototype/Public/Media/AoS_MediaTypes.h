// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoS_MediaTypes.generated.h"

USTRUCT(BlueprintType)
struct FAoS_MediaSettings
{
	GENERATED_BODY()
	
	FAoS_MediaSettings() {}
};

USTRUCT(BlueprintType)
struct FAoS_VideoSettings : public FAoS_MediaSettings
{
	GENERATED_BODY()

	FAoS_VideoSettings(bool bInShouldRepeat = false, float InVolume = 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldRepeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Volume;
};

USTRUCT(BlueprintType)
struct FAoS_CinematicSettings : public FAoS_MediaSettings
{
	GENERATED_BODY()

	FAoS_CinematicSettings() {}
};
