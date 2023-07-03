// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_MoveToIndicator.h"

#include "AI/SI_AIPerceptionStimuliSource.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ASI_MoveToIndicator::ASI_MoveToIndicator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StimuliSource = CreateDefaultSubobject<USI_AIPerceptionStimuliSource>(TEXT("StimuliSource"));
}

// Called when the game starts or when spawned
void ASI_MoveToIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASI_MoveToIndicator::SetPerceptionStimuliSource()
{
	StimuliSource->RegisterSense(UAISense_Sight::StaticClass());
}

// Called every frame
void ASI_MoveToIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASI_MoveToIndicator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

