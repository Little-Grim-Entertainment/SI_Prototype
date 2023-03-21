// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraFadingObject.h"

#include "ATPCCameraComponent.h"
#include "ATPCCameraModeDataAsset.h"
#include "Algo/ForEach.h"
#include "Components/MeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"

FATPCFadingActorInfo::FATPCFadingActorInfo(AActor* InActor, bool bInFadeOut, float InFadeOutTime, float InFadeValue /* = 1.f*/)
    : Actor(InActor)
    , bFadeOut(bInFadeOut)
    , FadeOutTime(InFadeOutTime)
    , FadeValue(InFadeValue)
{
}

bool FATPCFadingActorInfo::operator==(const FATPCFadingActorInfo& other) const
{
	return Actor == other.Actor;
}

void UATPCCameraFadingObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;

	if (cameraMode.bEnableFadeSettings)
	{
		if (cameraMode.FadeSettings.bFadeSelfIfCollision)
		{
			SelfFade();
		}

		if (cameraMode.FadeSettings.MaterialFadeParamNames.Num() != 0)
		{
			TArray<AActor*> newFadingActors = FilterCollidedActors(FindCollidedActors());
			UpdateFadingActorsList(newFadingActors);
			ApplyFade(DeltaSeconds);
		}
	}

	//If after disable fading left proccessed actors
	else if (!cameraMode.bEnableFadeSettings)
	{
		UpdateFadingActorsList({});
		ApplyFade(DeltaSeconds);
	}
}

void UATPCCameraFadingObject::Validate(bool bWithInterpolation)
{
	Super::Validate(bWithInterpolation);
}

void UATPCCameraFadingObject::OnEnterCameraMode(bool bWithInterpolation)
{
	Super::OnEnterCameraMode(bWithInterpolation);

	auto& cameraMode = GetCamera().GetCurrentCameraMode()->CameraModeSettings;
	if (!cameraMode.bEnableFadeSettings)
	{
		for (auto& fadingActor : FadingActors)
		{
			fadingActor.bFadeOut = false;
			if (!bWithInterpolation)
			{
				fadingActor.FadeValue = cameraMode.FadeSettings.MaterialFadeMaxValue;
			}
		}
	}

	if (!cameraMode.FadeSettings.bSelfFadeAttachedActors)
	{
		TArray<AActor*> attachedToOwnerActors;
		GetOwningActor()->GetAttachedActors(attachedToOwnerActors);
		for (auto actor : attachedToOwnerActors)
		{
			RemoveManualFadeActor(actor);
		}
	}

	if (!bWithInterpolation)
	{
		ApplyFade(0.f);
		UpdateFadingActorsList({});
	}
}

void UATPCCameraFadingObject::AddIgnoredActor(AActor* Actor)
{
	if (Actor == nullptr)
	{
		return;
	}

	IgnoredActors.Add(Actor);

	FATPCFadingActorInfo* fadingActorInfo = FadingActors.FindByPredicate([Actor](const FATPCFadingActorInfo& FadingActorInfo) {
		return FadingActorInfo.Actor.Get() == Actor;
	});
	if (fadingActorInfo != nullptr)
	{
		fadingActorInfo->bFadeOut = false;
	}
}

void UATPCCameraFadingObject::RemoveIgnoredActor(AActor* Actor)
{
	IgnoredActors.Remove(Actor);
}

void UATPCCameraFadingObject::ClearIgnoredActors()
{
	IgnoredActors.Empty();
}

