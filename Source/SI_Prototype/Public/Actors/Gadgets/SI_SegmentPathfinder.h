// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "SI_SegmentPathfinder.generated.h"

UCLASS()
class SI_PROTOTYPE_API ASI_SegmentPathfinder : public APawn
{
	GENERATED_BODY()

public:
	// Default Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleHitbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TestStaticMesh;
		
	// Sets default values for this pawn's properties
	ASI_SegmentPathfinder();
	
	void InitializePathfinder(FVector InFlashlightActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
