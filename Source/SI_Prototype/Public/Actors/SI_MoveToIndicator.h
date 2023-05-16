// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SI_MoveToIndicator.generated.h"

class USI_AIPerceptionStimuliSource;

UCLASS()
class SI_PROTOTYPE_API ASI_MoveToIndicator : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASI_MoveToIndicator();

private:

	UPROPERTY(VisibleAnywhere)
	USI_AIPerceptionStimuliSource* StimuliSource;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPerceptionStimuliSource();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
