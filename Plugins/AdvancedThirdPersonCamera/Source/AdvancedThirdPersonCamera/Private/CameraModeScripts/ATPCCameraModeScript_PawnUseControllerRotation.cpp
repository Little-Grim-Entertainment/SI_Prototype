// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#include "CameraModeScripts/ATPCCameraModeScript_PawnUseControllerRotation.h"

#include "ATPCCameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UATPCCameraModeScript_PawnUseControllerRotation::OnEnterCameraMode(UATPCCameraComponent* Camera)
{
	Super::OnEnterCameraMode(Camera);

	if (auto movementComponent = GetMovementComponent(Camera))
	{
		if (bRestoreOldValuesOnExitCameraMode)
		{
			OldOrientRotationToMovement = movementComponent->bOrientRotationToMovement;
			OldUseControllerDesiredRotation = movementComponent->bUseControllerDesiredRotation;
		}

		movementComponent->bOrientRotationToMovement = OrientRotationToMovement;
		movementComponent->bUseControllerDesiredRotation = UseControllerDesiredRotation;
	}
}

void UATPCCameraModeScript_PawnUseControllerRotation::OnExitCameraMode()
{
	Super::OnExitCameraMode();

	if (bRestoreOldValuesOnExitCameraMode)
	{
		if (auto movementComponent = GetMovementComponent(OwningCamera))
		{
			movementComponent->bOrientRotationToMovement = OldOrientRotationToMovement;
			movementComponent->bUseControllerDesiredRotation = OldUseControllerDesiredRotation;
		}
	}
}

UCharacterMovementComponent* UATPCCameraModeScript_PawnUseControllerRotation::GetMovementComponent(UATPCCameraComponent* Camera) const
{
	auto character = Camera != nullptr ? Cast<ACharacter>(Camera->GetOwner()) : nullptr;
	return character != nullptr ? character->GetCharacterMovement() : nullptr;
}
