// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once

#include "CoreMinimal.h"
#include "Widget/Blueprint/HorizonUserWidget.h"
#include "HorizonDesignableUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HORIZONUI_API UHorizonDesignableUserWidget : public UHorizonUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI")
	virtual void SynchronizeProperties() override;
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "HorizonPlugin|UI")
	void OnSynchronizeProperties();
	virtual void OnSynchronizeProperties_Implementation() {};
};
