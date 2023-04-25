// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraComponent.h"

#include "ATPCCameraFOVObject.h"
#include "ATPCCameraFadingObject.h"
#include "ATPCCameraFollowTerrainObject.h"
#include "ATPCCameraLocationObject.h"
#include "ATPCCameraLockOnTargetObject.h"
#include "ATPCCameraModeDataAsset.h"
#include "ATPCCameraModeScript.h"
#include "ATPCCameraShakesObject.h"
#include "ATPCCameraVolume.h"
#include "AdvancedThirdPersonCamera.h"
#include "Algo/AnyOf.h"
#include "Camera/PlayerCameraManager.h"
#include "CinematicCamera/Public/CineCameraComponent.h"
#include "Engine/DataTable.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

UATPCCameraComponent::UATPCCameraComponent()
{
	LocationObjectClass = UATPCCameraLocationObject::StaticClass();
	FOVObjectClass = UATPCCameraFOVObject::StaticClass();
	FadingObjectClass = UATPCCameraFadingObject::StaticClass();
	FollowTerrainObjectClass = UATPCCameraFollowTerrainObject::StaticClass();
	CameraShakesObjectClass = UATPCCameraShakesObject::StaticClass();
	LockOnTargetObjectClass = UATPCCameraLockOnTargetObject::StaticClass();

	if (HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
	{
		RegisterConsoleCommands();
	}

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;

	bAutoActivate = true;
	bTickInEditor = true;
}

void UATPCCameraComponent::OnRegister()
{
	Super::OnRegister();

	CreateCameraModesFromAssets();

	CreateAllCameraObjects();
}

void UATPCCameraComponent::BeginPlay()
{
	Super::BeginPlay();

#if !UE_BUILD_SHIPPING
	CheckCameraModesErros();
#endif //!UE_BUILD_SHIPPING

	SetInitialCameraMode();
}

void UATPCCameraComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	USceneComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto cameraManager = GetPlayerCameraManager();
	if(cameraManager == nullptr || cameraManager->GetViewTarget() != GetOwner())
	{
		return;
	}
	
	const auto& attachedChildrenComponents = GetAttachChildren();
	const bool bHasActiveCameraChild = Algo::AnyOf(attachedChildrenComponents, [](const USceneComponent* Component)
	{
		const auto cameraComponent = Cast<UCameraComponent>(Component);
		return cameraComponent != nullptr && cameraComponent->IsActive();
	});
	if(!bHasActiveCameraChild)
	{
		return;	
	}
	
	if (IsCineCameraActive())
	{
		if (!bHandledCineCamera)
		{
			bHandledCineCamera = true;

			for (auto& objPtr : CameraObjList)
			{
				objPtr->SwitchToCineCamera();
			}
		}
	}
	else
	{
		bHandledCineCamera = false;
	}

	auto cameraMode = GetCurrentCameraMode();

	for (auto& cameraModeScript : cameraMode->CameraModeScripts)
	{
		if (cameraModeScript != nullptr && cameraModeScript->IsEnableTick() && cameraModeScript->GetTickGroup() == EATPCCameraModeScriptTickGroup::PreCameraObjectTick)
		{
			cameraModeScript->Tick(DeltaTime);
		}
	}

	for (auto& objPtr : CameraObjList)
	{
		objPtr->Tick(DeltaTime);
	}

	for (auto& cameraModeScript : cameraMode->CameraModeScripts)
	{
		if (cameraModeScript != nullptr && cameraModeScript->IsEnableTick() && cameraModeScript->GetTickGroup() == EATPCCameraModeScriptTickGroup::PostCameraObjectTick)
		{
			cameraModeScript->Tick(DeltaTime);
		}
	}
}

void UATPCCameraComponent::ValidateComponents(bool bWithInterpolation)
{
	for (auto& cameraObj : CameraObjList)
	{
		cameraObj->Validate(bWithInterpolation);
	}
}

void UATPCCameraComponent::OnBeginOverlapCameraVolume(AATPCCameraVolume* CameraVolume)
{
	if (CameraVolume != nullptr)
	{
		SetCameraMode(CameraVolume->CameraModeTag, CameraVolume->bChangeCameraModeWithInterp);
	}
}

void UATPCCameraComponent::OnEndOverlapCameraVolume(AATPCCameraVolume* CameraVolume)
{
	AATPCCameraVolume* cameraVolume = FindOverlapCameraVolume();
	FGameplayTag newCameraModeTag = cameraVolume ? cameraVolume->CameraModeTag : DefaultCameraModeTag;

	SetCameraMode(newCameraModeTag, true);
}

