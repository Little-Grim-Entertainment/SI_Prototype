// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoS_GlobalStructs.generated.h"

class USoundBase;

USTRUCT(BlueprintType)
struct FMusicSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USoundBase* MetaSoundSource;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	USoundBase* MusicSource;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	bool bHasIntro = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="bHasIntro", EditConditionHides))
	float LoopStart = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float VolumeMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float PitchMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	float StartTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	bool bShouldFade = true;
};