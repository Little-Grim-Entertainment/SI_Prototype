// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_MovableActor.h"


// Sets default values
ASI_MovableActor::ASI_MovableActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASI_MovableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASI_MovableActor::OnPossessMovable_Implementation(AActor* Caller)
{
	ISI_MovableInterface::OnPossessMovable_Implementation(Caller);
}

void ASI_MovableActor::OnEndPossessMovable_Implementation(AActor* Caller)
{
	ISI_MovableInterface::OnEndPossessMovable_Implementation(Caller);
}

// Called every frame
void ASI_MovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

