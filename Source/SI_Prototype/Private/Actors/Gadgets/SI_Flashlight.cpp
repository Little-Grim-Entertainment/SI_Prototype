// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Gadgets/SI_Flashlight.h"
#include "AITypes.h"
#include "Components/SpotLightComponent.h"
#include "Actors/Gadgets/SI_FlashlightSegment.h"
#include "Interfaces/SI_PowerInterface.h"
#include "DrawDebugHelpers.h"
#include "Actors/SI_PowerActor.h"
#include "Actors/Gadgets/SI_SegmentPathfinder.h"

ASI_Flashlight::ASI_Flashlight()
{	
	// COMPONENT CONSTRUCTION
	FirstSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First Segment"));
	FirstSegment->SetupAttachment(RootComponent);
	FirstSegment->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SecondSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second Segment"));
	SecondSegment->SetupAttachment(FirstSegment);
	SecondSegment->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThirdSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third Segment"));
	ThirdSegment->SetupAttachment(FirstSegment);
	ThirdSegment->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FourthSegment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fourth Segment"));
	FourthSegment->SetupAttachment(FirstSegment);
	FourthSegment->SetCollisionEnabled(ECollisionEnabled::NoCollision);		
	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight Spotlight"));
	Spotlight->SetupAttachment(FirstSegment);
	ConeRootSC = CreateDefaultSubobject<USceneComponent>(TEXT("Cone Root"));
	ConeRootSC->SetupAttachment(FirstSegment);	
	CollisionCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Cone"));
	CollisionCone->SetupAttachment(ConeRootSC);
	CollisionCone->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionCone->SetCollisionResponseToChannel (ECC_GameTraceChannel3, ECR_Overlap);
	
	// VARIABLE DEFAULTS
	MaxPower = 100.0f;
	CurrentPower = MaxPower;
	bFlashlightOn = false;
	SegmentsPlaced = 0;
	MaxPlaceableSegments = 3;
	MaxSpotlightIntensity = 20000.0f;
	MaxSpotlightConeAngle = 40.0f;	// Collision cone dimensions are hard coded for 40.0f MaxSpotLightConeAngle
	MaxSpotlightAttenuationRadius = 2000;

	// APPLY DEFAULTS	
	Spotlight->SetIntensity(MaxSpotlightIntensity);		
	Spotlight->SetInnerConeAngle(MaxSpotlightConeAngle);
	Spotlight->SetOuterConeAngle(MaxSpotlightConeAngle);	
	Spotlight->SetAttenuationRadius(MaxSpotlightAttenuationRadius);
	ConeRootScale = FVector(25.75f,25.75f,15.3f);	// Default size of spotlight cone
	SegmentPathfindingFrequency = 4.0f;
}

void ASI_Flashlight::BeginPlay()
{
	Super::BeginPlay();
	Spotlight->SetHiddenInGame(true);
	CollisionCone->SetHiddenInGame(true);
	CollisionCone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Bind overlap function to cone mesh
	CollisionCone->OnComponentBeginOverlap.AddDynamic(this, &ASI_Flashlight::OnConeBeginOverlap);
	CollisionCone->OnComponentEndOverlap.AddDynamic(this, &ASI_Flashlight::OnConeEndOverlap);
}

void ASI_Flashlight::OnConeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If other actor doesn't implement PowerInterface then return
	if (!OtherActor->Implements<USI_PowerInterface>()) {return;}
	
	// LT01. [LT = Line Trace process flow]	
	PowerActorsHit.Add(OtherActor);					// Add Overlapping Power Actors to array
	ExecuteTrace();									// Execute trace for first power actor trace
	
	// Start timer if timer has not been set
	if (!GetWorldTimerManager().IsTimerActive(FlashlightTraceTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(FlashlightTraceTimerHandle, this, &ASI_Flashlight::ExecuteTrace, 0.5f, true);
	}

	// TODO: See steps below
	// > Line trace to object
	// ON END OVERLAP - Find matching object in array and end timer
}

