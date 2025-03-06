// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#include "CameraModeScripts/ATPCCameraModeScript_ChangeMovementSpeed.h"

#include "ATPCCameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UATPCCameraModeScript_ChangeMovementSpeed::OnEnterCameraMode(UATPCCameraComponent* Camera)
{
	Super::OnEnterCameraMode(Camera);

	if (auto movementComponent = GetMovementComponent(Camera))
	{
		if (bRestoreOldMovementSpeedOnExitCameraMode)
		{
			OldMaxMovementSpeed = movementComponent->MaxWalkSpeed;
		}

		movementComponent->MaxWalkSpeed = NewMaxMovementSpeed;
	}
}

void UATPCCameraModeScript_ChangeMovementSpeed::OnExitCameraMode()
{
	Super::OnExitCameraMode();

	if (bRestoreOldMovementSpeedOnExitCameraMode)
	{
		if (auto movementComponent = GetMovementComponent(OwningCamera))
		{
			movementComponent->MaxWalkSpeed = OldMaxMovementSpeed;
		}
	}
}

UCharacterMovementComponent* UATPCCameraModeScript_ChangeMovementSpeed::GetMovementComponent(UATPCCameraComponent* Camera) const
{
	auto character = Camera != nullptr ? Cast<ACharacter>(Camera->GetOwner()) : nullptr;
	return character != nullptr ? character->GetCharacterMovement() : nullptr;
}
