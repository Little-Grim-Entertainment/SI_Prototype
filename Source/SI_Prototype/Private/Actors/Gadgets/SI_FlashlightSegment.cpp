// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_FlashlightSegment.h"
#include "Characters/SI_Nick.h"
#include "Components/PointLightComponent.h"
#include "Interfaces/SI_PowerInterface.h"
#include "Actors/SI_PowerActor.h"


// Sets default values
ASI_FlashlightSegment::ASI_FlashlightSegment()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightDome = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Dome"));
	LightDome->SetupAttachment(RootComponent);
	LightDome->SetCollisionResponseToAllChannels(ECR_Ignore);

	PowerCollisionMesh = CreateDefaultSubobject<USphereComponent>(TEXT("Power Collision Mesh"));
	PowerCollisionMesh->SetupAttachment(RootComponent);
	// Todo: Scale size of power collision mesh to match light dome
	PowerCollisionMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	PowerCollisionMesh->SetCollisionResponseToChannel (ECC_GameTraceChannel3, ECR_Overlap);	
	
	Pointlight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	Pointlight->SetupAttachment(RootComponent);
	PointlightIntensity = 500.0f;
	Pointlight->SetIntensity(PointlightIntensity);
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


void ASI_FlashlightSegment::RemoveSegment()
{		
	SegmentPickUpDelegate.Execute(SegmentNumber);
	// todo: Call endoverlap powerinterface?? (WORKING SO FAR)
	Destroy();
}

void ASI_FlashlightSegment::OnPowerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (!OtherActor->Implements<USI_PowerInterface>()) {return;}
		
	if (const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(OtherActor))
	{
		PowerInterfaceActor->Execute_OnPowerReceived(OtherActor, this, Power);	
	}		
		
}

void ASI_FlashlightSegment::OnPowerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<USI_PowerInterface>()) {return;}
	
	if (const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(OtherActor))
	{
		PowerInterfaceActor->Execute_OnPowerLost(OtherActor, this, Power);
	}			
			
}

// Called every frame
void ASI_FlashlightSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASI_FlashlightSegment::InitializeSegment(float InPower)
{
	Power = InPower;
	
	PowerCollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ASI_FlashlightSegment::OnPowerBeginOverlap);
	PowerCollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ASI_FlashlightSegment::OnPowerEndOverlap);

	TArray<AActor*> OverlappingPowerActors;
	PowerCollisionMesh->GetOverlappingActors(OverlappingPowerActors,ASI_PowerActor::StaticClass());

	for (AActor* Actor : OverlappingPowerActors)
	{
		if (const ISI_PowerInterface* PowerInterfaceActor = Cast<ISI_PowerInterface>(Actor))
		{
			PowerInterfaceActor->Execute_OnPowerReceived(Actor, this, Power);	
		}	
	}
}