void ASI_Flashlight::OnConeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{ 
	if (!OtherActor->Implements<USI_PowerInterface>()) {return;}
	
	if (const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(OtherActor))
	{
		PowerActorsHit.Remove(OtherActor);
		PowerInterfaceActor->Execute_OnFlashlightPowerLost(OtherActor, this, CurrentPower);
	}
}

void ASI_Flashlight::ExecuteTrace()
{
	// LT02. Fire Line Trace to each Power Actor in array	
	// For each power actor in the array
	for (AActor* PowerActor : PowerActorsHit)
	{
		if (PowerActor)
		{			
			// Prepare the multi-line trace 
			TArray<FHitResult> HitResults;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);
			QueryParams.AddIgnoredActor(FlashlightSegment);
			FVector Start = this->GetActorLocation();
			FVector End = PowerActor->GetActorLocation();
			
			// Fire the multi-line trace
			bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility, QueryParams);
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.5f, 0, 4.0f);

			// If the trace hit 
			if (bHit)
			{
				// If power actor is first actor hit then pass power
				if (HitResults[0].GetActor() == PowerActor)
				{
					// Execute interface call to pass power
					const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(PowerActor);					
					PowerInterfaceActor->Execute_OnFlashlightPowerReceived(PowerActor, this, CurrentPower);						
				}
				// Else remove power contribution of flashlight
				else
				{
					// Execute interface call to pass power
					const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(PowerActor);
					PowerInterfaceActor->Execute_OnFlashlightPowerLost(PowerActor, this, CurrentPower);
				}
			}
		}
	}
}

void ASI_Flashlight::ActivatePrimaryAction_Implementation()
{
	// todo: check segments placed to see if spotlight turns on/off or final segment turns on/off
	if(!bFlashlightOn)
	{
		Spotlight->SetHiddenInGame(false);
		CollisionCone->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		bFlashlightOn = true;
	}
	else
	{
		CancelPrimaryAction();
		bFlashlightOn = false;
	}
		// todo: set emissive property of flashlight glass
}

void ASI_Flashlight::CancelPrimaryAction_Implementation()
{
	Spotlight->SetHiddenInGame(true);
	CollisionCone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// todo: set emissive property of flashlight glass	
}

