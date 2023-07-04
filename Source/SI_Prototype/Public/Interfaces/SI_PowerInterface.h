// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SI_PowerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USI_PowerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SI_PROTOTYPE_API ISI_PowerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Power")
	void OnPowerReceived(AActor* Caller, float InPower);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Power")
	void OnPowerLost(AActor* Caller, float InPower);
};
