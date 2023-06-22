// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SI_InteractableActor.h"
#include "SI_FlashlightSegment.generated.h"

DECLARE_DELEGATE_OneParam(FSegmentPickedUp, int);

class UPointLightComponent;
class ASI_Nick;
class ASI_Flashlight;

UCLASS()
class SI_PROTOTYPE_API ASI_FlashlightSegment : public ASI_InteractableActor
{
	GENERATED_BODY()
	
public:
	ASI_FlashlightSegment();
	
	UPROPERTY(EditAnywhere, Category = LightDome)
	UStaticMeshComponent* LightDome;

	UPROPERTY(EditAnywhere, Category = Segment)
	UPointLightComponent* Pointlight;

	UPROPERTY(EditAnywhere, Category = Segment)
	float PointlightIntensity;

	FSegmentPickedUp SegmentPickUpDelegate;

	int SegmentNumber;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation(AActor* Caller) override;
	void RemoveSegment();
	

public:
	virtual void Tick(float DeltaTime) override;
};
