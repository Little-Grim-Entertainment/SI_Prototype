// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoS_InteractionWidget.h"
#include "AoS_InteractionPrompt.generated.h"

class UTextBlock;

UCLASS()
class AOS_PROTOTYPE_API UAoS_InteractionPrompt : public UAoS_InteractionWidget
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
