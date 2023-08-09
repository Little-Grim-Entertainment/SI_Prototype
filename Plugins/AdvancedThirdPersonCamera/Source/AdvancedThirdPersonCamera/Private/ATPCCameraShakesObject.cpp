// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraShakesObject.h"

#include "ATPCCameraComponent.h"
#include "ATPCCameraModeDataAsset.h"
#include "LegacyCameraShake.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UATPCCameraShakesObject::OnEnterCameraMode(bool bWithInterpolation)
{
	Super::OnEnterCameraMode(bWithInterpolation);

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;
	if (cameraMode.bEnableCameraShakesSettings)
	{
		auto& cameraShakesSettings = cameraMode.CameraShakesSettings;
		if (APlayerCameraManager* cameraManager = GetPlayerCameraManager())
		{
			if (cameraShakesSettings.bNeedStopAllCameraShakeOnEnterToCameraMode)
			{
				cameraManager->StopAllCameraShakes(!bWithInterpolation);
			}

			bPlayRegularCameraMode = cameraShakesSettings.EnterToModeCameraShake == nullptr;
			PlayCameraShake(cameraShakesSettings.EnterToModeCameraShake != nullptr ? cameraShakesSettings.EnterToModeCameraShake : cameraShakesSettings.RegularCameraShake);
		}
	}
}

void UATPCCameraShakesObject::OnExitCameraMode()
{
	Super::OnExitCameraMode();

	GetWorld()->GetTimerManager().ClearTimer(CameraShakeEndTimerHandle);

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;
	if (cameraMode.bEnableCameraShakesSettings)
	{
		if (APlayerCameraManager* cameraManager = GetPlayerCameraManager())
		{
			auto cameraShake = bPlayRegularCameraMode ? cameraMode.CameraShakesSettings.RegularCameraShake : cameraMode.CameraShakesSettings.EnterToModeCameraShake;
			cameraManager->StopAllInstancesOfCameraShake(cameraShake, false);
		}
	}
}

TPair<bool, float> UATPCCameraShakesObject::GetCameraShakeDuration(TSubclassOf<UCameraShakeBase> CameraShake) const
{
	FCameraShakeDuration cameraShakeDuration;
	UCameraShakeBase::GetCameraShakeDuration(CameraShake, cameraShakeDuration);

	using ShakeDuration = TPairInitializer<bool, float>;

	if (cameraShakeDuration.IsCustom())
	{
		ShakeDuration shakeDuration(false, 0.f);
		if (auto matineeCameraShake = Cast<ULegacyCameraShake>(CameraShake.GetDefaultObject()))
		{
			shakeDuration.Key = matineeCameraShake->OscillationDuration < 0.f;
			shakeDuration.Value = matineeCameraShake->OscillationDuration;
		}
		return shakeDuration;
	}
	else if (cameraShakeDuration.IsFixed())
	{
		return ShakeDuration(false, cameraShakeDuration.Get());
	}

	return ShakeDuration(true, 0.f);
}

void UATPCCameraShakesObject::PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake)
{
	APlayerCameraManager* cameraManager = GetPlayerCameraManager();
	if (cameraManager != nullptr && CameraShake != nullptr)
	{
		cameraManager->StartCameraShake(CameraShake);

		auto cameraShakeDuration = GetCameraShakeDuration(CameraShake);

		if (!cameraShakeDuration.Key)
		{
			GetWorld()->GetTimerManager().SetTimer(CameraShakeEndTimerHandle, this, &UATPCCameraShakesObject::OnCameraShakeEnd, cameraShakeDuration.Value + 0.1f, false);
		}
	}
}

void UATPCCameraShakesObject::OnCameraShakeEnd()
{
	PlayCameraShake(GetCamera().GetCurrentCameraMode()->CameraModeSettings.CameraShakesSettings.RegularCameraShake);
}
