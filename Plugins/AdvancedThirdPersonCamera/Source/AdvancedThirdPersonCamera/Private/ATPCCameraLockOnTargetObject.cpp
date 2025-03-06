// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraLockOnTargetObject.h"

#include "ATPCArrowDebugActor.h"
#include "ATPCCameraComponent.h"
#include "ATPCCameraLocationObject.h"
#include "ATPCCameraModeDataAsset.h"
#include "ATPCFunctionLibrary.h"
#include "ATPCLockOnTargetLocationComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

void UATPCCameraLockOnTargetObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto& camera = GetCamera();
	auto locationObject = camera.GetCameraLocationObject();
	auto& lockOnTargetSettings = GetLockOnTargetSettings();

	if (TargetActor.IsValid() && locationObject != nullptr && (lockOnTargetSettings.RotateCameraByPitch || lockOnTargetSettings.RotateCameraByYaw))
	{
		if (!bPauseLock)
		{
			if (lockOnTargetSettings.bResetLockOnLostVisibleTarget && !IsActorVisible(TargetActor.Get()))
			{
				InternalSetTargetActor(nullptr, EATPCChangeTargetReason::LostByVisible);
			}
			else if (lockOnTargetSettings.bResetTargetOnReachMaxDistance && !IsValidDistanceToActor(TargetActor.Get()))
			{
				InternalSetTargetActor(nullptr, EATPCChangeTargetReason::LostByDistance);
			}

			if (TargetActor.IsValid())
			{
				RotateCameraToActor(TargetActor.Get(), DeltaSeconds);
			}
		}

		const float minInputDelta = 0.1f;
		const FRotator viewRotaitonDelta = locationObject->GetLastTickTargetRotationDelta();

		// If has player input
		if (!FMath::IsNearlyEqual(viewRotaitonDelta.Yaw, 0.f, minInputDelta) || !FMath::IsNearlyEqual(viewRotaitonDelta.Pitch, 0.f, minInputDelta))
		{
			if (lockOnTargetSettings.bResetTargetAfterPlayerInput)
			{
				if (AccumulatedPlayerInput.IsSet())
				{
					AccumulatedPlayerInput->Pitch += viewRotaitonDelta.Pitch;
					AccumulatedPlayerInput->Yaw += viewRotaitonDelta.Yaw;
				}
				else
				{
					AccumulatedPlayerInput = viewRotaitonDelta;
				}

				if (lockOnTargetSettings.ResetAccumulatedPlayerInputForResetTargetDelay > 0.f + KINDA_SMALL_NUMBER)
				{
					GetWorld()->GetTimerManager().SetTimer(ResetAccumulatedPlayerInputTimerHandle, this, &UATPCCameraLockOnTargetObject::ResetAccumulatedPlayerInput, lockOnTargetSettings.ResetAccumulatedPlayerInputForResetTargetDelay, false);
				}
			}

			if (lockOnTargetSettings.bPauseLockAfterPlayerInput && lockOnTargetSettings.PauseLockAfterPlayerInputTime > 0.f + KINDA_SMALL_NUMBER)
			{
				PauseLock();
				GetWorld()->GetTimerManager().SetTimer(PauseLockTimerHandle, this, &UATPCCameraLockOnTargetObject::ResumeLock, lockOnTargetSettings.PauseLockAfterPlayerInputTime, false);
			}
		}
		else
		{
			if (lockOnTargetSettings.bResetTargetAfterPlayerInput && lockOnTargetSettings.ResetAccumulatedPlayerInputForResetTargetDelay <= 0.f + KINDA_SMALL_NUMBER)
			{
				ResetAccumulatedPlayerInput();
			}
		}

		if (lockOnTargetSettings.bResetTargetAfterPlayerInput && AccumulatedPlayerInput.IsSet()
		    && (FMath::Abs(AccumulatedPlayerInput->Yaw) > FMath::Abs(lockOnTargetSettings.RequiredPlayerInputForResetTarget.Yaw) || FMath::Abs(AccumulatedPlayerInput->Pitch) > FMath::Abs(lockOnTargetSettings.RequiredPlayerInputForResetTarget.Pitch)))
		{
			InternalSetTargetActor(nullptr, EATPCChangeTargetReason::LostByPlayerInput);
		}
	}

#if !UE_BUILD_SHIPPING
	if (camera.DebugRules.bEnableLockOnTargetDebug)
	{
		PrintDebug();
	}
	if (camera.DebugRules.bLockOnTargetShowTargetDebug)
	{
		ShowTargetActor();
	}

#endif
}

void UATPCCameraLockOnTargetObject::OnEnterCameraMode(bool bWithInterpolation)
{
	Super::OnEnterCameraMode(bWithInterpolation);

	if (GetLockOnTargetSettings().bHardLockOnTarget)
	{
		if (APlayerController* playerController = GetPlayerController())
		{
			playerController->SetIgnoreLookInput(true);
		}
	}
}

