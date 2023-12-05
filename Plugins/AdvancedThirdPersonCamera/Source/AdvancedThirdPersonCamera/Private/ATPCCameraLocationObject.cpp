// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraLocationObject.h"

#include "ATPCCameraComponent.h"
#include "ATPCCameraModeDataAsset.h"
#include "ATPCFunctionLibrary.h"
#include "AdvancedThirdPersonCamera.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "VisualLogger/VisualLogger.h"

UATPCCameraLocationObject::UATPCCameraLocationObject()
{
}

void UATPCCameraLocationObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LastTickTargetRotationDelta = (GetTargetRotation() - LastTargetRotation).GetNormalized();

	auto& camera = GetCamera();
	const auto& cameraMode = camera.GetCurrentCameraMode()->CameraModeSettings;

	if (bAttachCameraWithInterp)
	{
		camera.SetRelativeLocation(FMath::VInterpConstantTo(camera.GetRelativeLocation(), AttachCameraRelativeLocation, DeltaSeconds, AttachCameraInterpSpeed));
		if (camera.GetRelativeLocation().Equals(AttachCameraRelativeLocation))
		{
			bAttachCameraWithInterp = false;
		}
	}

	if (cameraMode.bEnableLocationSettings)
	{
		UpdateTargetOffsetTarget();
		TargetOffset.Interpolate(true, DeltaSeconds);
		UpdateSocketOffsetTarget();
		OldSocketOffset = SocketOffset;
		SocketOffset.Interpolate(true, DeltaSeconds);
	}

	if (OverrideCameraRotation.IsSet())
	{
		SetViewRotation(OverrideCameraRotation.GetValue());
	}
	else if (cameraMode.bEnableRotationSettings)
	{
		if (cameraMode.RotationSettings.bEnableRoofCollisionCheckSettings)
		{
			ProcessRoofCollisionCheck();
		}

		UpdateOffsetCameraRotationTime(DeltaSeconds);

		UpdateViewRotationToActorRotationTime(DeltaSeconds);

		ValidateCameraView(true, DeltaSeconds);
	}

	LastTargetRotation = GetTargetRotation();

	UpdateDesiredArmLocation(cameraMode.LocationSettings.bDoCollisionTest, cameraMode.LocationSettings.bEnableCameraLocationLag, cameraMode.LocationSettings.bEnableCameraRotationLag, DeltaSeconds);

#if !UE_BUILD_SHIPPING
	if (GetCamera().DebugRules.bEnableLocationObjectDebug)
	{
		ShowDebug();
	}
#endif
}

void UATPCCameraLocationObject::Validate(bool bWithInterpolation)
{
	Super::Validate(bWithInterpolation);

	const auto& camera = GetCamera();
	const auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;

	if (camera.IsSettingInitialCameraMode())
	{
		SetCameraDistance(cameraMode.LocationSettings.DefaultCameraDistance, false);

		UpdateTargetOffsetTarget();
		TargetOffset.Interpolate(false, 0.f);
		UpdateSocketOffsetTarget();
		SocketOffset.Interpolate(false, 0.f);
	}
	else
	{
		SetCameraDistance(CameraDistance.TargetDistance, bWithInterpolation);
	}

	ValidateCameraView(bWithInterpolation, GetWorld()->GetDeltaSeconds());

	bEnableRoofCollisionCheckRotationOffset = false;
}

void UATPCCameraLocationObject::OnExitCameraMode()
{
	Super::OnExitCameraMode();

	auto& camera = GetCamera();
	const auto& cameraMode = camera.GetCurrentCameraMode()->CameraModeSettings;

	if (cameraMode.LocationSettings.bCacheDistanceForCurrentCameraMode)
	{
		auto& distance = CachedCameraModesDistance.FindOrAdd(camera.GetCurrentCameraModeTag());
		distance = FMath::Clamp(CameraDistance.CurrentDistance, cameraMode.LocationSettings.MinCameraDistance, cameraMode.LocationSettings.MaxCameraDistance);
	}

	//Reset scroll
	CameraDistance.TargetDistance = CameraDistance.CurrentDistance;
}

void UATPCCameraLocationObject::OnEnterCameraMode(bool bWithInterpolation)
{
	Super::OnEnterCameraMode(bWithInterpolation);

	auto& camera = GetCamera();
	const auto& cameraModeSettings = camera.GetCurrentCameraMode()->CameraModeSettings;
	auto& locationSettings = cameraModeSettings.LocationSettings;

	bool bSetDistanceFromCache = false;
	if (locationSettings.bCacheDistanceForCurrentCameraMode)
	{
		const auto prevDistance = CachedCameraModesDistance.Find(camera.GetCurrentCameraModeTag());
		if (prevDistance != nullptr && prevDistance->IsSet())
		{
			bSetDistanceFromCache = true;
			SetCameraDistance(prevDistance->GetValue(), bWithInterpolation);
		}
	}

	if (!bSetDistanceFromCache && locationSettings.bSetDistanceToDefaultOnChangeCameraMode)
	{
		SetCameraDistance(locationSettings.DefaultCameraDistance, bWithInterpolation);
	}

	RuntimeCameraToActorRotationSettings.RotationInterpolation = cameraModeSettings.RotationSettings.ViewRotationToActorRotationSettings.RotationInterpolation;

	SocketOffset.InterploationSpeed = locationSettings.SocketOffsetInterpolation;
	TargetOffset.InterploationSpeed = locationSettings.TargetOffsetInterpolation;

	Validate(camera.IsSettingInitialCameraMode() ? false : bWithInterpolation);
}

