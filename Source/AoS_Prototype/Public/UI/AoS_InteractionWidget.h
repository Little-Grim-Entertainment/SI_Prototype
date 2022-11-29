// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_InteractionWidget : public UAoS_UserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void ShowWidget();
	UFUNCTION(BlueprintNativeEvent)
	void HideWidget();
	UFUNCTION(BlueprintNativeEvent)
	void RefreshWidget();

protected:

	virtual void ShowWidget_Implementation();
	virtual void HideWidget_Implementation();
	virtual void RefreshWidget_Implementation();	
};
