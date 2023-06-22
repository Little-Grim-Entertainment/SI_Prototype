// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Actors/SI_InteractableActor.h"
#include "SI_BaseGadget.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_BaseGadget : public ASI_InteractableActor
{
	GENERATED_BODY()

public:
	FGameplayTag GadgetIDTag;
};
