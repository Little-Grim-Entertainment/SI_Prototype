// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCFunctionLibrary.h"

#include "ATPCCameraComponent.h"
#include "AdvancedThirdPersonCamera.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"

void UATPCFunctionLibrary::InterpolationSpeed_InterpolateSpeed(FATPCInterploationSpeed& InterpSpeed, float DeltaTime)
{
	InterpSpeed.InterpolateSpeed(DeltaTime);
}

void UATPCFunctionLibrary::InterpolationSpeed_ResetSpeed(FATPCInterploationSpeed& InterpSpeed)
{
	InterpSpeed.ResetCurrentSpeed();
}

float UATPCFunctionLibrary::InterpolationSpeed_GetCurrentInterpolationSpeed(const FATPCInterploationSpeed& InterpSpeed)
{
	return InterpSpeed.GetCurrentInterpolationSpeed();
}

FVector UATPCFunctionLibrary::InterpVector(const FVector& Current, const FVector& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget /*= true*/)
{
	return InterpImpl(
	    Current, Target, DeltaTime, InterpSpeed, bResetSpeedIfResultEqualToTarget, [](auto& LocalCurrent, auto& LocalTarget, auto LocalDeltaTime, auto LocalInterpSpeed) { return FMath::VInterpTo(LocalCurrent, LocalTarget, LocalDeltaTime, LocalInterpSpeed); }, [](auto& LocalCurrent, auto& LocalTarget, auto LocalDeltaTime, auto LocalInterpSpeed) { return FMath::VInterpConstantTo(LocalCurrent, LocalTarget, LocalDeltaTime, LocalInterpSpeed); }, [&](const FVector& LocalResult, const FVector& LocalTarget) { return LocalResult.Equals(LocalTarget, InterpSpeed.ResetInterpSpeedTolerance); });
}

FRotator UATPCFunctionLibrary::InterpRotator(const FRotator& Current, const FRotator& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget /*= true*/)
{
	return InterpImpl(
	    Current, Target, DeltaTime, InterpSpeed, bResetSpeedIfResultEqualToTarget, [](auto& LocalCurrent, auto& LocalTarget, auto LocalDeltaTime, auto LocalInterpSpeed) { return FMath::QInterpTo(LocalCurrent.Quaternion(), LocalTarget.Quaternion(), LocalDeltaTime, LocalInterpSpeed).Rotator(); }, [](auto& LocalCurrent, auto& LocalTarget, auto LocalDeltaTime, auto LocalInterpSpeed) { return FMath::QInterpConstantTo(LocalCurrent.Quaternion(), LocalTarget.Quaternion(), LocalDeltaTime, LocalInterpSpeed).Rotator(); }, [&](const FRotator& LocalResult, const FRotator& LocalTarget) { return LocalResult.Equals(LocalTarget, InterpSpeed.ResetInterpSpeedTolerance); });
}

float UATPCFunctionLibrary::InterpFloat(const float& Current, const float& Target, float DeltaTime, FATPCInterploationSpeed& InterpSpeed, bool bResetSpeedIfResultEqualToTarget /*= true*/)
{
	return InterpImpl(
	    Current, Target, DeltaTime, InterpSpeed, bResetSpeedIfResultEqualToTarget, [](auto& LocalCurrent, auto& LocalTarget, auto LocalDeltaTime, auto LocalInterpSpeed) { return FMath::FInterpTo(LocalCurrent, LocalTarget, LocalDeltaTime, LocalInterpSpeed); }, [](auto& LocalCurrent, auto& LocalTarget, auto LocalDeltaTime, auto LocalInterpSpeed) { return FMath::FInterpConstantTo(LocalCurrent, LocalTarget, LocalDeltaTime, LocalInterpSpeed); }, [&](float LocalResult, float LocalTarget) { return FMath::IsNearlyEqual(LocalResult, LocalTarget, InterpSpeed.ResetInterpSpeedTolerance); });
}

bool UATPCFunctionLibrary::ReplaceSpringArmToATPCComponent(AActor* Actor)
{
	bool bSuccessReplace = false;

	if (Actor != nullptr)
	{
		if (auto springArm = Actor->FindComponentByClass<USpringArmComponent>())
		{
			if (auto atpcCamera = Actor->FindComponentByClass<UATPCCameraComponent>())
			{
				auto attachChildren = springArm->GetAttachChildren();
				for (auto child : attachChildren)
				{
					child->AttachToComponent(atpcCamera, FAttachmentTransformRules::KeepRelativeTransform);
				}

				bSuccessReplace = true;
			}
			else
			{
				UE_LOG(LogATPC, Warning, TEXT("Try ReplaceSpringArmToATPCComponent but atpc component not found for actor: %s"), *Actor->GetName());
			}
		}
		else
		{
			UE_LOG(LogATPC, Warning, TEXT("Try ReplaceSpringArmToATPCComponent but spring arm not found for actor: %s"), *Actor->GetName());
		}
	}
	else
	{
		UE_LOG(LogATPC, Warning, TEXT("Try ReplaceSpringArmToATPCComponent for null actor!"));
	}

	return bSuccessReplace;
}
