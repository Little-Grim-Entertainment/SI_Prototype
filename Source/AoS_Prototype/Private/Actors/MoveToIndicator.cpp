// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MoveToIndicator.h"

#include "AI/AoS_AIPerceptionStimuliSource.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AMoveToIndicator::AMoveToIndicator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StimuliSource = CreateDefaultSubobject<UAoS_AIPerceptionStimuliSource>(TEXT("StimuliSource"));
}

// Called when the game starts or when spawned
void AMoveToIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMoveToIndicator::SetPerceptionStimuliSource()
{
	StimuliSource->RegisterSense(UAISense_Sight::StaticClass());
}

// Called every frame
void AMoveToIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMoveToIndicator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