FTransform UATPCCameraLocationObject::GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace) const
{
	auto& camera = GetCamera();

	FTransform socketTransform = FTransform::Identity;

	const FRotator cameraRotation = (RelativeSocketRotation.Rotator() + FRotator(FollowTerrainRotationPitchOffset, 0.f, 0.f)).GetNormalized();

	const FTransform relativeTransform(cameraRotation.Quaternion(), RelativeSocketLocation);

	switch (TransformSpace)
	{
	case RTS_World:
	{
		socketTransform = relativeTransform * camera.GetComponentTransform();
		break;
	}
	case RTS_Actor:
	{
		if (const AActor* Actor = camera.GetOwner())
		{
			socketTransform = relativeTransform * camera.GetComponentTransform();
			socketTransform = socketTransform.GetRelativeTransform(Actor->GetTransform());
		}
		break;
	}
	case RTS_Component:
	default:;
		{
			socketTransform = relativeTransform;
			break;
		}
	}

	return socketTransform;
}

void UATPCCameraLocationObject::SetViewRotation(FRotator Rotation)
{
	const APawn* owningPawn = GetOwningPawn();
	if (owningPawn != nullptr && owningPawn->Controller != nullptr)
	{
		owningPawn->Controller->SetControlRotation(Rotation);
	}
	else
	{
		GetCamera().SetWorldRotation(Rotation);
	}
}

FRotator UATPCCameraLocationObject::GetViewRotation() const
{
	const APawn* pawn = GetOwningPawn();
	return pawn != nullptr ? pawn->GetViewRotation() : GetDesiredRotation();
}

FRotator UATPCCameraLocationObject::GetDesiredRotation() const
{
	return GetCamera().GetComponentRotation();
}

FRotator UATPCCameraLocationObject::GetTargetRotation() const
{
	auto& camera = GetCamera();
	auto& rotationSettings = camera.GetCurrentCameraMode()->CameraModeSettings.RotationSettings;
	FRotator desiredRotation = rotationSettings.bUsePawnControlRotation ? GetViewRotation() : GetDesiredRotation();

	// If inheriting rotation, check options for which components to inherit
	if (!camera.IsUsingAbsoluteRotation())
	{
		const FRotator localRelativeRotation = camera.GetRelativeRotation();
		if (!rotationSettings.bInheritPitch)
		{
			desiredRotation.Pitch = localRelativeRotation.Pitch;
		}

		if (!rotationSettings.bInheritYaw)
		{
			desiredRotation.Yaw = localRelativeRotation.Yaw;
		}

		if (!rotationSettings.bInheritRoll)
		{
			desiredRotation.Roll = localRelativeRotation.Roll;
		}
	}

	return desiredRotation;
}

FVector UATPCCameraLocationObject::GetCameraLocation() const
{
	return GetSocketTransform(NAME_None, RTS_World).GetLocation();
}

FRotator UATPCCameraLocationObject::GetCameraRotation() const
{
	return GetSocketTransform(NAME_None, RTS_World).Rotator();
}