void ASI_Flashlight::ActivateSecondaryAction_Implementation()
{
	// Place a segment if max placeable segments have not been reached
	if (SegmentsPlaced == MaxPlaceableSegments)
	{
		LG_PRINT(4.0f, Yellow, "Cannot place any more Flashlight Segments");
		// Trigger audio / visual notification to player that no more segments can be placed
		// todo: Fire beam between all segments
	}
	else
	{	
		PlaceSegment();								
	}
	
	// Start segment pathfinder timer if timer has not been set
	if (!GetWorldTimerManager().IsTimerActive(SegmentPathfinderTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(SegmentPathfinderTimerHandle, this, &ASI_Flashlight::SpawnSegmentPathfinder, SegmentPathfindingFrequency, true);
	}	
}

void ASI_Flashlight::PlaceSegment()
{
	// PlayAnimation;	
	// FlashlightMeshHandler(-)
	SpawnSegment();		
	SpotlightHandler();
	PowerCalculationHandler();	
	// GadgetIconHandler();
}

void ASI_Flashlight::BindPickUpSegment(ASI_FlashlightSegment* inFlashlightSegment)
{
	FlashlightSegment->SegmentPickUpDelegate.BindUObject(this, &ThisClass::PickUpSegment);		
}

void ASI_Flashlight::PickUpSegment(int InSegmentNumber)
{	
	// Todo: Segment number not consistent with order/ unique segment
	// PlayAnimation;
	// DestroyOverlappingSegment;
	// FlashlightMeshHandler(+)
	SegmentsPlaced--;
	SpotlightHandler();
	PowerCalculationHandler();	
	// GadgetIconHandler();
	// todo: if segments placed == maxplaceablesegments then cancel segmentpathfinder timer  
}

void ASI_Flashlight::SpawnSegment()
{
	// todo: if (segments placed == max segments placed) spawn segment in front of nick and bind to hand
	if (FlashlightSegmentClass)
	{				
			// Spawn segment
			FTransform const SegmentSpawnTransform = GetActorTransform();
			FlashlightSegment = GetWorld()->SpawnActor<ASI_FlashlightSegment>(FlashlightSegmentClass, SegmentSpawnTransform);

			// Initialize placed segment
			FlashlightSegment->InitializeSegment(MaxPower/(MaxPlaceableSegments + 1));
			BindPickUpSegment(FlashlightSegment);
		
			// Add Segment to array of placed segments
			PlacedSegmentsArray.Add(FlashlightSegment);
	}
	SegmentsPlaced++;
}

void ASI_Flashlight::SpotlightHandler()
{
	// Adjust Spotlight Details	
	Spotlight->SetInnerConeAngle(MaxSpotlightConeAngle - (MaxSpotlightConeAngle/(MaxPlaceableSegments+1)) * SegmentsPlaced);
	Spotlight->SetOuterConeAngle(MaxSpotlightConeAngle - (MaxSpotlightConeAngle/(MaxPlaceableSegments+1)) * SegmentsPlaced);
	
	// Adjust collision cone size to match flashlight spotlight cone todo: change into switch statement
	if		(SegmentsPlaced == 0) {	ConeRootScale = FVector(25.75f,25.75f,15.3f);}
	else if (SegmentsPlaced == 1) {	ConeRootScale = FVector(20.3f,20.3f,17.5f);	}
	else if (SegmentsPlaced == 2) {	ConeRootScale = FVector(13.9f,13.9f,19.0f);	}
	else						  { ConeRootScale = FVector(6.7f,6.7f,19.0f);	}
	
	// Set relative scale
	ConeRootSC->SetRelativeScale3D(ConeRootScale);
	
	// Print Debug Info
	DebugSpotlightInfo();		
}

void ASI_Flashlight::PowerCalculationHandler()
{
	CurrentPower = (MaxPower - (MaxPower/(MaxPlaceableSegments+1)) * SegmentsPlaced);
}

void ASI_Flashlight::DebugSpotlightInfo()
{
	/*if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Flashlight: Inside LightIntensityHandler %f"),Spotlight->Intensity));
	}*/
}

void ASI_Flashlight::SpawnSegmentPathfinder()
{
	LG_PRINT(2.0f, White, "Segment Pathfinder spawned");
	
	// todo: iterate through tarray of placed segments
	// todo: (Anu) Continue work on spawning pathfinder
	// Iterate through Tarray of placed segments
	for (ASI_FlashlightSegment* CurrentSegment : PlacedSegmentsArray)
	{
		if (CurrentSegment)
		{
			// Initialize SpawnActor variables
			FTransform const SegmentTransform = CurrentSegment->GetActorTransform();
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			// Spawn SegmentPathfinder
			ASI_SegmentPathfinder* CurrentSegmentPathfinder = GetWorld()->SpawnActor<ASI_SegmentPathfinder>(SegmentPathfinderClass, SegmentTransform, SpawnParameters);
			
			// Initialize and run pathfinder
			if (CurrentSegmentPathfinder)
			{
				// TODO : Send flashlight data in function that starts the AI
				CurrentSegmentPathfinder->InitializePathfinder(this->GetActorLocation());
			}			
		}
	}

	
		// For each element in array
		// Initialize pathfinder
		// Create Fvectors for current segment location and current flashlight location
			// If (Segment is within certain distance - don't spawn)
			// Spawn SegmentPathfinder class
	//todo: don't forget that Tarray must be updated on PickUpSegment
		
}



