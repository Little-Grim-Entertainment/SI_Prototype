// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_RotationIndicator.h"


// Sets default values
ASI_RotationIndicator::ASI_RotationIndicator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASI_RotationIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_RotationIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