void UATPCCameraLocationObject::UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime)
{
	auto& camera = GetCamera();
	auto& locationSettings = camera.GetCurrentCameraMode()->CameraModeSettings.LocationSettings;

	FRotator desiredRot = GetTargetRotation();
	if (bDoRotationLag)
	{
		ProcessRotationLag(desiredRot, DeltaTime);
	}
	PreviousDesiredRot = desiredRot;

	const FVector armOrigin = camera.GetComponentLocation() + GetTargetOffset();
	FVector armOriginWithLag = armOrigin;
	if (bDoLocationLag)
	{
		ProcessLocationLag(armOriginWithLag, armOrigin, DeltaTime);
	}
	PreviousArmOrigin = armOriginWithLag;

	UE_VLOG_LOCATION(this, LogATPC, Log, armOrigin, 15, FColor::Orange, TEXT("Arm origin"));
	UE_VLOG_LOCATION(this, LogATPC, Log, armOriginWithLag, 15, FColor::Green, TEXT("Arm origin lag"));

	auto calcDesiredLocation = [armOriginWithLag, desiredRot](float Distance, FVector SocketOffsets) {
		FVector desiredLoc = armOriginWithLag;
		desiredLoc -= desiredRot.Vector() * Distance;

		desiredLoc += FRotationMatrix(desiredRot).TransformVector(SocketOffsets);
		return desiredLoc;
	};

	const float oldCameraDistance = CameraDistance.CurrentDistance;
	const FVector desiredLocOldDist = calcDesiredLocation(CameraDistance.CurrentDistance, GetAllOldSocketOffsets());

	PitchCameraDistanceModifier = locationSettings.PitchDistanceCurve != nullptr ? locationSettings.PitchDistanceCurve->GetFloatValue(FRotator::NormalizeAxis(desiredRot.Pitch)) : 0.f;

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;
	const float targetCameraDistance = GetTotalCameraDistance();
	const float newCameraDistance = UATPCFunctionLibrary::InterpFloat(CameraDistance.CurrentDistance, targetCameraDistance, DeltaTime, cameraMode.LocationSettings.ZoomInterpolation, false);

	FVector desiredLoc = calcDesiredLocation(newCameraDistance, GetAllSocketOffsets());

	InternalSetCurrentCameraDistance(newCameraDistance);

	const bool bIsPrevCameraFixed = bIsCameraFixed;

	FVector resultLoc = FVector::ZeroVector;
	if (bDoTrace)
	{
		FCollisionQueryParams collisionQueryParams;
		collisionQueryParams.AddIgnoredActor(GetOwningActor());

		const FVector traceStart = armOrigin;

		FHitResult hitResultOldDist;
		const FVector traceEndOldDist = desiredLocOldDist;
		GetWorld()->SweepSingleByChannel(hitResultOldDist, traceStart, traceEndOldDist, FQuat::Identity, locationSettings.ProbeChannel, FCollisionShape::MakeSphere(locationSettings.ProbeSize), collisionQueryParams);
		UE_VLOG_ARROW(this, LogATPC, Log, traceStart, traceEndOldDist, FColor::Orange, TEXT("Trace old dist"));
		if (hitResultOldDist.bBlockingHit)
		{
			UE_VLOG_LOCATION(this, LogATPC, Log, hitResultOldDist.Location, locationSettings.ProbeSize, FColor::Orange, TEXT("Blocking hit trace old dist"));
		}

		FHitResult hitResult;
		const FVector traceEnd = desiredLoc;
		GetWorld()->SweepSingleByChannel(hitResult, traceStart, traceEnd, FQuat::Identity, locationSettings.ProbeChannel, FCollisionShape::MakeSphere(locationSettings.ProbeSize), collisionQueryParams);
		UE_VLOG_ARROW(this, LogATPC, Log, traceStart, traceEnd, FColor::Green, TEXT("Trace dist"));
		if (hitResult.bBlockingHit)
		{
			UE_VLOG_LOCATION(this, LogATPC, Log, hitResult.Location, locationSettings.ProbeSize, FColor::Green, TEXT("Blocking hit trace"));
		}

		//If some modifiers are cause collision it will use modifiers from prev time(if it wasn't collision)
		if (hitResultOldDist.bBlockingHit != hitResult.bBlockingHit)
		{
			hitResult = hitResultOldDist;
			InternalSetCurrentCameraDistance(oldCameraDistance);
			desiredLoc = desiredLocOldDist;
			SocketOffset = OldSocketOffset;
		}

		AddHitResultToDebug(hitResult);

		const bool bIsPrevCameraUsedMovementCollisionTest = bIsCameraUsedMovementCollisionTest;
		bIsCameraUsedMovementCollisionTest = false;

		// Do Movement collision test
		if (locationSettings.bDoMovementCollisionTest && hitResult.bBlockingHit && hitResult.Component.IsValid()
		    && hitResult.Component->GetCollisionResponseToChannel(locationSettings.MovementCollisionTestCollisionChannel) == ECR_Overlap)
		{
			const bool bEnableCollisionTestByMovement = !bIsPrevCameraFixed && FVector::Distance(PreviousResultLoc, desiredLoc) >= locationSettings.MovementCollisionTestMinLocationDelta;
			const float worldTimeSec = GetWorld()->GetTimeSeconds();

			if (bEnableCollisionTestByMovement || (bIsPrevCameraUsedMovementCollisionTest && worldTimeSec < LastTimeUseMovementCollisionTest + locationSettings.MovementCollisionTestDuration))
			{
				FHitResult onlyCameraHitResult;
				GetWorld()->SweepSingleByChannel(onlyCameraHitResult, traceStart, traceStart, FQuat::Identity, locationSettings.ProbeChannel, FCollisionShape::MakeSphere(locationSettings.ProbeSize), collisionQueryParams);
				if (!onlyCameraHitResult.bBlockingHit)
				{
					hitResult = onlyCameraHitResult;

					bIsCameraUsedMovementCollisionTest = true;

					if (bEnableCollisionTestByMovement)
					{
						LastTimeUseMovementCollisionTest = worldTimeSec;
					}
				}
			}
		}

		UnfixedCameraPosition = desiredLoc;

		resultLoc = BlendLocations(desiredLoc, /*armOrigin*/ armOriginWithLag, hitResult.bBlockingHit, hitResult.Location, DeltaTime);

		bIsCameraFixed = hitResult.bBlockingHit && !resultLoc.Equals(desiredLoc);
	}
	else
	{
		resultLoc = desiredLoc;
		bIsCameraFixed = false;
		UnfixedCameraPosition = resultLoc;
	}

	PreviousResultLoc = resultLoc;

	// Form a transform for new world transform for camera
	FTransform worldCamTM(desiredRot, resultLoc);
	// Convert to relative to component
	FTransform relCamTM = worldCamTM.GetRelativeTransform(camera.GetComponentTransform());

	// Update socket location/rotation
	RelativeSocketLocation = relCamTM.GetLocation();
	RelativeSocketRotation = relCamTM.GetRotation();

	camera.UpdateChildTransforms();
}

