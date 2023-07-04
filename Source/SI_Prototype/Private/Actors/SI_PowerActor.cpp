// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_PowerActor.h"
#include "Actors/Gadgets/SI_FlashlightSegment.h"


// Sets default values
ASI_PowerActor::ASI_PowerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PowerCollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Power Collision Mesh"));
	PowerCollisionMesh->SetupAttachment(RootComponent);
	PowerCollisionMesh->SetCollisionResponseToAllChannels(ECR_Ignore);	// todo: Change when collision needed
	PowerCollisionMesh->SetCollisionResponseToChannel (ECC_GameTraceChannel3, ECR_Overlap);
	PowerCollisionMesh->SetCollisionResponseToChannel (ECC_Visibility, ECR_Overlap);	
	PowerCollisionMesh->SetCollisionObjectType(ECC_GameTraceChannel3);
	PowerCollisionMesh->bMultiBodyOverlap = true;

	// Todo: Test settings (can edit)
	CurrentPower = 0.0f;
	RequiredPower = 50.0f;
}

// Called when the game starts or when spawned
void ASI_PowerActor::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASI_PowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASI_PowerActor::OnPowerReceived_Implementation(AActor* Caller, float InPower)
{	
	CurrentPower = CurrentPower + InPower;
	
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Power Actor: Received Power. Current Power: %f"), CurrentPower));
	}
	UpdatePowerDetails();
}

void ASI_PowerActor::OnPowerLost_Implementation(AActor* Caller, float InPower)
{
	CurrentPower = CurrentPower - InPower;

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Power Actor: Lost Power. Current Power: %f"), CurrentPower));
	}
	UpdatePowerDetails();
}

bool ASI_PowerActor::HasMaxPower_Implementation()
{
	return bIsFullyPowered;
}


void ASI_PowerActor::UpdatePowerDetails()
{
	if (CurrentPower >= RequiredPower)
	{
		bIsFullyPowered = true;
		// Trigger 'fully-powered' animation
		// Turn on powered features		
	}
	else
	{
		bIsFullyPowered = false;
		// Stop 'fully-powered' animation
		// Turn off powered features
	}

	// Update UI power indicator
}