void UATPCCameraFadingObject::AddManualFadeActor(AActor* Actor, bool bWithCustomTime /* = false*/, float CustomFadeOutTime /* = 0.f*/)
{
	if (Actor == nullptr)
	{
		return;
	}

	ManualFadingActors.Add(Actor);

	float fadeOutTime = bWithCustomTime ? CustomFadeOutTime : GetCamera().GetCurrentCameraMode()->CameraModeSettings.FadeSettings.FadeOutTime;

	FATPCFadingActorInfo* fadingActorInfo = FadingActors.FindByPredicate([Actor](const FATPCFadingActorInfo& FadingActorInfo) {
		return FadingActorInfo.Actor.Get() == Actor;
	});

	if (fadingActorInfo != nullptr)
	{
		fadingActorInfo->FadeOutTime = fadeOutTime;
	}
	else
	{
		FadingActors.Add(FATPCFadingActorInfo(Actor, true, fadeOutTime));
	}
}

void UATPCCameraFadingObject::RemoveManualFadeActor(AActor* Actor)
{
	ManualFadingActors.Remove(Actor);
}

void UATPCCameraFadingObject::ClearManualFadeActors()
{
	ManualFadingActors.Empty();
}

void UATPCCameraFadingObject::SelfFade()
{
	auto& camera = GetCamera();
	auto& fadeSettings = camera.GetCurrentCameraMode()->CameraModeSettings.FadeSettings;

	TArray<FOverlapResult> overlapResults;

	FCollisionShape collisionShape;
	collisionShape.SetSphere(fadeSettings.SelfFadeCheckRadius);

	GetWorld()->OverlapMultiByChannel(overlapResults, camera.GetCameraLocation(), FQuat::Identity, fadeSettings.FadeChannel, collisionShape);

	AActor* owningActor = GetOwningActor();

	auto owningActorOverlapRes = overlapResults.FindByPredicate([owningActor](auto& OverlapRes) {
		return OverlapRes.GetActor() == owningActor;
	});

	TArray<AActor*> attachedToOwnerActors;
	GetOwningActor()->GetAttachedActors(attachedToOwnerActors);

	if (owningActorOverlapRes != nullptr)
	{
		AddManualFadeActor(owningActor, fadeSettings.bUseCustomFadeOutTimeForSelfFade, fadeSettings.SelfFadeCustomFadeOutTime);

		if (fadeSettings.bSelfFadeAttachedActors)
		{
			for (auto actor : attachedToOwnerActors)
			{
				AddManualFadeActor(actor, fadeSettings.bUseCustomFadeOutTimeForSelfFade, fadeSettings.SelfFadeCustomFadeOutTime);
			}
		}
	}
	else
	{
		RemoveManualFadeActor(owningActor);

		if (fadeSettings.bSelfFadeAttachedActors)
		{
			for (auto actor : attachedToOwnerActors)
			{
				RemoveManualFadeActor(actor);
			}
		}
	}
}

TArray<FHitResult> UATPCCameraFadingObject::FindCollidedActors() const
{
	auto& camera = GetCamera();

	ETraceTypeQuery traceType = UCollisionProfile::Get()->ConvertToTraceType(GetCamera().GetCurrentCameraMode()->CameraModeSettings.FadeSettings.FadeChannel);

	FVector traceStart = GetOwningActor()->GetActorLocation();
	FVector traceEnd = camera.GetCameraLocation();

	float actorCollisionHalfHeight = GetOwningActor()->GetSimpleCollisionHalfHeight();
	float actorCollisionRadius = GetOwningActor()->GetSimpleCollisionRadius();
	FVector boxHalfSize(0.f, actorCollisionRadius * 0.7f, actorCollisionHalfHeight * 0.7f * (1 - FMath::Abs(camera.GetCameraRotation().Pitch) / 90.f));

	TArray<AActor*> ignoreActors = { GetOwningActor() };

	EDrawDebugTrace::Type drawDebugTrace = camera.DebugRules.bEnableDrawFadeShapeDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;

	TArray<FHitResult> hitResults;
	UKismetSystemLibrary::BoxTraceMulti(GetOwningActor(), traceStart, traceEnd, boxHalfSize, FRotationMatrix::MakeFromX(camera.GetCameraLocation() - GetOwningActor()->GetActorLocation()).Rotator(), traceType, false, ignoreActors, drawDebugTrace, hitResults, true);

	return hitResults;
}

