// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_BaseGadget.h"
#include "SI_FlashlightSegment.h"
#include "SI_Flashlight.generated.h"

class USpotLightComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_Flashlight : public ASI_BaseGadget
{
	GENERATED_BODY()

	ASI_Flashlight();	

public:	
	void UsePrimary();
	void UseSecondary();
	void PlaceSegment();
	void BindPickUpSegment();

	UFUNCTION()
	void PickUpSegment(int InSegmentNumber);	
	void SpawnSegment();
	
	UFUNCTION()
	void ExecuteTrace();	
	// UFUNCTION()
	// void StopPowerTrace();
	
	void LightIntensityHandler();

	
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_FlashlightSegment> FlashlightSegmentClass = ASI_FlashlightSegment::StaticClass();

	UPROPERTY(EditAnywhere)
	ASI_FlashlightSegment* FlashlightSegment;
	
	UPROPERTY(EditAnywhere, Category = Power)
	float MaxPower;

	UPROPERTY(EditAnywhere, Category = Power)
	float CurrentPower;

	UPROPERTY(EditAnywhere, Category = Power)
	FTimerHandle PowerTraceTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	bool bFlashlightOn;

	UPROPERTY(EditAnywhere, Category = SegmentPieces)
	int SegmentsPlaced;
	
	UPROPERTY(EditAnywhere, Category = SegmentPiece)
	int MaxPlaceableSegments;

	
	
private:

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* FirstSegment;
	
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* SecondSegment;
	
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* ThirdSegment;
	
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* FourthSegment;
	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	USpotLightComponent* Spotlight;
	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	float MaxSpotlightIntensity;
	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	float CurrentSpotlightIntensity;

	UPROPERTY(EditAnywhere, Category = Spotlight)
	float SpotlightIntensityIncrement;
	

protected:
	virtual void BeginPlay() override;
	
};
