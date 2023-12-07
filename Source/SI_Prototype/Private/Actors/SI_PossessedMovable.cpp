// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_PossessedMovable.h"

#include "Camera/CameraComponent.h"
#include "ATPCCameraComponent.h"

ASI_PossessedMovable::ASI_PossessedMovable()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);
	
	ATPCCamera = CreateDefaultSubobject<UATPCCameraComponent>(TEXT("ATPCCamera"));
	ATPCCamera->SetupAttachment(MeshComponent);

	// Create a follow camera
	PossessedFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PossessedFollowCamera"));
	PossessedFollowCamera->SetupAttachment(ATPCCamera);
}

void ASI_PossessedMovable::UpdateActiveMesh(UStaticMesh* InMesh)
{
	if(!IsValid(InMesh) || MeshComponent->GetStaticMesh() == InMesh) return;
	
	MeshComponent->SetStaticMesh(InMesh);
}

void ASI_PossessedMovable::SetActiveMeshToDefault()
{
	if(!IsValid(DefaultMesh) || !IsValid(MeshComponent)) return;
	
	MeshComponent->SetStaticMesh(DefaultMesh);
}

