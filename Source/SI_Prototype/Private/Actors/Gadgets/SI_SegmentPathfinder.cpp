// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_SegmentPathfinder.h"

// Sets default values
ASI_SegmentPathfinder::ASI_SegmentPathfinder()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASI_SegmentPathfinder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASI_SegmentPathfinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASI_SegmentPathfinder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