void UATPCCameraLocationObject::SetCameraDistance(float NewDist, bool bInterpolate)
{
	const auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;

	CameraDistance.TargetDistance = FMath::Clamp(NewDist, cameraMode.LocationSettings.MinCameraDistance, cameraMode.LocationSettings.MaxCameraDistance);
	if (!bInterpolate)
	{
		InternalSetCurrentCameraDistance(GetTotalCameraDistance());
	}
}

float UATPCCameraLocationObject::GetCameraTargetDistance() const
{
	return CameraDistance.TargetDistance;
}

float UATPCCameraLocationObject::GetCameraDistance() const
{
	return CameraDistance.CurrentDistance;
}

float UATPCCameraLocationObject::GetRealCameraDistance() const
{
	auto& camera = GetCamera();

	return FVector::Dist(camera.GetCameraLocation(), camera.GetComponentLocation());
}

FVector UATPCCameraLocationObject::GetSocketOffset() const
{
	return SocketOffset.Current;
}

FVector UATPCCameraLocationObject::GetAllSocketOffsets() const
{
	return SocketOffset.Current + FollowTerrainSocketOffset;
}

FVector UATPCCameraLocationObject::GetTargetOffset() const
{
	return TargetOffset.Current;
}

void UATPCCameraLocationObject::SetOverrideCameraRotation(const FRotator& NewOverrideRotation, bool bClampByCameraModeRotationLimits /*= false*/)
{
	OverrideCameraRotation = NewOverrideRotation;

	if (bClampByCameraModeRotationLimits)
	{
		ClampCameraRotation(OverrideCameraRotation.GetValue());
	}
}

void UATPCCameraLocationObject::ResetOverrideCameraRotation()
{
	OverrideCameraRotation.Reset();
}

bool UATPCCameraLocationObject::IsOverrideCameraRotation() const
{
	return OverrideCameraRotation.IsSet();
}

const FRotator& UATPCCameraLocationObject::GetOverrideCameraRotation() const
{
	static const FRotator defaultValue = FRotator();
	return OverrideCameraRotation.Get(defaultValue);
}

void UATPCCameraLocationObject::AttachCameraToComponent(USceneComponent* InParentComponent, FVector InRelativeLocation, FName InSocketName, bool bWithInterp, float InterpSpeed)
{
	auto& camera = GetCamera();

	const FAttachmentTransformRules attachmentRules = bWithInterp ? FAttachmentTransformRules::KeepWorldTransform : FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	camera.AttachToComponent(InParentComponent, attachmentRules, InSocketName);

	bAttachCameraWithInterp = bWithInterp;
	AttachCameraRelativeLocation = InRelativeLocation;
	AttachCameraInterpSpeed = InterpSpeed;
	if (!bWithInterp)
	{
		camera.SetRelativeLocation(InRelativeLocation);
	}
}

FVector UATPCCameraLocationObject::GetAllOldSocketOffsets() const
{
	return OldSocketOffset.Current + FollowTerrainSocketOffset;
}

void UATPCCameraLocationObject::InternalSetCurrentCameraDistance(float NewDist)
{
	CameraDistance.CurrentDistance = NewDist;
}