void UATPCCameraLockOnTargetObject::OnExitCameraMode()
{
	Super::OnExitCameraMode();

	auto& lockOnTargetSettings = GetLockOnTargetSettings();
	if (lockOnTargetSettings.bHardLockOnTarget)
	{
		if (APlayerController* playerController = GetPlayerController())
		{
			playerController->SetIgnoreLookInput(false);
		}
	}

	if (lockOnTargetSettings.bResetTargetOnChangeCameraMode)
	{
		InternalSetTargetActor(nullptr, EATPCChangeTargetReason::LostByExitCameraMode);
	}
}

float UATPCCameraLockOnTargetObject::GetDistanceSquareToActor(AActor* Actor) const
{
	return Actor != nullptr ? FVector::DistSquared(GetTargetLocation(Actor), GetCamera().GetOwner()->GetActorLocation()) : 0.f;
}

FVector UATPCCameraLockOnTargetObject::GetTargetLocation(AActor* Actor) const
{
	if (Actor != nullptr)
	{
		auto locationComponent = Actor->FindComponentByClass<UATPCLockOnTargetLocationComponent>();
		return locationComponent != nullptr ? locationComponent->GetTargetLocation() : Actor->GetActorLocation();
	}
	return FVector::ZeroVector;
}

bool UATPCCameraLockOnTargetObject::IsValidDistanceToActor(AActor* Actor) const
{
	if (Actor != nullptr)
	{
		auto& lockOnTargetSettings = GetLockOnTargetSettings();
		return !lockOnTargetSettings.bUseMaxLockDistance || GetDistanceSquareToActor(Actor) <= lockOnTargetSettings.MaxLockDistance * lockOnTargetSettings.MaxLockDistance;
	}
	return false;
}

bool UATPCCameraLockOnTargetObject::IsActorVisible(AActor* Actor) const
{
	if (Actor != nullptr)
	{
		auto& lockOnTargetSettings = GetLockOnTargetSettings();
		if (lockOnTargetSettings.bUseCheckTargetVisibility)
		{
			FHitResult hitResult;
			UKismetSystemLibrary::LineTraceSingle(Actor, GetCamera().GetCameraLocation(), GetTargetLocation(Actor), UCollisionProfile::Get()->ConvertToTraceType(lockOnTargetSettings.CheckVisibilityTraceChannel), false, { GetOwningActor(), Actor }, EDrawDebugTrace::None, hitResult, true);
			return !hitResult.bBlockingHit;
		}
		return true;
	}
	return false;
}

FRotator UATPCCameraLockOnTargetObject::GetRotationToTarget(AActor* Actor) const
{
	return Actor != nullptr ? FRotationMatrix::MakeFromX(GetTargetLocation(Actor) - GetOwningActor()->GetActorLocation()).Rotator() : FRotator::ZeroRotator;
}

void UATPCCameraLockOnTargetObject::RotateCameraToActor(AActor* Actor, float DeltaSeconds)
{
	if (Actor == nullptr)
	{
		return;
	}

	auto& camera = GetCamera();
	if (auto locationObject = camera.GetCameraLocationObject())
	{
		auto& lockOnTargetSettings = GetLockOnTargetSettings();

		auto targetRotation = GetRotationToTarget(Actor);
		const auto currentViewRotation = camera.GetCameraLocationObject()->GetTargetRotation();

		if (lockOnTargetSettings.bUseDesiredConeRotation)
		{
			const auto deltaCurrentViewToTarget = (currentViewRotation - targetRotation).GetNormalized();
			if (FMath::Abs(deltaCurrentViewToTarget.Yaw) > lockOnTargetSettings.DeisredConeRotationYaw)
			{
				targetRotation.Yaw = UKismetMathLibrary::ComposeRotators(targetRotation, FRotator(0.f, lockOnTargetSettings.DeisredConeRotationYaw * (deltaCurrentViewToTarget.Yaw > 0 ? 1 : -1), 0.f)).Yaw;
			}
			else
			{
				targetRotation.Yaw = currentViewRotation.Yaw;
			}
		}
		auto resultRotation = UATPCFunctionLibrary::InterpRotator(currentViewRotation, targetRotation, DeltaSeconds, lockOnTargetSettings.CameraRotationInterpolation, false);

		if (!lockOnTargetSettings.RotateCameraByYaw)
		{
			resultRotation.Yaw = currentViewRotation.Yaw;
		}
		if (!lockOnTargetSettings.RotateCameraByPitch)
		{
			resultRotation.Pitch = currentViewRotation.Pitch;
		}

		locationObject->SetOverrideCameraRotation(resultRotation, lockOnTargetSettings.bClampByCameraModeRotationLimits);
	}
}

bool UATPCCameraLockOnTargetObject::CanSetActorAsTarget(AActor* Actor) const
{
	return Actor != nullptr && IsActorVisible(Actor) && IsValidDistanceToActor(Actor);
}

bool UATPCCameraLockOnTargetObject::SetTargetActor(AActor* NewTargetActor)
{
	return InternalSetTargetActor(NewTargetActor, EATPCChangeTargetReason::SetNew);
}

AActor* UATPCCameraLockOnTargetObject::GetTargetActor() const
{
	return TargetActor.Get();
}

