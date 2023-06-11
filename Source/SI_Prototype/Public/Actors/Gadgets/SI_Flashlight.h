// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_BaseGadget.h"
#include "SI_Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_Flashlight : public ASI_BaseGadget
{
	GENERATED_BODY()

	ASI_Flashlight();

public:	
	virtual void OnInteract_Implementation(AActor* Caller) override;
	//VARIABLE DECLARATIONS
	// Spotlight myFlashlight;

private:
	// bool bFlashlightOn;
	// int SegmentsPlaced;
	// int MaxPlaceableSegments
	
};