void UATPCCameraLocationObject::ProcessLocationLag(FVector& DesiredLoc, const FVector& ArmOrigin, float DeltaSeconds)
{
	const auto& locationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.LocationSettings;
	const auto& cameraLagSettings = locationSettings.CameraLocationLagSettings;
	if (!locationSettings.bEnableCameraLocationLag)
	{
		if (!LocationLagDelta.IsNearlyZero())
		{
			LocationLagDelta = FMath::VInterpTo(LocationLagDelta, FVector::ZeroVector, DeltaSeconds, LastCameraLagSpeed);
			DesiredLoc += LocationLagDelta;
		}

		return;
	}

	FVector lagDesiredLocation = DesiredLoc;
	if (cameraLagSettings.bUseCameraLagSubstepping && DeltaSeconds > cameraLagSettings.CameraLagMaxTimeStep && cameraLagSettings.CameraLagSpeed > 0.f)
	{
		const FVector armMovementStep = (lagDesiredLocation - PreviousArmOrigin) * (1.f / DeltaSeconds);
		FVector lerpTarget = PreviousArmOrigin;

		float remainingTime = DeltaSeconds;
		while (remainingTime > KINDA_SMALL_NUMBER)
		{
			const float LerpAmount = FMath::Min(cameraLagSettings.CameraLagMaxTimeStep, remainingTime);
			lerpTarget += armMovementStep * LerpAmount;
			remainingTime -= LerpAmount;

			lagDesiredLocation = FMath::VInterpTo(PreviousArmOrigin, lerpTarget, LerpAmount, cameraLagSettings.CameraLagSpeed);
			//PreviousDesiredLoc = lagDesiredLocation;
		}
	}
	else
	{
		lagDesiredLocation = FMath::VInterpTo(PreviousArmOrigin, lagDesiredLocation, DeltaSeconds, cameraLagSettings.CameraLagSpeed);
	}

	// Clamp distance if requested
	bool bClampedDist = false;
	if (cameraLagSettings.CameraLagMaxDistance > 0.f)
	{
		const FVector fromOrigin = lagDesiredLocation - ArmOrigin;
		if (fromOrigin.SizeSquared() > FMath::Square(cameraLagSettings.CameraLagMaxDistance))
		{
			lagDesiredLocation = ArmOrigin + fromOrigin.GetClampedToMaxSize(cameraLagSettings.CameraLagMaxDistance);
			bClampedDist = true;
		}
	}

	const auto oldDesiredLoc = DesiredLoc;

	if (cameraLagSettings.bEnableCameraLagForXY)
	{
		DesiredLoc.X = lagDesiredLocation.X;
		DesiredLoc.Y = lagDesiredLocation.Y;
	}
	if (cameraLagSettings.bEnableCameraLagForZ)
	{
		DesiredLoc.Z = lagDesiredLocation.Z;
	}

	LocationLagDelta = DesiredLoc - oldDesiredLoc;
	LastCameraLagSpeed = cameraLagSettings.CameraLagSpeed;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (cameraLagSettings.bDrawDebugLagMarkers)
	{
		DrawDebugSphere(GetWorld(), ArmOrigin, 5.f, 8, FColor::Green);
		DrawDebugSphere(GetWorld(), DesiredLoc, 5.f, 8, FColor::Yellow);

		const FVector toOrigin = ArmOrigin - DesiredLoc;
		DrawDebugDirectionalArrow(GetWorld(), DesiredLoc, DesiredLoc + toOrigin * 0.5f, 7.5f, bClampedDist ? FColor::Red : FColor::Green);
		DrawDebugDirectionalArrow(GetWorld(), DesiredLoc + toOrigin * 0.5f, ArmOrigin, 7.5f, bClampedDist ? FColor::Red : FColor::Green);
	}
#endif
}

void UATPCCameraLocationObject::ProcessRotationLag(FRotator& DesiredRotation, float DeltaSeconds)
{
	const auto& locationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.LocationSettings;
	const auto& cameraLagSettings = locationSettings.CameraRotationLagSettings;
	if (!locationSettings.bEnableCameraRotationLag)
	{
		return;
	}

	if (cameraLagSettings.bUseCameraLagSubstepping && DeltaSeconds > cameraLagSettings.CameraLagMaxTimeStep && cameraLagSettings.CameraLagSpeed > 0.f)
	{
		const FRotator armRotStep = (DesiredRotation - PreviousDesiredRot).GetNormalized() * (1.f / DeltaSeconds);
		FRotator lerpTarget = PreviousDesiredRot;
		float remainingTime = DeltaSeconds;
		while (remainingTime > KINDA_SMALL_NUMBER)
		{
			const float lerpAmount = FMath::Min(cameraLagSettings.CameraLagMaxTimeStep, remainingTime);
			lerpTarget += armRotStep * lerpAmount;
			remainingTime -= lerpAmount;

			DesiredRotation = FRotator(FMath::QInterpTo(FQuat(PreviousDesiredRot), FQuat(lerpTarget), lerpAmount, cameraLagSettings.CameraLagSpeed));
			PreviousDesiredRot = DesiredRotation;
		}
	}
	else
	{
		DesiredRotation = FRotator(FMath::QInterpTo(FQuat(PreviousDesiredRot), FQuat(DesiredRotation), DeltaSeconds, cameraLagSettings.CameraLagSpeed));
	}
}

FVector UATPCCameraLocationObject::BlendLocations(const FVector& DesiredArmLocation, const FVector& ArmOrigin, bool bHitSomething, const FVector& TraceHitLocation, float DeltaTime)
{
	FVector resultLocation;

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;

	if (bHitSomething)
	{
		resultLocation = TraceHitLocation;

		InternalSetCurrentCameraDistance(FVector::Dist(ArmOrigin, TraceHitLocation));

		cameraMode.LocationSettings.ZoomInterpolation.ResetCurrentSpeed();
	}
	else
	{
		resultLocation = DesiredArmLocation;
	}
	return resultLocation;
}

float UATPCCameraLocationObject::GetCameraDistanceModifiers() const
{
	return PitchCameraDistanceModifier;
}

float UATPCCameraLocationObject::GetTotalCameraDistance() const
{
	return CameraDistance.TargetDistance + GetCameraDistanceModifiers();
}

void UATPCCameraLocationObject::UpdateTargetOffsetTarget()
{
	TargetOffset.Target = GetCamera().GetCurrentCameraMode()->CameraModeSettings.LocationSettings.TargetOffset;
}

