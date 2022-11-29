// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AoS_InteractInterface.generated.h"

class UWidgetComponent;

UINTERFACE(MinimalAPI)
class UAoS_InteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AOS_PROTOTYPE_API IAoS_InteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	UWidgetComponent* GetInteractionPromptComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	UWidgetComponent* GetInteractionIconComponent();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(AActor* Caller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnObserved(AActor* Caller);

};