TArray<AActor*> UATPCCameraFadingObject::FilterCollidedActors(const TArray<FHitResult>& HitResults)
{
	TArray<AActor*> collidedActors;
	for (auto& hitResult : HitResults)
	{
		if (!hitResult.bBlockingHit && hitResult.GetActor() != nullptr)
		{
			collidedActors.Add(hitResult.GetActor());
		}
	}

	return collidedActors;
}

void UATPCCameraFadingObject::UpdateFadingActorsList(TArray<AActor*> RelevantActors)
{
	const FATPCFadeSettings& fadeSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.FadeSettings;

	FadingActors.RemoveAll([&fadeSettings, this](const FATPCFadingActorInfo& elem) {
		return !elem.Actor.IsValid() || (!elem.bFadeOut && elem.FadeValue + KINDA_SMALL_NUMBER >= fadeSettings.MaterialFadeMaxValue);
	});

	RelevantActors.RemoveAll([this](AActor* actor) {
		return IgnoredActors.Contains(actor);
	});

	for (auto& actor : ManualFadingActors)
	{
		RelevantActors.AddUnique(actor.Get());
	}

	//Find already fading actors
	for (auto& fadingActor : FadingActors)
	{
		AActor** findedActor = RelevantActors.FindByPredicate([fadingActor](const AActor* actor) {
			return fadingActor.Actor.Get() == actor;
		});

		if (findedActor != nullptr)
		{
			fadingActor.bFadeOut = true;
		}
		else
		{
			fadingActor.bFadeOut = false;
		}
	}

	//Add new actors
	for (auto& actor : RelevantActors)
	{
		FadingActors.AddUnique(FATPCFadingActorInfo(actor, true, fadeSettings.FadeOutTime));
	}
}

void UATPCCameraFadingObject::ApplyFade(float DeltaSeconds)
{
	const FATPCFadeSettings& fadeSettings = GetCamera().GetCurrentCameraMode()->CameraModeSettings.FadeSettings;
	for (auto& fadedActor : FadingActors)
	{
		if (fadedActor.Actor.IsValid())
		{
			float fadeSpeed = fadedActor.bFadeOut ? -1.f * fadedActor.FadeOutTime : fadeSettings.FadeInTime;
			fadedActor.FadeValue += 1.f / fadeSpeed * DeltaSeconds;

			fadedActor.FadeValue = FMath::Clamp(fadedActor.FadeValue, fadeSettings.MaterialFadeMinValue, fadeSettings.MaterialFadeMaxValue);

			TArray<UMeshComponent*> meshes;
			fadedActor.Actor->GetComponents(meshes);

			for (auto& mesh : meshes)
			{
				const TArray<UMaterialInterface*> materialInterfaces = mesh->GetMaterials();
				for (auto& materialInterface : materialInterfaces)
				{
					if(materialInterface != nullptr)
					{
						TArray<FMaterialParameterInfo> materialScalarParameters;
						TArray<FGuid> materialScalarParametersIds;
						materialInterface->GetAllScalarParameterInfo(materialScalarParameters, materialScalarParametersIds);

						for (auto& materialParameterInfo : materialScalarParameters)
						{
							if (fadeSettings.MaterialFadeParamNames.Contains(materialParameterInfo.Name))
							{
								if (const auto widgetComponent = Cast<UWidgetComponent>(mesh))
								{
									if (const auto widgetMatInstance = widgetComponent->GetMaterialInstance())
									{
										widgetMatInstance->SetScalarParameterValue(materialParameterInfo.Name, fadedActor.FadeValue);
									}
								}
								else
								{
									mesh->SetScalarParameterValueOnMaterials(materialParameterInfo.Name, fadedActor.FadeValue);
								}
							}
						}
					}
				}
			}
		}
	}
}