void UATPCCameraLocationObject::UpdateSocketOffsetTarget()
{
	const auto& locationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.LocationSettings;

	SocketOffset.Target = locationSettings.SocketOffsetCurve != nullptr ? locationSettings.SocketOffsetCurve->GetVectorValue(CameraDistance.CurrentDistance) : FVector::ZeroVector;
}

FATPCRotationOffsetSettings& UATPCCameraLocationObject::GetCurrentRotationOffsetSettings()
{
	auto& rotationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.RotationSettings;

	return bEnableRoofCollisionCheckRotationOffset ? rotationSettings.RoofCollisionCheckSettings.RotationOffsetSettings : rotationSettings.RotationOffsetSettings;
}

const FATPCRotationOffsetSettings& UATPCCameraLocationObject::GetCurrentRotationOffsetSettings() const
{
	return const_cast<UATPCCameraLocationObject*>(this)->GetCurrentRotationOffsetSettings();
}

void UATPCCameraLocationObject::ProcessRoofCollisionCheck()
{
	auto& rotationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.RotationSettings;

	if (rotationSettings.bEnableRoofCollisionCheckSettings)
	{
		FHitResult eyesHit, actorFirstHit, actorSecondHit;
		FindRoofCollision(eyesHit, actorFirstHit, actorSecondHit);

		bEnableRoofCollisionCheckRotationOffset = !eyesHit.bBlockingHit && (actorFirstHit.bBlockingHit || actorSecondHit.bBlockingHit);

#if !UE_BUILD_SHIPPING
		if (GetCamera().DebugRules.bEnableRoofCollisionCheckDebug)
		{
			const FColor color = FColor::Orange;
			GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Roof Collision Check End Debug -----"));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("EyesHit: block %d, hit actor: %s"), eyesHit.bBlockingHit, *GetNameSafe(eyesHit.GetActor())));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("EyesHit: block %d, hit actor: %s"), actorFirstHit.bBlockingHit, *GetNameSafe(actorFirstHit.GetActor())));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("EyesHit: block %d, hit actor: %s"), actorSecondHit.bBlockingHit, *GetNameSafe(actorSecondHit.GetActor())));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Enable rotation offset: %d"), bEnableRoofCollisionCheckRotationOffset));
			GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Roof Collision Check Start Debug -----"));
		}
#endif //!UE_BUILD_SHIPPING
	}
}

FRotator UATPCCameraLocationObject::GetLastTickTargetRotationDelta() const
{
	return LastTickTargetRotationDelta;
}

void UATPCCameraLocationObject::ClampCameraRotation(FRotator& Rotation)
{
	const auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;
	if (cameraMode.bEnableRotationSettings)
	{
		auto& rotationSettings = cameraMode.RotationSettings;
		Rotation.Pitch = FMath::ClampAngle(Rotation.Pitch, rotationSettings.ViewPitchMin, rotationSettings.ViewPitchMax);
		Rotation.Yaw = FMath::ClampAngle(Rotation.Yaw, rotationSettings.ViewYawMin, rotationSettings.ViewYawMax);
	}
}

#if ENABLE_VISUAL_LOG
void UATPCCameraLocationObject::GrabDebugSnapshot(FVisualLogEntry* Snapshot) const
{
	const FName category = "LocationObject";

	Snapshot->AddText(FString::Printf(TEXT("Camera distance: %f"), CameraDistance.CurrentDistance), category, ELogVerbosity::Log);
	Snapshot->AddText(FString::Printf(TEXT("Camera location: %s"), *GetCameraLocation().ToString()), category, ELogVerbosity::Log);
	Snapshot->AddText(FString::Printf(TEXT("Camera fixed: %s"), *LexToString(bIsCameraFixed)), category, ELogVerbosity::Log);
}
#endif

void UATPCCameraLocationObject::UpdateOffsetCameraRotationTime(float DeltaSeconds)
{
	const auto& rotationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.RotationSettings;

	const bool bEnableRotationOffset = bEnableRoofCollisionCheckRotationOffset ? rotationSettings.bEnableRoofCollisionCheckSettings : rotationSettings.bEnableRotationOffset;

	if (bEnableRotationOffset)
	{
		const APawn* owningPawn = GetOwningPawn();
		if (owningPawn != nullptr && owningPawn->Controller != nullptr)
		{
			const FRotator targetRotation = GetTargetRotation();
			const float worldTimeSec = GetWorld()->TimeSeconds;

			const auto& rotationOffsetSettings = GetCurrentRotationOffsetSettings();

			if (FMath::IsNearlyEqual(LastTargetRotation.Pitch, targetRotation.Pitch)
			    && (!rotationOffsetSettings.bActivateOnlyIfMovement
			        || owningPawn->GetVelocity().SizeSquared() > FMath::Square(rotationOffsetSettings.MinMovementSpeedForActivate)))
			{
				if (!RuntimeOffsetRotationSettings.bPendingRotationOffset)
				{
					RuntimeOffsetRotationSettings.bPendingRotationOffset = true;
					RuntimeOffsetRotationSettings.LastChangeCameraRotationTime = worldTimeSec;
				}
			}
			else
			{
				RuntimeOffsetRotationSettings.bPendingRotationOffset = false;
			}

			if (RuntimeOffsetRotationSettings.bPendingRotationOffset && worldTimeSec - RuntimeOffsetRotationSettings.LastChangeCameraRotationTime >= rotationOffsetSettings.StartOffsetDelay)
			{
				UpdateOffsetCameraRotation(true, DeltaSeconds);
			}
		}
	}
}