void UATPCCameraComponent::SetCameraMode(FGameplayTag CameraModeTag, bool bWithInterpolation, bool bForceSet /*= false*/)
{
	if (!bForceSet && !CanSetCameraMode(CameraModeTag))
	{
		return;
	}

	if (auto cameraModePtr = SortedCameraModes.Find(CameraModeTag))
	{
		InternalSetCameraMode(*cameraModePtr, CameraModeTag, bWithInterpolation);
	}
	else
	{
		PutLog(FString::Printf(TEXT("Try set %s camera mode, but this mode not found!"), *CameraModeTag.ToString()));
	}
}

bool UATPCCameraComponent::CanSetCameraMode_Implementation(FGameplayTag CameraModeTag) const
{
	return true;
}

FGameplayTag UATPCCameraComponent::GetDesiredCameraModeTag_Implementation() const
{
	return CurrentCameraModeTag.IsValid() ? CurrentCameraModeTag : DefaultCameraModeTag;
}

FGameplayTag UATPCCameraComponent::GetInitialCameraModeTag_Implementation() const
{
	FGameplayTag cameraVolumeTag = GetCameraModeTagFromOverlapCameraVolume();
	return cameraVolumeTag.IsValid() ? cameraVolumeTag : DefaultCameraModeTag;
}

FGameplayTag UATPCCameraComponent::GetCameraModeTagFromOverlapCameraVolume() const
{
	AATPCCameraVolume* cameraVolume = FindOverlapCameraVolume();

	return cameraVolume != nullptr && cameraVolume->CameraModeTag.IsValid() ? cameraVolume->CameraModeTag : FGameplayTag();
}

FGameplayTag UATPCCameraComponent::GetCurrentCameraModeTag() const
{
	return CurrentCameraModeTag;
}

const UATPCCameraModeDataAsset* UATPCCameraComponent::GetCurrentCameraMode() const
{
	return const_cast<UATPCCameraComponent*>(this)->GetCurrentCameraMode();
}

UATPCCameraModeDataAsset* UATPCCameraComponent::GetCurrentCameraMode()
{
	UATPCCameraModeDataAsset* retValue = nullptr;

	if (CustomCameraMode != nullptr)
	{
		retValue = CustomCameraMode;
	}
	else if (auto cameraModePtr = SortedCameraModes.Find(CurrentCameraModeTag))
	{
		retValue = *cameraModePtr;
	}
	else
	{
		if (EmptyCameraMode == nullptr)
		{
			EmptyCameraMode = NewObject<UATPCCameraModeDataAsset>();
		}
		retValue = EmptyCameraMode;
	}

	return retValue;
}

void UATPCCameraComponent::SetCustomCameraMode(UATPCCameraModeDataAsset* CameraMode, bool bWithInterpolation)
{
	InternalSetCameraMode(CameraMode, {}, bWithInterpolation);
}

void UATPCCameraComponent::ResetCustomCameraMode(bool bWithInterpolation)
{
	if (IsSetCustomCameraMode())
	{
		CustomCameraMode = nullptr;
		InternalSetCameraMode(GetCurrentCameraMode(), CurrentCameraModeTag, bWithInterpolation);
	}
}

bool UATPCCameraComponent::IsSetCustomCameraMode() const
{
	return CustomCameraMode != nullptr;
}

void UATPCCameraComponent::AddCameraMode(UATPCCameraModeDataAsset* CameraMode)
{
	if (CameraMode == nullptr)
	{
		PutLog(FString::Printf(TEXT("Try AddCameraMode with null CameraMode!")));
	}
	else if (!CameraMode->CameraModeTag.IsValid())
	{
		PutLog(FString::Printf(TEXT("Try AddCameraMode with null CameraModeTag and CameraMode: %s!"), *GetNameSafe(CameraMode)));
	}
	else
	{
		auto instancedCameraMode = DuplicateObject(CameraMode, this);
		SortedCameraModes.Add(instancedCameraMode->CameraModeTag, instancedCameraMode);
	}
}

void UATPCCameraComponent::RemoveCameraMode(FGameplayTag CameraModeTag)
{
	SortedCameraModes.Remove(CameraModeTag);
}

bool UATPCCameraComponent::HasCameraMode(FGameplayTag CameraModeTag) const
{
	return SortedCameraModes.Contains(CameraModeTag);
}

UATPCCameraModeDataAsset* UATPCCameraComponent::GetCameraMode(FGameplayTag CameraModeTag) const
{
	return const_cast<UATPCCameraComponent*>(this)->GetCameraMode(CameraModeTag);
}

