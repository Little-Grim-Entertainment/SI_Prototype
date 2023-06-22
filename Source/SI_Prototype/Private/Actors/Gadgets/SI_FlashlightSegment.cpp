// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_FlashlightSegment.h"
#include "Characters/SI_Nick.h"
#include "Components/PointLightComponent.h"


// Sets default values
ASI_FlashlightSegment::ASI_FlashlightSegment()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightDome = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Dome"));
	LightDome->SetupAttachment(RootComponent);
	//LightDome->SetCollisionResponseToAllChannels(ECR_Ignore);	// todo: Change when collision needed
	//LightDome->SetCollisionResponseToChannel (ECC_GameTraceChannel3, ECR_Overlap);
	
	Pointlight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	Pointlight->SetupAttachment(RootComponent);
	PointlightIntensity = 500.0f;
	Pointlight->SetIntensity(PointlightIntensity);
}

void ASI_FlashlightSegment::RemoveSegment()
{	
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Segment: Remove segment called"));
	}
	SegmentPickUpDelegate.Execute(SegmentNumber);
	Destroy();
}


// Called when the game starts or when spawned
void ASI_FlashlightSegment::BeginPlay()
{
	Super::BeginPlay();	
}



void ASI_FlashlightSegment::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);

	RemoveSegment();
}


// Called every frame
void ASI_FlashlightSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

