// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraFOVObject.h"

#include "ATPCCameraComponent.h"
#include "ATPCCameraModeDataAsset.h"
#include "ATPCFunctionLibrary.h"
#include "ATPCTypes.h"
#include "Camera/CameraComponent.h"
#include "CineCameraComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void UATPCCameraFOVObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateFOV(true, DeltaSeconds);
}

void UATPCCameraFOVObject::Validate(bool bWithInterpolation)
{
	Super::Validate(bWithInterpolation);

	UpdateFOV(bWithInterpolation, GetWorld()->GetDeltaSeconds());
}

void UATPCCameraFOVObject::OnEnterCameraMode(bool bWithInterpolation)
{
	Super::OnEnterCameraMode(bWithInterpolation);

	Validate(bWithInterpolation);
}

float UATPCCameraFOVObject::GetCurrentFOV() const
{
	if (auto cameraManager = GetPlayerCameraManager())
	{
		return cameraManager->GetFOVAngle();
	}
	return 0.f;
}

void UATPCCameraFOVObject::UpdateFOV(bool bWithInterpolation, float DeltaTime)
{
	auto& camera = GetCamera();
	auto& cameraMode = camera.GetCurrentCameraMode()->CameraModeSettings;
	if (!cameraMode.bEnableFOVSettings )
	{
		return;
	}

	for(const auto& attachChild : camera.GetAttachChildren())
	{
		const auto renderCamera = Cast<UCameraComponent>(attachChild);
		const auto cineCamera = Cast<UCineCameraComponent>(attachChild);
		if(renderCamera != nullptr && renderCamera->IsActive() && (cineCamera == nullptr || cameraMode.FOVSettings.ChangeFOVWhenCineCamera))
		{
			float fovRotationModifier = 0.f;
			if (cameraMode.FOVSettings.PitchRotationFOVModifier != nullptr)
			{
				fovRotationModifier = cameraMode.FOVSettings.PitchRotationFOVModifier->GetFloatValue(renderCamera->GetComponentRotation().Pitch);
			}

			float fovSpeedModifier = 0.f;
			if (cameraMode.FOVSettings.MovementSpeedFOVModifier != nullptr)
			{
				fovSpeedModifier = cameraMode.FOVSettings.MovementSpeedFOVModifier->GetFloatValue(GetOwningActor()->GetVelocity().Size());
			}

			const float targetFOV = cameraMode.FOVSettings.CameraFOV + fovRotationModifier + fovSpeedModifier;

			const float newFOV = bWithInterpolation ? UATPCFunctionLibrary::InterpFloat(renderCamera->FieldOfView, targetFOV, DeltaTime, cameraMode.FOVSettings.FOVInterpolation) : targetFOV;

			renderCamera->SetFieldOfView(newFOV);
		}
	}
}