const FATPCLockOnTargetSettings& UATPCCameraLockOnTargetObject::GetLockOnTargetSettings() const
{
	return const_cast<UATPCCameraLockOnTargetObject*>(this)->GetLockOnTargetSettings();
}

FATPCLockOnTargetSettings& UATPCCameraLockOnTargetObject::GetLockOnTargetSettings()
{
	return GetCamera().GetCurrentCameraMode()->CameraModeSettings.LockOnTargetSettings;
}

bool UATPCCameraLockOnTargetObject::InternalSetTargetActor(AActor* NewTargetActor, EATPCChangeTargetReason ChangeTargetReason)
{
	if (TargetActor.Get() != NewTargetActor && (NewTargetActor == nullptr || CanSetActorAsTarget(NewTargetActor)))
	{
		ResumeLock();

		if (auto locationObject = GetCamera().GetCameraLocationObject())
		{
			locationObject->ResetOverrideCameraRotation();
		}

		if (NewTargetActor == nullptr || GetLockOnTargetSettings().bResetInterpolationSpeedAfterChangeTarget)
		{
			GetLockOnTargetSettings().CameraRotationInterpolation.ResetCurrentSpeed();
		}

		ResetAccumulatedPlayerInput();

		TargetActor = NewTargetActor;

		if (TargetDebugActor != nullptr)
		{
			TargetDebugActor->PickActor(NewTargetActor);
		}

		OnTargetChangeDelegate.Broadcast(NewTargetActor, ChangeTargetReason);
		return true;
	}
	return false;
}

void UATPCCameraLockOnTargetObject::PauseLock()
{
	bPauseLock = true;

	if (auto locationObject = GetCamera().GetCameraLocationObject())
	{
		locationObject->ResetOverrideCameraRotation();
	}
	GetLockOnTargetSettings().CameraRotationInterpolation.ResetCurrentSpeed();
}

void UATPCCameraLockOnTargetObject::ResumeLock()
{
	bPauseLock = false;
	GetWorld()->GetTimerManager().ClearTimer(PauseLockTimerHandle);
}

void UATPCCameraLockOnTargetObject::ResetAccumulatedPlayerInput()
{
	AccumulatedPlayerInput.Reset();
	GetWorld()->GetTimerManager().ClearTimer(ResetAccumulatedPlayerInputTimerHandle);
}

void UATPCCameraLockOnTargetObject::ShowTargetActor()
{
	if (TargetDebugActor == nullptr)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		TargetDebugActor = GetWorld()->SpawnActor<AATPCArrowDebugActor>(spawnParams);
	}
	TargetDebugActor->PickActor(TargetActor.Get());
}

void UATPCCameraLockOnTargetObject::PrintDebug()
{
	const FColor color = FColor::Orange;
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Lock On Target Object End Debug -----"));

	if (TargetActor.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Interp Rotation Speed: %s"), *GetLockOnTargetSettings().CameraRotationInterpolation.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Is paused lock: %s. Remaining pause time: %.2f"), *UKismetStringLibrary::Conv_BoolToString(bPauseLock), GetWorld()->GetTimerManager().GetTimerRemaining(PauseLockTimerHandle)));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Reset accumulated player input through: %.2f"), GetWorld()->GetTimerManager().GetTimerRemaining(ResetAccumulatedPlayerInputTimerHandle)));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Accumulated player input(for bResetTargetAfterPlayerInput): %s"), AccumulatedPlayerInput.IsSet() ? *AccumulatedPlayerInput->ToString() : *FRotator::ZeroRotator.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Distance to target actor: %.2f"), FMath::Sqrt(GetDistanceSquareToActor(TargetActor.Get()))));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Target actor: %s"), *TargetActor->GetName()));

		auto& lockOnTargetSettings = GetLockOnTargetSettings();

		if (lockOnTargetSettings.bUseDesiredConeRotation)
		{
			const float coneDist = 400.f;
			const FColor coneColor = FColor::Orange;
			const float lineThickness = 3.f;

			FVector lineStart = GetOwningActor()->GetActorLocation();

			float rotationToTargetYaw = GetCamera().GetCameraLocationObject()->GetViewRotation().Yaw;

			const FVector centerLineEnd = lineStart + FRotator(0.f, rotationToTargetYaw, 0.f).Vector() * coneDist;
			::DrawDebugLine(GetWorld(), lineStart, centerLineEnd, coneColor, false, -1.f, 0, 1.5f);

			const FVector leftLineEnd = lineStart + FRotator(0.f, rotationToTargetYaw + lockOnTargetSettings.DeisredConeRotationYaw, 0.f).Vector() * coneDist;
			::DrawDebugLine(GetWorld(), lineStart, leftLineEnd, coneColor, false, -1.f, 0, lineThickness);

			const FVector rightLineEnd = lineStart + FRotator(0.f, rotationToTargetYaw - lockOnTargetSettings.DeisredConeRotationYaw, 0.f).Vector() * coneDist;
			::DrawDebugLine(GetWorld(), lineStart, rightLineEnd, coneColor, false, -1.f, 0, lineThickness);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("Target actor is null"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("----- Camera Lock On Target Start Debug ---"));
}
