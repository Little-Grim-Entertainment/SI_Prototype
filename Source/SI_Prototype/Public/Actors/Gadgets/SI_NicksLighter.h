// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_BaseGadget.h"
#include "SI_NicksLighter.generated.h"

UCLASS()
class SI_PROTOTYPE_API ASI_NicksLighter : public ASI_BaseGadget
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASI_NicksLighter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
