// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCArrowDebugActor.h"

#include "Components/ArrowComponent.h"

AATPCArrowDebugActor::AATPCArrowDebugActor()
{
	SceneRootcomponent = CreateDefaultSubobject<USceneComponent>("SceneRootcomponent");
	SetRootComponent(SceneRootcomponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(SceneRootcomponent);
	ArrowComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	ArrowComponent->SetRelativeScale3D(FVector(1.f, 2.f, 2.f));
	ArrowComponent->ArrowSize = 1.5f;

#if !UE_BUILD_SHIPPING
	PrimaryActorTick.bCanEverTick = true;
#endif
}

void AATPCArrowDebugActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const float animDistance = 60.f;
	const float animTime = 1.f;

	CurrentArrowAnimTime += DeltaSeconds * CurrentArrowAnimTimeSign;

	if (CurrentArrowAnimTime > animTime)
	{
		CurrentArrowAnimTimeSign = -1.f;
	}
	else if (CurrentArrowAnimTime < 0.f)
	{
		CurrentArrowAnimTimeSign = 1.f;
	}
	CurrentArrowAnimTime = FMath::Clamp(CurrentArrowAnimTime, 0.f, animTime);

	ArrowComponent->SetRelativeLocation(FVector(0.f, 0.f, FMath::Lerp(0.f, animDistance, CurrentArrowAnimTime / animTime)));
}

void AATPCArrowDebugActor::PickActor(AActor* Actor)
{
	if (Actor != nullptr)
	{
		FVector origin, boxExtent;
		Actor->GetActorBounds(true, origin, boxExtent);
		SetActorLocation(origin + FVector(0.f, 0.f, boxExtent.Z + 125.f));
	}

	ArrowComponent->SetHiddenInGame(Actor == nullptr);
}
