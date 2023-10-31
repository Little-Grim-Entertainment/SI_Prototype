// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/SI_PowerActor.h"
#include "Actors/Gadgets/SI_Flashlight.h"
#include "Components/ActorComponent.h"
#include "Actors/Gadgets/SI_FlashlightSegment.h"
#include "Components/BoxComponent.h"

// Sets default values
ASI_PowerActor::ASI_PowerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PowerCollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Power Collision Mesh"));
	PowerCollisionMesh->SetupAttachment(RootComponent);
	PowerCollisionMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	PowerCollisionMesh->SetCollisionResponseToChannel (ECC_GameTraceChannel3, ECR_Overlap);
	PowerCollisionMesh->SetCollisionResponseToChannel (ECC_Visibility, ECR_Ignore);	
	PowerCollisionMesh->SetCollisionObjectType(ECC_GameTraceChannel3);
	PowerCollisionMesh->bMultiBodyOverlap = true;

	// VARIABLE DEFAULTS
	CurrentPower = 0.0f;
	RequiredPower = 50.0f;
	bIsFlashlightSet = false;	
	bIsFlashlightPowered = false;
	bIsFullyPowered = false;	
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
	// Todo: Rename interface calls to be segment power and flashlight power
	// Adjust Segment Contribution
	SegmentPowerContribution += InPower;
	
	UpdatePowerDetails();
}

void ASI_PowerActor::OnPowerLost_Implementation(AActor* Caller, float InPower)
{	
	// Todo: Rename interface calls to be segment power and flashlight power
	// Adjust Segment Contribution
	SegmentPowerContribution -= InPower;
	
	UpdatePowerDetails();	
}

void ASI_PowerActor::OnFlashlightPowerReceived_Implementation(AActor* Caller, float InPower)
{	
	// Adjust Flashlight contribution if changed
	if (FlashlightPowerContribution != InPower)
	{
		FlashlightPowerContribution = InPower;
		bIsFlashlightPowered = true;		
	}
	UpdatePowerDetails();
}

// Todo: Adjust to REMOVE InPower in interface call (not needed atm)
void ASI_PowerActor::OnFlashlightPowerLost_Implementation(AActor* Caller, float InPower)
{
	// Set Flashlight contribution to zero
	FlashlightPowerContribution = 0;
	bIsFlashlightPowered = false;	
	UpdatePowerDetails();	
}

void ASI_PowerActor::UpdatePowerDetails()
{
	// Recalculate current power
	CurrentPower = SegmentPowerContribution + FlashlightPowerContribution;

	// Todo: Update UI power indicator
	
	
	// If power requirements are met
	if (CurrentPower >= RequiredPower)
	{
		bIsFullyPowered = true;
		// Trigger 'fully-powered' animation
		// Turn on powered features
		// todo: delete material change when implementation complete//todo: ?????????????????????????????????????????????
		Mesh->SetMaterial(0, MaterialPoweredOn);
	}
	// Else power requirements are not met
	else
	{
		// Todo: Not sure if we need to set it to zero.. could it cause calculation problems later?
		if (CurrentPower < 0)
		{
			CurrentPower = 0;
		}
		bIsFullyPowered = false;
		// Stop 'fully-powered' animation
		// Turn off powered features
		// todo: delete material change when implementation complete
		Mesh->SetMaterial(0, MaterialPoweredOff);
	}
	
	PrintDebug();
}

void ASI_PowerActor::PrintDebug()
{
	if(GEngine)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Power Actor: Current Power: %f"), CurrentPower));
	}
	
}