UATPCCameraModeDataAsset* UATPCCameraComponent::GetCameraMode(FGameplayTag CameraModeTag)
{
	auto cameraMode = SortedCameraModes.Find(CameraModeTag);
	return cameraMode != nullptr ? *cameraMode : nullptr;
}

void UATPCCameraComponent::ClearAllCameraModes()
{
	SortedCameraModes.Empty();
}

AATPCCameraVolume* UATPCCameraComponent::FindOverlapCameraVolume() const
{
	TSet<AActor*> cameraVolumes;
	GetOwner()->GetOverlappingActors(cameraVolumes, AATPCCameraVolume::StaticClass());
	return cameraVolumes.Num() > 0 ? Cast<AATPCCameraVolume>(*cameraVolumes.CreateConstIterator()) : nullptr;
}

FTransform UATPCCameraComponent::GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace /*= RTS_World*/) const
{
	if (LocationObject != nullptr)
	{
		return LocationObject->GetSocketTransform(InSocketName, TransformSpace);
	}
	else
	{
		return Super::GetSocketTransform(InSocketName, TransformSpace);
	}
}

void UATPCCameraComponent::ZoomIn()
{
	if (LocationObject != nullptr && GetCurrentCameraMode()->CameraModeSettings.bEnableLocationSettings)
	{
		LocationObject->SetCameraDistance(GetCameraDistance() - GetCurrentCameraMode()->CameraModeSettings.LocationSettings.ZoomDistance, true);
	}
}

void UATPCCameraComponent::ZoomOut()
{
	if (LocationObject != nullptr && GetCurrentCameraMode()->CameraModeSettings.bEnableLocationSettings)
	{
		LocationObject->SetCameraDistance(GetCameraDistance() + GetCurrentCameraMode()->CameraModeSettings.LocationSettings.ZoomDistance, true);
	}
}

void UATPCCameraComponent::SetCameraDistance(float NewDistance, bool bInterpolate)
{
	if (LocationObject != nullptr)
	{
		LocationObject->SetCameraDistance(NewDistance, bInterpolate);
	}
}

float UATPCCameraComponent::GetCameraDistance() const
{
	return LocationObject != nullptr ? LocationObject->GetCameraDistance() : 0.f;
}

FVector UATPCCameraComponent::GetCameraLocation() const
{
	return GetSocketTransform(NAME_None).GetLocation();
}

FRotator UATPCCameraComponent::GetCameraRotation() const
{
	return GetSocketTransform(NAME_None).Rotator();
}

bool UATPCCameraComponent::IsCineCameraActive() const
{
	auto viewTarget = GetOwner();
	if (auto playerController = GetPlayerController())
	{
		viewTarget = playerController->GetViewTarget();
	}

	TArray<UCineCameraComponent*> cineCameraComponents;
	viewTarget->GetComponents(cineCameraComponents);

	return cineCameraComponents.ContainsByPredicate([](UCineCameraComponent* CineCamera) {
		return CineCamera->IsActive();
	});
}

bool UATPCCameraComponent::IsSettingInitialCameraMode() const
{
	return bIsSettingInitialCameraMode;
}

APawn* UATPCCameraComponent::GetOwningPawn() const
{
	return Cast<APawn>(GetOwner());
}

APlayerController* UATPCCameraComponent::GetPlayerController() const
{
	APawn* owningPawn = GetOwningPawn();
	return owningPawn != nullptr ? Cast<APlayerController>(owningPawn->Controller) : nullptr;
}

APlayerCameraManager* UATPCCameraComponent::GetPlayerCameraManager() const
{
	APlayerController* playerController = GetPlayerController();
	return playerController != nullptr ? playerController->PlayerCameraManager : nullptr;
}

void UATPCCameraComponent::CreateCameraModesFromAssets()
{
	SortedCameraModes.Empty();
	for (auto dataAsset : CameraModesAssets)
	{
		if (dataAsset != nullptr)
		{
			AddCameraMode(dataAsset);
		}
	}
}

void UATPCCameraComponent::SetInitialCameraMode()
{
	if (!HasCameraMode(DefaultCameraModeTag))
	{
		PutLog(FString::Printf(TEXT("Default camera mode [%s] not found!"), *DefaultCameraModeTag.ToString()));
	}

	bIsSettingInitialCameraMode = true;
	SetCameraMode(GetInitialCameraModeTag(), false);
	bIsSettingInitialCameraMode = false;
}

