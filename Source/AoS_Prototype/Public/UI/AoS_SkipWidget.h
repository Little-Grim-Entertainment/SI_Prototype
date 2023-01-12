// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_SkipWidget.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_SkipWidget : public UAoS_UserWidget
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
