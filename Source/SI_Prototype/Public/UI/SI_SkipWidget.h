// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_UserWidget.h"
#include "SI_SkipWidget.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_SkipWidget : public USI_UserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnSkipStarted();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnSkipPercentUpdate(float InPercent);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnSkipCanceled();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnSkipComplete();
};
