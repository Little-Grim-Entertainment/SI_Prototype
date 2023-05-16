// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_InteractionWidget.h"
#include "SI_InteractionPrompt.generated.h"

class UTextBlock;

UCLASS()
class SI_PROTOTYPE_API USI_InteractionPrompt : public USI_InteractionWidget
{
	GENERATED_BODY()


public:
	
	UFUNCTION(BlueprintNativeEvent)
	void SetInteractText(const FText& InInteractionText);
	virtual void SetInteractText_Implementation(const FText& InInteractionText);


protected:

	virtual void ShowWidget_Implementation() override;

	UPROPERTY(BlueprintReadOnly)
	FText InteractionText;
};
