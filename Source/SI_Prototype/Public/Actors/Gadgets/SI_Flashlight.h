// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_BaseGadget.h"
#include "SI_Flashlight.generated.h"


class USpotLightComponent;


UCLASS()
class SI_PROTOTYPE_API ASI_Flashlight : public ASI_BaseGadget
{
	GENERATED_BODY()

	ASI_Flashlight();

public:	
	void UsePrimary();
	
private:

	/*UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* FlashlightMesh;*/
	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	USpotLightComponent* Spotlight;
	
	//UPROPERTY(EditAnywhere, Category = Spotlight)
	//float LightBrightness;

	UPROPERTY(EditAnywhere, Category = Spotlight)
	bool bFlashlightOn;

	/*UPROPERTY(EditAnywhere, Category = SectionalPieces)
	int SegmentsPlaced;
	
	UPROPERTY(EditAnywhere, Category = SectionalPieces)
	int MaxPlaceableSegments;#1#*/

	
};