void UATPCCameraLocationObject::UpdateOffsetCameraRotation(bool bWithInterp, float DeltaSeconds)
{
	const APawn* owningPawn = GetOwningPawn();
	if (owningPawn != nullptr && owningPawn->Controller != nullptr)
	{
		const auto& rotationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.RotationSettings;
		auto& rotationOffsetSettings = GetCurrentRotationOffsetSettings();

		const float pitchTarget = FMath::ClampAngle(FRotator::NormalizeAxis(rotationOffsetSettings.PitchOffset), rotationSettings.ViewPitchMin, rotationSettings.ViewPitchMax);

		FRotator newViewRotation = GetTargetRotation();

		newViewRotation.Pitch = bWithInterp ?
                                    UATPCFunctionLibrary::InterpRotator(FRotator(newViewRotation.Pitch, 0.f, 0.f), FRotator(pitchTarget, 0.f, 0.f), DeltaSeconds, rotationOffsetSettings.RotationInterpolation).Pitch :
                                    pitchTarget;

		SetViewRotation(newViewRotation);
	}
}

void UATPCCameraLocationObject::UpdateViewRotationToActorRotationTime(float DeltaSeconds)
{
	const auto& rotationSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.RotationSettings;

	const APawn* owningPawn = GetOwningPawn();
	if (rotationSettings.bEnableViewRotationToActorRotation && owningPawn != nullptr && owningPawn->Controller != nullptr)
	{
		auto& cameraToActorRotationSettings = rotationSettings.ViewRotationToActorRotationSettings;
		const float worldTimeSec = GetWorld()->TimeSeconds;

		const float viewRotationYaw = GetTargetRotation().Yaw;
		const float owningActorYawRotation = owningPawn->GetActorRotation().Yaw;
		const float actorToViewRotDelta = FMath::Abs(FRotator::NormalizeAxis(owningActorYawRotation - viewRotationYaw));

		if (actorToViewRotDelta < cameraToActorRotationSettings.MaxDeltaForChange
		    && FMath::IsNearlyEqual(LastTargetRotation.Yaw, viewRotationYaw, 0.01f)
		    && owningPawn->GetVelocity().SizeSquared() > KINDA_SMALL_NUMBER)
		{
			if (!RuntimeCameraToActorRotationSettings.bPendingRotationOffset)
			{
				RuntimeCameraToActorRotationSettings.bPendingRotationOffset = true;
				RuntimeCameraToActorRotationSettings.LastChangeCameraRotationTime = worldTimeSec;
			}
		}
		else
		{
			RuntimeCameraToActorRotationSettings.RotationInterpolation.ResetCurrentSpeed();
			RuntimeCameraToActorRotationSettings.bPendingRotationOffset = false;
		}

		const float startOffsetDelay = cameraToActorRotationSettings.StartChangeDelay;

		if (RuntimeCameraToActorRotationSettings.bPendingRotationOffset && worldTimeSec - RuntimeCameraToActorRotationSettings.LastChangeCameraRotationTime >= startOffsetDelay)
		{
			UpdateViewRotationToActorRotation(true, DeltaSeconds);
		}
	}
}

void UATPCCameraLocationObject::UpdateViewRotationToActorRotation(bool bWithInterp, float DeltaSeconds)
{
	FRotator viewRot = GetTargetRotation();

	const float targetYawRotation = GetOwningActor()->GetActorRotation().Yaw;

	const float newViewRotYaw = bWithInterp ? UATPCFunctionLibrary::InterpRotator(FRotator(0.f, viewRot.Yaw, 0.f), FRotator(0.f, targetYawRotation, 0.f), DeltaSeconds, RuntimeCameraToActorRotationSettings.RotationInterpolation).Yaw : targetYawRotation;

	viewRot.Yaw = newViewRotYaw;
	SetViewRotation(viewRot);
}

