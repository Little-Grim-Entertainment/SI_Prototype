// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "SI_AIInterface.generated.h"

using namespace SI_NativeGameplayTagLibrary;

struct FGameplayTagContainer;

// This class does not need to be modified.
UINTERFACE()
class USI_AIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SI_PROTOTYPE_API ISI_AIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	void OnUpdateBehaviorTag(FVector TargetLocation);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	void OnUpdateTargetRotation(FRotator TargeRotation);
};
