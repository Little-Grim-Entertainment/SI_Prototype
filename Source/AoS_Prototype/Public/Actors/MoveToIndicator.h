// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MoveToIndicator.generated.h"

class UAoS_AIPerceptionStimuliSource;

UCLASS()
class AOS_PROTOTYPE_API AMoveToIndicator : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMoveToIndicator();

private:

	UPROPERTY(VisibleAnywhere)
	UAoS_AIPerceptionStimuliSource* StimuliSource;

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
