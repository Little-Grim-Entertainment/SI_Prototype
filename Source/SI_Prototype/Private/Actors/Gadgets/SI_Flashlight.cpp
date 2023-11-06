// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Gadgets/SI_Flashlight.h"
#include "AITypes.h"
#include "Components/SpotLightComponent.h"
#include "Actors/Gadgets/SI_FlashlightSegment.h"
#include "Interfaces/SI_PowerInterface.h"

// TODO: CHANGING CONE SIZE WITH SEGMENTS PLACED

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
	MaxSpotlightConeAngle = 40.0f;
	MaxSpotlightAttenuationRadius = 2000;

	// APPLY DEFAULTS	
	Spotlight->SetIntensity(MaxSpotlightIntensity);		
	Spotlight->SetInnerConeAngle(MaxSpotlightConeAngle);
	Spotlight->SetOuterConeAngle(MaxSpotlightConeAngle);	
	Spotlight->SetAttenuationRadius(MaxSpotlightAttenuationRadius);	
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
	if (const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(OtherActor))
	{
		// Add Overlapping Power Actors to array
		PowerActorsHit.Add(PowerInterfaceActor);

		// Execute trace for instant power actor calculation
		ExecuteTrace();
		
		// Start timer if timer has not been set
		if (!GetWorldTimerManager().IsTimerActive(FlashlightTraceTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(FlashlightTraceTimerHandle, this, &ASI_Flashlight::ExecuteTrace, 0.5f, true);
		}
		
		// > Line trace to object
		// ON END OVERLAP - Find matching object in array and end timer
		// then remove struct from array
		
		// AddPowerActorToArray
		PowerActorsHit.Add(PowerInterfaceActor);
		
	}
	
	/*// Ensure that the Power Actor has a reference to this Flashlight before passing power
	if (const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(OtherActor))
	{
		if (!PowerInterfaceActor->Execute_IsFlashlightSet(OtherActor))
		{
			PowerInterfaceActor->Execute_SetFlashlight(OtherActor, this);
		}
		PowerInterfaceActor->Execute_OnFlashlightPowerReceived(OtherActor, this, CurrentPower);	
	}	*/
}

void ASI_Flashlight::OnConeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<USI_PowerInterface>()) {return;}
	
	if (const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(OtherActor))
	{
		PowerInterfaceActor->Execute_OnFlashlightPowerLost(OtherActor, this, CurrentPower);
	}
}

void ASI_Flashlight::ExecuteTrace()
{
	// For each power actor in the array
		// Fire Multiline Trace
			// Fill hit results in array
			// If first element (i = 0) is a power actor then pass power
			
	
	
}

void ASI_Flashlight::ActivatePrimaryAction_Implementation()
{
	// todo: check segments placed to see if spotlight turns on/off or final segment turns on/off

	Spotlight->SetHiddenInGame(false);
	CollisionCone->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// todo: set emissive property of flashlight glass
}

void ASI_Flashlight::CancelPrimaryAction_Implementation()
{
	Super::CancelPrimaryAction();

	Spotlight->SetHiddenInGame(true);
	CollisionCone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// todo: set emissive property of flashlight glass	
}

void ASI_Flashlight::ActivateSecondaryAction_Implementation()
{	
	if (SegmentsPlaced == MaxPlaceableSegments)
	 {
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cannot place any more Flashlight Segments"));
		}
		// Trigger audio/ visual notification to player that no more segments can be placed
		// todo: Fire beam between all segments
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
	SpotlightHandler();
	PowerIntensityHandler();	
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
	SpotlightHandler();
	//  todo 1:PowerIntensityHandler();
	// GadgetIconHandler();
}

void ASI_Flashlight::SpawnSegment()
{
	// todo: if (segments placed == max segments placed) spawn segment in front of nick and bind to hand
	if (FlashlightSegmentClass)
	{				
			FTransform const SegmentSpawnTransform = GetActorTransform();
			FlashlightSegment = GetWorld()->SpawnActor<ASI_FlashlightSegment>(FlashlightSegmentClass, SegmentSpawnTransform);
			FlashlightSegment->InitializeSegment(MaxPower/(MaxPlaceableSegments + 1));
			BindPickUpSegment();
	}
	SegmentsPlaced++;
}

void ASI_Flashlight::SpotlightHandler()
{
	// Adjust Spotlight Details	
	Spotlight->SetInnerConeAngle(MaxSpotlightConeAngle - (MaxSpotlightConeAngle/MaxPlaceableSegments+1) * SegmentsPlaced);
	Spotlight->SetOuterConeAngle(MaxSpotlightConeAngle - (MaxSpotlightConeAngle/MaxPlaceableSegments+1) * SegmentsPlaced);	
		
	// Print Debug Info
	DebugSpotlightInfo();		
}

void ASI_Flashlight::PowerIntensityHandler()
{
	CurrentPower = (MaxPower - (MaxPower/MaxPlaceableSegments+1) * SegmentsPlaced);
}

void ASI_Flashlight::DebugSpotlightInfo()
{
	/*if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Flashlight: Inside LightIntensityHandler %f"),Spotlight->Intensity));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Flashlight: Inside LightIntensityHandler %f"),Spotlight->InnerConeAngle));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Flashlight: Inside LightIntensityHandler %f"),Spotlight->OuterConeAngle));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Flashlight: Inside LightIntensityHandler %f"),Spotlight->AttenuationRadius));
	}*/
}



