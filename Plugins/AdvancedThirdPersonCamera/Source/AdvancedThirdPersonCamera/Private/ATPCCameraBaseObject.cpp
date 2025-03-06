// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraBaseObject.h"

#include "ATPCCameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#if WITH_ENGINE

UWorld* UATPCCameraBaseObject::GetWorld() const
{
	return OwningCamera != nullptr ? OwningCamera->GetWorld() : nullptr;
}

#endif //WITH_ENGINE

void UATPCCameraBaseObject::Tick(float DeltaSeconds)
{
	K2_Tick(DeltaSeconds);
}

void UATPCCameraBaseObject::Validate(bool bWithInterpolation)
{
	K2_Validate(bWithInterpolation);
}

void UATPCCameraBaseObject::OnExitCameraMode()
{
	K2_OnExitCameraMode();
}

void UATPCCameraBaseObject::OnEnterCameraMode(bool bWithInterpolation)
{
	K2_OnEnterCameraMode(bWithInterpolation);
}

void UATPCCameraBaseObject::SetCamera(UATPCCameraComponent* Camera)
{
	this->OwningCamera = Camera;
}

UATPCCameraComponent& UATPCCameraBaseObject::GetCamera()
{
	return *OwningCamera;
}

const UATPCCameraComponent& UATPCCameraBaseObject::GetCamera() const
{
	return *OwningCamera;
}

UATPCCameraComponent* UATPCCameraBaseObject::GetOwningCamera() const
{
	return OwningCamera;
}

AActor* UATPCCameraBaseObject::GetOwningActor() const
{
	return OwningCamera != nullptr ? OwningCamera->GetOwner() : nullptr;
}

APawn* UATPCCameraBaseObject::GetOwningPawn() const
{
	return OwningCamera != nullptr ? OwningCamera->GetOwningPawn() : nullptr;
}

APlayerController* UATPCCameraBaseObject::GetPlayerController() const
{
	return OwningCamera != nullptr ? OwningCamera->GetPlayerController() : nullptr;
}

APlayerCameraManager* UATPCCameraBaseObject::GetPlayerCameraManager() const
{
	return OwningCamera != nullptr ? OwningCamera->GetPlayerCameraManager() : nullptr;
}
