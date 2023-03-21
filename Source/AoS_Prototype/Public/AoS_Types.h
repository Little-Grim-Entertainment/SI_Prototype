// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AoS_Types.generated.h"

class USoundBase;
class UInputAction;

USTRUCT(BlueprintType)
struct FAoS_MusicSettings
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="bShouldFade", EditConditionHides))
	bool bUseGlobalFadeSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="!bUseGlobalFadeSettings", EditConditionHides))
	float FadeInDuration = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music", meta=(EditCondition="!bUseGlobalFadeSettings", EditConditionHides))
	float FadeOutDuration = 5.0f;
};

USTRUCT(BlueprintType)
struct FAoS_InputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction; 

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;
};