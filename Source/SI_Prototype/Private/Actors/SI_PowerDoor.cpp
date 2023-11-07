// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Actors\SI_PowerDoor.h"
#include "Actors/SI_PowerActor.h"


//TODO: RENAME ALL OF THIS STUFF TO ASI_SOMETHING



// Sets default values
APowerDoor::APowerDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APowerDoor::BeginPlay()
{
	Super::BeginPlay();

	for (ASI_PowerActor* AttachedPowerActor : AttachedPowerActors)
	{
		AttachedPowerActor->OnFullyPowered.AddDynamic(this, &ThisClass::CheckPowerRequirements);
	}
}

void APowerDoor::CheckPowerRequirements(bool bIsFullyPowered)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFullyPowered Delegate Called"))
	// If Array of attached power actors has more than 0 elements
	if (AttachedPowerActors.Num() > 0)
	{
		int ArraySize = AttachedPowerActors.Num();
		int FullyPoweredActors = 0;
		
		for (ASI_PowerActor* PowerActor : AttachedPowerActors)
		{			
			if (PowerActor->bIsFullyPowered)
			{
				FullyPoweredActors++;
			}			
		}
		if (FullyPoweredActors == ArraySize)
		{
			OpenDoorBPEvent();
			UE_LOG(LogTemp, Warning, TEXT("Door Opened"))
		}
	}
}

// Called every frame
void APowerDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}
