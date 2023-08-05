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
	virtual void ActivatePrimaryAction() override;
	virtual void ActivateSecondaryAction() override;
	virtual void CancelPrimaryAction() override;
	virtual void CancelSecondaryAction() override;
	
	void PlaceSegment();
	void BindPickUpSegment();
	void SpawnSegment();
	void SpotlightHandler();
	void PowerIntensityHandler();
	void DebugSpotlightInfo();
	
	UFUNCTION()
	void PickUpSegment(int InSegmentNumber);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_FlashlightSegment> FlashlightSegmentClass = ASI_FlashlightSegment::StaticClass();
	UPROPERTY(EditAnywhere)
	ASI_FlashlightSegment* FlashlightSegment;
	
	UPROPERTY(EditAnywhere, Category = Power)
	float MaxPower;
	UPROPERTY(EditAnywhere, Category = Power)
	float CurrentPower;
	UPROPERTY(EditAnywhere, Category = Spotlight)
	bool bFlashlightOn;
	UPROPERTY(EditAnywhere, Category = SegmentPieces)
	int SegmentsPlaced;	
	UPROPERTY(EditAnywhere, Category = SegmentPiece)
	int MaxPlaceableSegments;	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	float MaxSpotlightIntensity;
	UPROPERTY(EditAnywhere, Category = Spotlight)
	float MaxSpotlightConeAngle;	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	float MaxSpotlightAttenuationRadius;	
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* FirstSegment;
	
private:	
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* SecondSegment;	
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* ThirdSegment;	
	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* FourthSegment;	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	USpotLightComponent* Spotlight;	
	UPROPERTY(EditAnywhere, Category = Spotlight)
	USceneComponent* ConeRootSC;
	UPROPERTY(EditAnywhere, Category = Spotlight)
	UStaticMeshComponent* CollisionCone;
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnConeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnConeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
