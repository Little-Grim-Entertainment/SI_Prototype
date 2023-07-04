// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/SI_InteractionWidget.h"
#include "SI_OptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_OptionWidget : public USI_InteractionWidget
{
	GENERATED_BODY()

public:
	
	virtual void ShowWidget_Implementation() override;
	virtual void HideWidget_Implementation() override;
	virtual void RefreshWidget_Implementation() override;

	FGameplayTag OptionTag;
};
