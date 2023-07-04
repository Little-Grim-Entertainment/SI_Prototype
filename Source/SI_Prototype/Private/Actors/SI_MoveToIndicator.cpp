// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_MoveToIndicator.h"

#include "AI/SI_AIPerceptionStimuliSource.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ASI_MoveToIndicator::ASI_MoveToIndicator()
{
	StimuliSource = CreateDefaultSubobject<USI_AIPerceptionStimuliSource>(TEXT("StimuliSource"));
	
	MoveToMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Active Mesh");
	MoveToMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASI_MoveToIndicator::BeginPlay()
{
	Super::BeginPlay();
}

void ASI_MoveToIndicator::SetPerceptionStimuliSource()
{
	StimuliSource->RegisterSense(UAISense_Sight::StaticClass());
}

void ASI_MoveToIndicator::UpdateActiveMesh(UStaticMesh* InMesh)
{
	if(!IsValid(InMesh) || MoveToMeshComponent->GetStaticMesh() == InMesh) return;
	
	MoveToMeshComponent->SetStaticMesh(InMesh);
}

void ASI_MoveToIndicator::SetActiveMeshToDefault()
{
	if(!IsValid(DefaultMesh) || !IsValid(MoveToMeshComponent)) return;
	
	MoveToMeshComponent->SetStaticMesh(DefaultMesh);
}