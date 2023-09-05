// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_NicksLighter.h"


// Sets default values
ASI_NicksLighter::ASI_NicksLighter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASI_NicksLighter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_NicksLighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

