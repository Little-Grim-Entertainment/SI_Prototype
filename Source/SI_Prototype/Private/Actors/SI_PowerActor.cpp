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
	PowerCollisionMesh->SetCollisionResponseToChannel (ECC_Visibility, ECR_Overlap);	
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

bool ASI_PowerActor::IsFlashlightSet_Implementation()
{
	return bIsFlashlightSet;
}

void ASI_PowerActor::SetFlashlight_Implementation(AActor* Caller)
{
	if (ASI_Flashlight* FlashlightActor = Cast<ASI_Flashlight>(Caller))
	{
		Flashlight = FlashlightActor;
		bIsFlashlightSet = true;
	}	
}

void ASI_PowerActor::OnFlashlightPowerReceived_Implementation(AActor* Caller, float InPower)
{
	
	ExecuteTrace();
	//GetWorld()->GetTimerManager().SetTimer(PowerTraceTimerHandle, this, &ASI_PowerActor::ExecuteTrace, 2.0f, true);	
}

void ASI_PowerActor::OnFlashlightPowerLost_Implementation(AActor* Caller, float InPower)
{
	// LT05. End Line Trace timer
	//GetWorldTimerManager().ClearTimer(PowerTraceTimerHandle);
	if (bIsFlashlightPowered)
	{
		CurrentPower = CurrentPower - FlashlightPowerContribution;
		bIsFlashlightPowered = false;	
	}
	UpdatePowerDetails();
}

void ASI_PowerActor::ExecuteTrace()
{
	// LT02. Find Flashlight and Power Actor positions
	FVector Start = this->GetActorLocation();
	FVector End = Flashlight->FirstSegment->GetComponentLocation();
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// LT03. Line Trace  between Flashlight and Power Actor
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
	DrawDebugLine(GetWorld(), Start, End, HitResult.bBlockingHit ? FColor::Red : FColor::Green, false, 1.0f, 0, 5.0f);

	// LT04. Check to see if actor hit is Flashlight
	AActor* HitActor = HitResult.GetActor();
	if (HitActor == Flashlight)
	{
		// If Power Actor is not currently Flashlight powered
		if (!bIsFlashlightPowered)
		{
			FlashlightPowerContribution = Flashlight->CurrentPower;
			CurrentPower = CurrentPower + FlashlightPowerContribution;
			bIsFlashlightPowered = true;
		}
		// Else (if) Power Actor is currently Flashlight powered
		else
		{
			// Todo [1]: instead of checking for change every trace, use delegate to update flashlight contribution on segment drop/ pickup
			// Todo: Let the delegate broadcast update the FlashlightPowerContribution and then recalculate current power and UPDATE POWER DETAILS
			// Check to see if the Power of the Flashlight is different from what we're adding to Current Power
			if (FlashlightPowerContribution != Flashlight->CurrentPower)
			{
				CurrentPower = CurrentPower - (FlashlightPowerContribution - Flashlight->CurrentPower);
				FlashlightPowerContribution = Flashlight->CurrentPower;
			}
		}		
	}
	// Else (if) flashlight is no longer in direct line, remove Flashlight contribution from current power
	else
	{
		CurrentPower = CurrentPower - FlashlightPowerContribution;
		bIsFlashlightPowered = false;	
	}
	UpdatePowerDetails();
}

void ASI_PowerActor::UpdatePowerDetails()
{
	if (CurrentPower >= RequiredPower)
	{
		bIsFullyPowered = true;
		// Trigger 'fully-powered' animation
		// Turn on powered features
		// todo: delete material change when implementation complete
		Mesh->SetMaterial(0, MaterialPoweredOn);
	}
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
	// Update UI power indicator
	PrintDebug();
}

void ASI_PowerActor::PrintDebug()
{
	if(GEngine)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Power Actor: Current Power: %f"), CurrentPower));
	}
	
}

