// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AoS_MoveToIndicator.h"

#include "AI/AoS_AIPerceptionStimuliSource.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AAoS_MoveToIndicator::AAoS_MoveToIndicator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StimuliSource = CreateDefaultSubobject<UAoS_AIPerceptionStimuliSource>(TEXT("StimuliSource"));
}

// Called when the game starts or when spawned
void AAoS_MoveToIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAoS_MoveToIndicator::SetPerceptionStimuliSource()
{
	StimuliSource->RegisterSense(UAISense_Sight::StaticClass());
}

// Called every frame
void AAoS_MoveToIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAoS_MoveToIndicator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

