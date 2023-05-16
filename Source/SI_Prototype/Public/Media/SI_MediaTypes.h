// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_MediaTypes.generated.h"

USTRUCT(BlueprintType)
struct FSI_MediaSettings
{
	GENERATED_BODY()
	
	FSI_MediaSettings() {}
};

USTRUCT(BlueprintType)
struct FSI_VideoSettings : public FSI_MediaSettings
{
	GENERATED_BODY()

	FSI_VideoSettings(bool bInShouldRepeat = false, float InVolume = 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldRepeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Volume;
};

USTRUCT(BlueprintType)
struct FSI_CinematicSettings : public FSI_MediaSettings
{
	GENERATED_BODY()

	FSI_CinematicSettings() {}
};
