// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraVolume.h"

#include "ATPCCameraComponent.h"
#include "Components/BrushComponent.h"

AATPCCameraVolume::AATPCCameraVolume(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	GetBrushComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetBrushComponent()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetBrushComponent()->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AATPCCameraVolume::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AATPCCameraVolume::OnVolumeBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AATPCCameraVolume::OnVolumeEndOverlap);
}

void AATPCCameraVolume::OnVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && (!bCheckFilterActorClassWithCamera || FilterActorClassesWithCamera.Find(OtherActor->GetClass())))
	{
		if (UATPCCameraComponent* cameraComponent = GetCameraFromActor(OtherActor))
		{
			cameraComponent->OnBeginOverlapCameraVolume(this);
		}
	}
}

void AATPCCameraVolume::OnVolumeEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && (!bCheckFilterActorClassWithCamera || FilterActorClassesWithCamera.Find(OtherActor->GetClass())))
	{
		if (UATPCCameraComponent* cameraComponent = GetCameraFromActor(OtherActor))
		{
			cameraComponent->OnEndOverlapCameraVolume(this);
		}
	}
}

UATPCCameraComponent* AATPCCameraVolume::GetCameraFromActor(AActor* Actor)
{
	return Actor->FindComponentByClass<UATPCCameraComponent>();
}