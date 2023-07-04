// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_InteractableActor.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "Interfaces/SI_PowerInterface.h"
#include "SI_PowerActor.generated.h"

class ASI_FlashlightSegment;

UCLASS()
class SI_PROTOTYPE_API ASI_PowerActor : public ASI_InteractableActor, public ISI_PowerInterface
{
	GENERATED_BODY()	
	
public:
	// Sets default values for this actor's properties
	ASI_PowerActor();
	
	UPROPERTY(EditAnywhere, Category = PowerCollisionMesh)
	UBoxComponent* PowerCollisionMesh;

	UPROPERTY(EditAnywhere, Category = Power)
	float CurrentPower;
	
	UPROPERTY(EditAnywhere, Category = Power)
	float RequiredPower;

	UPROPERTY(EditAnywhere, Category = Power)
	bool bIsFullyPowered;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnPowerReceived_Implementation(AActor* Caller, float InPower) override;
	UFUNCTION()
	virtual void OnPowerLost_Implementation(AActor* Caller, float InPower) override;
	UFUNCTION()
	virtual bool HasMaxPower_Implementation() override;

private:
	void UpdatePowerDetails();
};