void UATPCCameraComponent::InternalSetCameraMode(UATPCCameraModeDataAsset* NewCameraMode, TOptional<FGameplayTag> CameraModeTag, bool bWithInterpolation)
{
	if (!CameraModeTag.IsSet() || IsSetCustomCameraMode() || CurrentCameraModeTag != CameraModeTag.GetValue())
	{
		NotifyExitCameraMode();
		if (CameraModeTag.IsSet())
		{
			CustomCameraMode = nullptr;
			CurrentCameraModeTag = CameraModeTag.GetValue();
		}
		else
		{
			CustomCameraMode = NewCameraMode;
		}
		NotifyEnterCameraMode(bWithInterpolation);
		OnCameraModeChangedDelegate.Broadcast();
	}
}

void UATPCCameraComponent::NotifyExitCameraMode()
{
	for (auto& cameraObj : CameraObjList)
	{
		cameraObj->OnExitCameraMode();
	}

	for (auto& cameraModeScript : GetCurrentCameraMode()->CameraModeScripts)
	{
		if (cameraModeScript != nullptr)
		{
			cameraModeScript->OnExitCameraMode();
		}
	}
}

void UATPCCameraComponent::NotifyEnterCameraMode(bool bWithInterpolation)
{
	for (auto& cameraObj : CameraObjList)
	{
		cameraObj->OnEnterCameraMode(bWithInterpolation);
	}

	for (auto& cameraModeScript : GetCurrentCameraMode()->CameraModeScripts)
	{
		if (cameraModeScript != nullptr)
		{
			cameraModeScript->OnEnterCameraMode(this);
		}
	}
}

void UATPCCameraComponent::CreateAllCameraObjects()
{
	for (auto& cameraObj : CameraObjList)
	{
		if (cameraObj != nullptr)
		{
			cameraObj->ConditionalBeginDestroy();
		}
	}
	CameraObjList.Empty();

	LocationObject = CreateCameraObject(LocationObjectClass);
	FOVObject = CreateCameraObject(FOVObjectClass);
	FadingObject = CreateCameraObject(FadingObjectClass);
	FollowTerrainObject = CreateCameraObject(FollowTerrainObjectClass);
	CameraShakesObject = CreateCameraObject(CameraShakesObjectClass);
	LockOnTargetObject = CreateCameraObject(LockOnTargetObjectClass);

	for (auto objPtr : CameraObjList)
	{
		objPtr->Validate(false);
	}
}

void UATPCCameraComponent::CheckCameraModesErros()
{
	const float messageTime = 10.f;

	for (auto& cameraModeDataAsset : CameraModesAssets)
	{
		if (cameraModeDataAsset == nullptr)
		{
			continue;
		}

		if (!cameraModeDataAsset->CameraModeTag.IsValid())
		{
			PutLog(FString::Printf(TEXT("Discovered camera mode with invalid tag: %s"), *cameraModeDataAsset->GetName()), messageTime);
		}
		else
		{
			auto sameCameraMode = CameraModesAssets.FindByPredicate([cameraModeDataAsset](const auto& OtherCameraModeDataAsset) {
				return OtherCameraModeDataAsset != nullptr && OtherCameraModeDataAsset != cameraModeDataAsset && OtherCameraModeDataAsset->CameraModeTag == cameraModeDataAsset->CameraModeTag;
			});
			if (sameCameraMode != nullptr)
			{
				PutLog(FString::Printf(TEXT("Discovered camera modes with same tags: %s and %s. Tag: %s"), *cameraModeDataAsset->GetName(), *(*sameCameraMode)->GetName(), *cameraModeDataAsset->CameraModeTag.ToString()), messageTime);
			}
		}
	}
}

void UATPCCameraComponent::PutLog(const FString& Message, float MessageTime /*= 5.f*/)
{
	if (DebugRules.bPrintErrorsToScreen)
	{
		GEngine->AddOnScreenDebugMessage(-1, MessageTime, FColor::Red, Message);
	}
	UE_LOG(LogATPC, Warning, TEXT("%s"), *Message);
}

UATPCCameraBaseObject* UATPCCameraComponent::CreateCameraObjectImpl(TSubclassOf<UATPCCameraBaseObject> ObjectClass)
{
	UATPCCameraBaseObject* newObject = nullptr;
	if (ObjectClass != nullptr)
	{
		newObject = NewObject<UATPCCameraBaseObject>(this, ObjectClass);
		newObject->SetCamera(this);
		CameraObjList.Add(newObject);
	}

	return newObject;
}
