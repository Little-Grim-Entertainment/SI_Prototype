// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_InteractableActor.h"
#include "Interfaces/SI_PowerInterface.h"
#include "SI_PowerActor.generated.h"

class UBoxComponent;
class ASI_FlashlightSegment;
class ASI_Flashlight;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFullyPowered, bool, bIsFullyPowered);

UCLASS()
class SI_PROTOTYPE_API ASI_PowerActor : public ASI_InteractableActor, public ISI_PowerInterface
{
	GENERATED_BODY()	
	
public:
	// Sets default values for this actor's properties
	ASI_PowerActor();

	UPROPERTY(EditAnywhere, Category = Flashlight)
	ASI_Flashlight* Flashlight;
	FOnFullyPowered OnFullyPowered;
	
	// todo: declare flashlight variable
	UPROPERTY(EditAnywhere, Category = PowerCollisionMesh)
	UBoxComponent* PowerCollisionMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
	float CurrentPower;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
	float RequiredPower;
	UPROPERTY(EditAnywhere, Category = Power)
	bool bIsFullyPowered;
	UPROPERTY(EditAnywhere, Category = Flashlight)
	bool bIsFlashlightPowered;
	UPROPERTY(EditAnywhere, Category = Flashlight)
	bool bIsFlashlightSet;
	UPROPERTY(EditAnywhere, Category = Flashlight)
	float FlashlightPowerContribution;
	UPROPERTY(EditAnywhere, Category = Flashlight)
	float SegmentPowerContribution;
	
	
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInstance* MaterialPoweredOff;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInstance* MaterialPoweredOn;
	
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
	virtual void OnFlashlightPowerReceived_Implementation(AActor* Caller, float InPower) override;
	UFUNCTION()
	virtual void OnFlashlightPowerLost_Implementation(AActor* Caller, float InPower) override;

private:
	void UpdatePowerDetails();
	// todo: remove debug function on completion
	UFUNCTION()
	void PrintDebug();
};