void UATPCCameraLocationObject::FindRoofCollision(FHitResult& EyesHit, FHitResult& ActorFirstRoofHit, FHitResult& ActorSecondRoofHit)
{
	const auto& roofCheckSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.RotationSettings.RoofCollisionCheckSettings;

	FVector actorViewPoint;
	FRotator actorViewRotator;

	const AActor* owningActor = GetOwningActor();

	owningActor->GetActorEyesViewPoint(actorViewPoint, actorViewRotator);

	const auto drawDebugType = GetCamera().DebugRules.bEnableRoofCollisionCheckDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;

	const FVector eyesTraceStart = actorViewPoint + owningActor->GetActorRotation().Vector() * roofCheckSettings.EyesBoxTraceHalfSize.X;
	UKismetSystemLibrary::BoxTraceSingleForObjects(this, eyesTraceStart, eyesTraceStart + 1.f, roofCheckSettings.EyesBoxTraceHalfSize, owningActor->GetActorRotation(), roofCheckSettings.TraceObjectTypes, false, {}, drawDebugType, EyesHit, true);

	const FRotator actorRoofTraceRotation = FRotator(roofCheckSettings.RoofTraceAngleFirst, 0.f, 0.f) + owningActor->GetActorRotation();
	const FVector actorRoofTraceStart = actorViewPoint + actorRoofTraceRotation.Vector() * roofCheckSettings.RoofBoxTraceHalfSizeFirst.X;
	UKismetSystemLibrary::BoxTraceSingleForObjects(this, actorRoofTraceStart, actorRoofTraceStart + 1.f, roofCheckSettings.RoofBoxTraceHalfSizeFirst, actorRoofTraceRotation, roofCheckSettings.TraceObjectTypes, false, {}, drawDebugType, ActorFirstRoofHit, true);

	const FRotator cameraRoofTraceRotation = FRotator(roofCheckSettings.RoofTraceAngleSecond, 0.f, 0.f) + owningActor->GetActorRotation();
	const FVector cameraRoofTraceStart = actorViewPoint + cameraRoofTraceRotation.Vector() * roofCheckSettings.RoofBoxTraceHalfSizeSecond.X;
	UKismetSystemLibrary::BoxTraceSingleForObjects(this, cameraRoofTraceStart, cameraRoofTraceStart + 1.f, roofCheckSettings.RoofBoxTraceHalfSizeSecond, cameraRoofTraceRotation, roofCheckSettings.TraceObjectTypes, false, {}, drawDebugType, ActorSecondRoofHit, true);
}

void UATPCCameraLocationObject::ValidateCameraView(bool bWithInterpolation, float DeltaTime)
{
	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;
	if (!cameraMode.bEnableRotationSettings)
	{
		return;
	}

	if (const APlayerController* controller = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerCameraManager* cameraManager = controller->PlayerCameraManager)
		{
			auto& rotationSettings = cameraMode.RotationSettings;

			auto& interpSpeed = rotationSettings.ViewInterpolation;

			bool bAllValuesFullyInterpolated = ValidateRotationValue(rotationSettings.ViewPitchMin, cameraManager->ViewPitchMin, false, DeltaTime, true, interpSpeed);
			bAllValuesFullyInterpolated &= ValidateRotationValue(rotationSettings.ViewPitchMax, cameraManager->ViewPitchMax, true, DeltaTime, true, interpSpeed);

			bAllValuesFullyInterpolated &= ValidateRotationValue(rotationSettings.ViewYawMin, cameraManager->ViewYawMin, false, DeltaTime, true, interpSpeed);
			bAllValuesFullyInterpolated &= ValidateRotationValue(rotationSettings.ViewYawMax, cameraManager->ViewYawMax, true, DeltaTime, true, interpSpeed);

			if (bAllValuesFullyInterpolated)
			{
				interpSpeed.ResetCurrentSpeed();
			}
		}
	}
}

bool UATPCCameraLocationObject::ValidateRotationValue(float CompareValue, float& Value, bool bLessCompare, float DeltaTime, bool bInterpolate, FATPCInterploationSpeed& InterpSpeed)
{
	if (bInterpolate)
	{
		Value = UATPCFunctionLibrary::InterpFloat(Value, CompareValue, DeltaTime, InterpSpeed, false);
		return FMath::IsNearlyEqual(Value, CompareValue, InterpSpeed.ResetInterpSpeedTolerance);
	}

	Value = CompareValue;
	return true;
}

void UATPCCameraLocationObject::ShowDebug()
{
	const FColor color = FColor::Green;
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Location Object End Debug -----"));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Trace hit component: %s"), *GetNameSafe(DebugData.TraceHitResult.GetComponent())));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Trace hit actor: %s"), *GetNameSafe(DebugData.TraceHitResult.GetActor())));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Trace blocking hit: %s"), *LexToString(DebugData.TraceHitResult.bBlockingHit)));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Camera location: %s"), *GetCameraLocation().ToString()));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Location lag dist: %.2f"), LocationLagDelta.Size()));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Current target distance: %.2f"), CameraDistance.TargetDistance));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Current total target distance: %.2f"), GetTotalCameraDistance()));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Current camera distance: %.2f"), CameraDistance.CurrentDistance));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Real camera distance: %.2f"), GetRealCameraDistance()));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Is Camera Fixed: %s"), *LexToString(bIsCameraFixed)));

	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Location Object Start Debug -----"));
}

void UATPCCameraLocationObject::AddHitResultToDebug(const FHitResult& HitResult)
{
#if !UE_BUILD_SHIPPING
	if (GetCamera().DebugRules.bEnableLocationObjectDebug)
	{
		DebugData.TraceHitResult = HitResult;
	}
#endif
}
