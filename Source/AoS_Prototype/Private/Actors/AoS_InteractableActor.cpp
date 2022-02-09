// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AoS_InteractableActor.h"
#include "Components/Scene/AoS_InteractableComponent.h"

// Sets default values
AAoS_InteractableActor::AAoS_InteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	InteractableComponent = CreateDefaultSubobject<UAoS_InteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAoS_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAoS_InteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

