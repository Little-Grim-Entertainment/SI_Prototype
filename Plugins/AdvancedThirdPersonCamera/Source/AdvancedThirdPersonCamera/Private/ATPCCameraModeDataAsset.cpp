// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraModeDataAsset.h"

#include "ATPCCustomVersion.h"

void UATPCCameraModeDataAsset::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar.UsingCustomVersion(FATPCCustomVersion::GUID);

	if (Ar.IsLoading())
	{
		const int32 customVer = Ar.CustomVer(FATPCCustomVersion::GUID);

		if (customVer < FATPCCustomVersion::NewInterpolationTypes)
		{
			auto replaceInterpolationSpeed = [](FATPCInterploationSpeed& NewInterpSpeed, const float OldInterSpeed, TOptional<EATPCInterpolationType> OldInterpType = {}, TOptional<float> InterpSpeedToInterpolation = {}) {
				NewInterpSpeed.InterpSpeed = OldInterSpeed;

				if (OldInterpType.IsSet())
				{
					NewInterpSpeed.InterpType = OldInterpType.GetValue();
				}

				if (InterpSpeedToInterpolation.IsSet())
				{
					NewInterpSpeed.InterpSpeedToInterpolation = InterpSpeedToInterpolation.GetValue();
				}
			};

			//--------REPLACE LOCATION SETTINGS--------//
			auto& locationSettings = CameraModeSettings.LocationSettings;

			replaceInterpolationSpeed(locationSettings.ZoomInterpolation, locationSettings.ZoomSpeed_OLD, locationSettings.ZoomInterpolationType_OLD);

			replaceInterpolationSpeed(locationSettings.SocketOffsetInterpolation, locationSettings.SocketOffsetInterpSpeed_OLD);

			replaceInterpolationSpeed(locationSettings.TargetOffsetInterpolation, locationSettings.TargetOffsetInterpSpeed_OLD);

			//--------REPLACE ROTATION SETTINGS--------//
			auto& rotationSettings = CameraModeSettings.RotationSettings;

			replaceInterpolationSpeed(rotationSettings.ViewInterpolation, rotationSettings.ViewInterpolationSpeed_OLD);

			replaceInterpolationSpeed(rotationSettings.RotationOffsetSettings.RotationInterpolation, rotationSettings.RotationOffsetSettings.ChangeRotationSpeed_OLD, rotationSettings.RotationOffsetSettings.InterpolationType_OLD);

			replaceInterpolationSpeed(rotationSettings.ViewRotationToActorRotationSettings.RotationInterpolation, rotationSettings.ViewRotationToActorRotationSettings.ChangeRotationSpeed_OLD, EATPCInterpolationType::SmoothInterpolation, rotationSettings.ViewRotationToActorRotationSettings.ChangeRotationSpeedInterpSpeed_OLD);

			//--------REPLACE FOV SETTINGS--------//
			replaceInterpolationSpeed(CameraModeSettings.FOVSettings.FOVInterpolation, CameraModeSettings.FOVSettings.InterpolationSpeed_OLD);

			//--------REPLACE FOLLOW TO TERRAIN SETTINGS--------//
			auto& followTerraionSettings = CameraModeSettings.FollowTerrainSettings;

			replaceInterpolationSpeed(followTerraionSettings.SocketOffsetInterpolation, followTerraionSettings.SocketOffsetInterpSpeed_OLD);
			replaceInterpolationSpeed(followTerraionSettings.PitchRotationInterpolation, followTerraionSettings.AngleRotationInterpSpeed_OLD);

			//--------REPLACE LOCK ON TARGET SETTINGS--------//
			auto& lockOnTargetSettings = CameraModeSettings.LockOnTargetSettings;

			replaceInterpolationSpeed(lockOnTargetSettings.CameraRotationInterpolation, lockOnTargetSettings.CameraRotationSpeed_OLD, EATPCInterpolationType::SmoothInterpolation, lockOnTargetSettings.AdditionalSmoothRotationSpeed_OLD);
		}
	}
}
