// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Evidence/SI_Evidence.h"


// Sets default values
ASI_Evidence::ASI_Evidence()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASI_Evidence::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_Evidence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

