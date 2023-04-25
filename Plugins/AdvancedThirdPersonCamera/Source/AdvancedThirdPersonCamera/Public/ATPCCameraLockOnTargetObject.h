// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraBaseObject.h"
#include "ATPCTypes.h"

#include "ATPCCameraLockOnTargetObject.generated.h"

class AActor;

UENUM(BlueprintType)
enum class EATPCChangeTargetReason : uint8
{
	SetNew,
	LostByExitCameraMode,
	LostByDistance,
	LostByVisible,
	LostByPlayerInput
};

UCLASS(classGroup = "ATPC")
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraLockOnTargetObject : public UATPCCameraBaseObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTargetChangeDelegate, AActor*, NewTarget, EATPCChangeTargetReason, ChangeTargetReason);

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnEnterCameraMode(bool bWithInterpolation) override;
	virtual void OnExitCameraMode() override;

	virtual float GetDistanceSquareToActor(AActor* Actor) const;

	FVector GetTargetLocation(AActor* Actor) const;

	virtual bool IsValidDistanceToActor(AActor* Actor) const;
	virtual bool IsActorVisible(AActor* Actor) const;
	FRotator GetRotationToTarget(AActor* Actor) const;
	virtual void RotateCameraToActor(AActor* Actor, float DeltaSeconds);

	/** Check Actor visibility and distance (see bUseMaxLockDistance and bUseCheckTargetVisibility from a camera mode lock on target settings)*/
	virtual bool CanSetActorAsTarget(AActor* Actor) const;

	/** Set and lock a target for aiming*/
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	virtual bool SetTargetActor(AActor* NewTargetActor);
	UFUNCTION(BlueprintPure, Category = "ATPC")
	AActor* GetTargetActor() const;

	const FATPCLockOnTargetSettings& GetLockOnTargetSettings() const;
	FATPCLockOnTargetSettings& GetLockOnTargetSettings();

public:
	UPROPERTY(BlueprintAssignable)
	FOnTargetChangeDelegate OnTargetChangeDelegate;

protected:
	virtual bool InternalSetTargetActor(AActor* NewTargetActor, EATPCChangeTargetReason ChangeTargetReason);

	void PauseLock();
	void ResumeLock();

	void ResetAccumulatedPlayerInput();

	virtual void ShowTargetActor();
	virtual void PrintDebug();

protected:
	TWeakObjectPtr<AActor> TargetActor;

	bool bPauseLock = false;

	TOptional<FRotator> AccumulatedPlayerInput;

	UPROPERTY()
	class AATPCArrowDebugActor* TargetDebugActor;

	FTimerHandle ResetAccumulatedPlayerInputTimerHandle;
	FTimerHandle PauseLockTimerHandle;
	FTimerHandle ClearTargetTimerHandle;
};