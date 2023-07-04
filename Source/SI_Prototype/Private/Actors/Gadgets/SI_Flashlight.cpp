// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_Flashlight.h"
#include "Components/SpotLightComponent.h"
#include "Actors/Gadgets/SI_FlashlightSegment.h"
#include "Interfaces/SI_PowerInterface.h"


ASI_Flashlight::ASI_Flashlight()
{	
	FirstSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstSegment"));
	FirstSegment->SetupAttachment(RootComponent);
	FirstSegment->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SecondSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondSegment"));
	SecondSegment->SetupAttachment(FirstSegment);
	SecondSegment->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThirdSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdSegment"));
	ThirdSegment->SetupAttachment(FirstSegment);
	ThirdSegment->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FourthSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FourthSegment"));
	FourthSegment->SetupAttachment(FirstSegment);
	FourthSegment->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	
	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight Spotlight"));
	Spotlight->SetupAttachment(FirstSegment);
	MaxSpotlightIntensity = 10000.0f;
	Spotlight->SetIntensity(MaxSpotlightIntensity);

	SpotlightIntensityIncrement = MaxSpotlightIntensity/(MaxPlaceableSegments+1);

	// Initializing defaults
	SegmentsPlaced = 0;
	MaxPlaceableSegments = 3;
	MaxPower = 100.0f;	
}

void ASI_Flashlight::BeginPlay()
{
	Super::BeginPlay();
	Spotlight->SetHiddenInGame(true);	
	bFlashlightOn = false;
}


void ASI_Flashlight::UsePrimary()
{
	if (bFlashlightOn)
	{
		Spotlight->SetHiddenInGame(true);
		// todo: set emissive property of flashlight glass
		// todo: Timer for power trace
		GetWorld()->GetTimerManager().SetTimer(PowerTraceTimerHandle, this, &ASI_Flashlight::ExecuteTrace, 1.0f, true);
	}
	else
	{
		Spotlight->SetHiddenInGame(false);
		// todo: set emissive property of flashlight glass
		// todo: End timer for power trace
		// end trace loop?
		// clear timer
	}
	bFlashlightOn = !bFlashlightOn;
}

void ASI_Flashlight::UseSecondary()
{	
	if (SegmentsPlaced == MaxPlaceableSegments)
	 {
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cannot place any more Flashlight Segments"));
		}
		// Trigger audio/ visual notification to player that no more segments can be placed
	 }
	else
	{	
		PlaceSegment();								
	}	
}

void ASI_Flashlight::PlaceSegment()
{
	// PlayAnimation;	
	// FlashlightMeshHandler(-)
	SpawnSegment();	
	SegmentsPlaced++;
	LightIntensityHandler();
	// PowerIntensityHandler(); (can merge w/LIH)	
	// ChangeGadgetIconHandler();
}

void ASI_Flashlight::BindPickUpSegment()
{
	FlashlightSegment->SegmentPickUpDelegate.BindUObject(this, &ThisClass::PickUpSegment);		
}

void ASI_Flashlight::PickUpSegment(int InSegmentNumber)
{	
	// todo: if 
	// Todo: Segment number not consistent with order/ unique segment
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Flashlight: Picked up segment %d"), InSegmentNumber));
	}
	// PlayAnimation;
	// DestroyOverlappingSegment;
	// FlashlightMeshHandler(+)
	SegmentsPlaced--;
	LightIntensityHandler();
	// PowerIntensityHandler(); (can merge w/LIH)
	// GadgetIconHandler();
}

void ASI_Flashlight::SpawnSegment()
{
	if (FlashlightSegmentClass)
	{				
			FTransform const SegmentSpawnTransform = GetActorTransform();
			FlashlightSegment = GetWorld()->SpawnActor<ASI_FlashlightSegment>(FlashlightSegmentClass, SegmentSpawnTransform);
			// todo: set segment unique identifier
			FlashlightSegment->InitializeSegment(MaxPower/(MaxPlaceableSegments + 1));
			BindPickUpSegment();
	}
	// todo: if (segments placed == max segments placed) spawn segment in front of nick and bind to hand
	
}

void ASI_Flashlight::ExecuteTrace()
{
	FVector Start = Spotlight->GetComponentLocation();
	FVector End = Start + Spotlight->GetForwardVector() * 100.0f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// todo: Dealing with partial obstruction in flashlight beam
	if (GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility, Params))
	{		
		for (FHitResult& HitResult : HitResults)
		{
			AActor* Actor = HitResult.GetActor();		
			if(!IsValid(Actor)) {continue;}

			const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(Actor);
			if(PowerInterfaceActor == nullptr || PowerInterfaceActor->Execute_HasMaxPower(Actor)) {continue;}
						
			PowerInterfaceActor->Execute_OnPowerReceived(Actor, this, CurrentPower);	
			
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Flashlight: Hit Actor: %s"),*Actor->GetName()));
			}			
		}
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);
	}
	// IF POWER ACTOR IS NULL (THEN RETURN)
	// IF POWER ACTOR IS HIT ACTOR (THEN RETURN)
	//
}

void ASI_Flashlight::LightIntensityHandler()
{
	SpotlightIntensityIncrement = MaxSpotlightIntensity/(MaxPlaceableSegments+1);
	CurrentSpotlightIntensity = MaxSpotlightIntensity - (SpotlightIntensityIncrement*SegmentsPlaced);
	Spotlight->SetIntensity(CurrentSpotlightIntensity);
	//Spotlight->Oncomp
	
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Flashlight: Inside LightIntensityHandler %f"),Spotlight->Intensity));
	}	
}



