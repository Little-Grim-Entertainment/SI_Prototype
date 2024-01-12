// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SI_SegmentPathfinder.generated.h"

UCLASS()
class SI_PROTOTYPE_API ASI_SegmentPathfinder : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASI_SegmentPathfinder();
	InitializePathfinder(FVector3d* inFlashlightLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
