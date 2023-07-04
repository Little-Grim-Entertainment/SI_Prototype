// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SI_InteractableActor.h"
#include "Components/SphereComponent.h"
#include "SI_FlashlightSegment.generated.h"

DECLARE_DELEGATE_OneParam(FSegmentPickedUp, int);

class UPointLightComponent;
class ASI_Nick;

UCLASS()
class SI_PROTOTYPE_API ASI_FlashlightSegment : public ASI_InteractableActor
{
	GENERATED_BODY()
	
public:
	ASI_FlashlightSegment();

	FSegmentPickedUp SegmentPickUpDelegate;	
	
	UPROPERTY(EditAnywhere, Category = LightDome)
	UStaticMeshComponent* LightDome;

	UPROPERTY(EditAnywhere, Category = PowerCollisionMesh)
	USphereComponent* PowerCollisionMesh;

	UPROPERTY(EditAnywhere, Category = Segment)
	UPointLightComponent* Pointlight;
	
	UPROPERTY(EditAnywhere, Category = Segment)
	float PointlightIntensity;

	UPROPERTY(EditAnywhere, Category = Segment)
	float Power;
	
	int SegmentNumber;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation(AActor* Caller) override;
	void RemoveSegment();

	UFUNCTION()
	void OnPowerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnPowerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void Tick(float DeltaTime) override;

	void InitializeSegment(float InPower);

};
