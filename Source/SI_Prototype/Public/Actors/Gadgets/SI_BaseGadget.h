// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SI_BaseGadget.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LogSI_Gadget, Log, All);

UCLASS()
class SI_PROTOTYPE_API ASI_BaseGadget : public AActor
{
	GENERATED_BODY()

public:
	FGameplayTag GadgetIDTag;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivatePrimaryAction();
	virtual void ActivatePrimaryAction_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivateSecondaryAction();
	virtual void ActivateSecondaryAction_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CancelPrimaryAction();
	virtual void CancelPrimaryAction_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CancelSecondaryAction();
	virtual void CancelSecondaryAction_Implementation();
};
