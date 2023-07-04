// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SI_MovableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USI_MovableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SI_PROTOTYPE_API ISI_MovableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnPossessMovable(AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnEndPossessMovable(AActor* Caller);
};
