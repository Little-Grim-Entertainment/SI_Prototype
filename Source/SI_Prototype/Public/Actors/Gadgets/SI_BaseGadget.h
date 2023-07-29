// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SI_BaseGadget.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_BaseGadget : public AActor
{
	GENERATED_BODY()

public:
	FGameplayTag GadgetIDTag;

	virtual void ActivatePrimaryAction();
	virtual void ActivateSecondaryAction();
	virtual void CancelPrimaryAction();
	virtual void CancelSecondaryAction();
};
