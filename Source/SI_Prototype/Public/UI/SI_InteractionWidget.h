// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_UserWidget.h"
#include "SI_InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_InteractionWidget : public USI_UserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void ShowWidget();
	UFUNCTION(BlueprintNativeEvent)
	void HideWidget();
	UFUNCTION(BlueprintNativeEvent)
	void RefreshWidget();
};
