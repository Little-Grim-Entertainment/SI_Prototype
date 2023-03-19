// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraFollowTerrainObject.h"

#include "ATPCCameraComponent.h"
#include "ATPCCameraLocationObject.h"
#include "ATPCCameraModeDataAsset.h"
#include "ATPCFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

void UATPCCameraFollowTerrainObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetCamera().GetCurrentCameraMode()->CameraModeSettings.bEnableFollowTerrainSettings)
	{
		DetermineTerrainData();
		UpdateRotationAndLocationOffset(true, DeltaSeconds);
	}
	else if (!TerrainSocketOffset.Current.Equals(FVector::ZeroVector) || !FMath::IsNearlyEqual(TargetTerrainRotationPitchOffset, 0.f))
	{
		UpdateRotationAndLocationOffset(true, DeltaSeconds);
	}

#if !UE_BUILD_SHIPPING
	if (GetCamera().DebugRules.bFollowTerrainEnableDebug)
	{
		PrintDebug();
	}
#endif //!UE_BUILD_SHIPPING
}

void UATPCCameraFollowTerrainObject::Validate(bool bWithInterpolation)
{
	Super::Validate(bWithInterpolation);

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;

	if (!bWithInterpolation && cameraMode.bEnableFollowTerrainSettings)
	{
		DetermineTerrainData();
		UpdateRotationAndLocationOffset(false, 0.f);
	}
}

void UATPCCameraFollowTerrainObject::OnEnterCameraMode(bool bWithInterpolation)
{
	Super::OnEnterCameraMode(bWithInterpolation);

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;

	if (cameraMode.bEnableFollowTerrainSettings)
	{
		TerrainSocketOffset.InterploationSpeed = cameraMode.FollowTerrainSettings.SocketOffsetInterpolation;
	}
	else
	{
		TerrainSocketOffset.Target = FVector::ZeroVector;
		TargetTerrainRotationPitchOffset = 0.f;
	}

	Validate(bWithInterpolation);
}

void UATPCCameraFollowTerrainObject::DetermineTerrainData()
{
	auto& followTerrainSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.FollowTerrainSettings;
	if (followTerrainSettings.SocketOffsetCurve != nullptr || followTerrainSettings.PitchRotationCurve != nullptr)
	{
		FHitResult hitResult;
		TraceToTerrain(hitResult);

		if (hitResult.bBlockingHit)
		{
			// if angle > 90, that chracter go up
			float terrainAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(hitResult.Normal, GetOwningActor()->GetActorForwardVector())));
			terrainAngle -= 90.f;

			if (GetOwningActor()->GetVelocity().SizeSquared() > KINDA_SMALL_NUMBER)
			{
				if (!bPendingNewTerrainAngle)
				{
					bPendingNewTerrainAngle = true;
					TimeChangeTerrainAngle = GetWorld()->TimeSeconds;
				}
				else if (GetWorld()->TimeSeconds - TimeChangeTerrainAngle > followTerrainSettings.ChangePitchRotationDelay)
				{
					bPendingNewTerrainAngle = false;

					if (followTerrainSettings.SocketOffsetCurve != nullptr)
					{
						TerrainSocketOffset.Target = followTerrainSettings.SocketOffsetCurve->GetVectorValue(terrainAngle);
					}
					if (followTerrainSettings.PitchRotationCurve != nullptr)
					{
						TargetTerrainRotationPitchOffset = followTerrainSettings.PitchRotationCurve->GetFloatValue(terrainAngle);
					}
				}

				CurrentTerrainAngle = terrainAngle;
			}
			else
			{
				bPendingNewTerrainAngle = false;
				TerrainSocketOffset.Target = TerrainSocketOffset.Current;
				TargetTerrainRotationPitchOffset = CurrentTerrainRotationPitchOffset;
			}
		}
	}
}

void UATPCCameraFollowTerrainObject::TraceToTerrain(FHitResult& HitResult) const
{
	AActor* owningActor = GetOwningActor();
	if (USceneComponent* rootComponent = owningActor->GetRootComponent())
	{
		float actorHalfHeight = owningActor->GetSimpleCollisionHalfHeight();

		FCollisionQueryParams collisionQueryParams;
		collisionQueryParams.AddIgnoredActor(GetOwningActor());

		FCollisionResponseParams collisionResponseParams(rootComponent->GetCollisionResponseToChannels());

		FVector startTrace = owningActor->GetActorLocation();
		FVector endTrace = owningActor->GetActorLocation() + owningActor->GetActorUpVector() * -1.f * (actorHalfHeight * 2.f);
		GetWorld()->LineTraceSingleByChannel(HitResult, startTrace, endTrace, rootComponent->GetCollisionObjectType(), collisionQueryParams, collisionResponseParams);
	}
}

void UATPCCameraFollowTerrainObject::UpdateRotationAndLocationOffset(bool bWithInterp, float DeltaTime)
{
	TerrainSocketOffset.Interpolate(bWithInterp, DeltaTime);

	CurrentTerrainRotationPitchOffset = bWithInterp ? UATPCFunctionLibrary::InterpFloat(CurrentTerrainRotationPitchOffset, TargetTerrainRotationPitchOffset, DeltaTime, GetCamera().GetCurrentCameraMode()->CameraModeSettings.FollowTerrainSettings.PitchRotationInterpolation) : TargetTerrainRotationPitchOffset;

	if (UATPCCameraLocationObject* locationObj = GetCamera().GetCameraLocationObject())
	{
		locationObj->FollowTerrainSocketOffset = TerrainSocketOffset.Current;
		locationObj->FollowTerrainRotationPitchOffset = CurrentTerrainRotationPitchOffset;
	}
}

void UATPCCameraFollowTerrainObject::PrintDebug()
{
	const FColor color = FColor::Orange;
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Follow Terrain Object End Debug -----"));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("TerrainAngle: %.2f"), CurrentTerrainAngle));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Pitch offset: %.2f"), CurrentTerrainRotationPitchOffset));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Socket offset: %s"), *TerrainSocketOffset.Current.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Follow Terrain Object Start Debug ---"));
}
