// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraBaseObject.h"
#include "ATPCOffsetValue.h"
#include "ATPCTypes.h"
#include "Engine/HitResult.h"
#include "EngineDefines.h"
#include "GameplayTagContainer.h"
#include "VisualLogger/VisualLoggerDebugSnapshotInterface.h"

#include "ATPCCameraLocationObject.generated.h"

enum ERelativeTransformSpace : int;

struct ADVANCEDTHIRDPERSONCAMERA_API FATPCRuntimeCameraOffsetRotationSettings
{
public:
	float LastChangeCameraRotationTime = 0.f;
	bool bPendingRotationOffset = false;
};

struct ADVANCEDTHIRDPERSONCAMERA_API FATPCRuntimeCameraToActorRotationSettings
{
public:
	FATPCInterploationSpeed RotationInterpolation = 0.f;
	float LastChangeCameraRotationTime = 0.f;
	bool bPendingRotationOffset = false;
};

UCLASS(classGroup = "ATPC")
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraLocationObject : public UATPCCameraBaseObject
    , public IVisualLoggerDebugSnapshotInterface
{
	GENERATED_BODY()
public:
	struct FCameraDistanceData
	{
	public:
		float TargetDistance = 0.f;
		float CurrentDistance = 0.f;
	};

	struct FDebugData
	{
		FHitResult TraceHitResult;
	};

public:
	UATPCCameraLocationObject();

	//~ Begin UATPCCameraBaseObject Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void Validate(bool bWithInterpolation) override;
	virtual void OnExitCameraMode() override;
	virtual void OnEnterCameraMode(bool bWithInterpolation) override;
	//~ End UATPCCameraBaseObject Interface

	virtual void UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime);
	virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace) const;

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	virtual void SetViewRotation(FRotator Rotation);
	/** Get view rotation from pawn */
	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual FRotator GetViewRotation() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual FRotator GetDesiredRotation() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual FRotator GetTargetRotation() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	FVector GetCameraLocation() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	FRotator GetCameraRotation() const;

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void SetCameraDistance(float NewDist, bool bInterpolate);
	UFUNCTION(BlueprintPure, Category = "ATPC")
	float GetCameraTargetDistance() const;

	/** Return camera distance without target, socket offsets and other modifiers*/
	UFUNCTION(BlueprintPure, Category = "ATPC")
	float GetCameraDistance() const;

	/** Return real distance between camera and character. With socket and target offsets and etc. */
	UFUNCTION(BlueprintPure, Category = "ATPC")
	float GetRealCameraDistance() const;

	//~ Begin Socket Offset Section
	UFUNCTION(BlueprintPure, Category = "ATPC")
	FVector GetSocketOffset() const;

	// Return all socket offsets(from cameraMode, customSocketOffset, curveSocketOffset, floorOffset)
	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual FVector GetAllSocketOffsets() const;
	//~ End Socket Offset Section

	//~ Begin Target Offset Section
	UFUNCTION(BlueprintPure, Category = "ATPC")
	FVector GetTargetOffset() const;
	//~ End Target Offset Section

	//~ Begin Override Rotation Section
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void SetOverrideCameraRotation(const FRotator& NewOverrideRotation, bool bClampByCameraModeRotationLimits = false);
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void ResetOverrideCameraRotation();
	UFUNCTION(BlueprintPure, Category = "ATPC")
	bool IsOverrideCameraRotation() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	const FRotator& GetOverrideCameraRotation() const;
	//~ End Override Rotation Section

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	virtual void AttachCameraToComponent(USceneComponent* ParentComponent, FVector RelativeLocation, FName SocketName, bool bWithInterp, float InterpSpeed);

	//Return offset settings with override/roof offset/default
	FATPCRotationOffsetSettings& GetCurrentRotationOffsetSettings();
	const FATPCRotationOffsetSettings& GetCurrentRotationOffsetSettings() const;

	virtual void ProcessRoofCollisionCheck();

	FRotator GetLastTickTargetRotationDelta() const;

	void ClampCameraRotation(FRotator& Rotation);

#if ENABLE_VISUAL_LOG
	virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;
#endif // ENABLE_VISUAL_LOG

public:
	FVector FollowTerrainSocketOffset = FVector::ZeroVector;
	float FollowTerrainRotationPitchOffset = 0.f;

protected:
	virtual FVector GetAllOldSocketOffsets() const;

	void InternalSetCurrentCameraDistance(float NewDist);

	virtual void ProcessLocationLag(FVector& DesiredLoc, const FVector& ArmOrigin, float DeltaSeconds);
	virtual void ProcessRotationLag(FRotator& DesiredRotation, float DeltaSeconds);

	virtual FVector BlendLocations(const FVector& DesiredArmLocation, const FVector& ArmOrigin, bool bHitSomething, const FVector& TraceHitLocation, float DeltaTime);

	float GetCameraDistanceModifiers() const;
	float GetTotalCameraDistance() const;

	virtual void UpdateTargetOffsetTarget();
	virtual void UpdateSocketOffsetTarget();

	virtual void UpdateOffsetCameraRotationTime(float DeltaSeconds);
	virtual void UpdateOffsetCameraRotation(bool bWithInterp, float DeltaSeconds);

	virtual void UpdateViewRotationToActorRotationTime(float DeltaSeconds);
	virtual void UpdateViewRotationToActorRotation(bool bWithInterp, float DeltaSeconds);

	virtual void FindRoofCollision(FHitResult& EyesHit, FHitResult& ActorFirstRoofHit, FHitResult& ActorSecondRoofHit);

	virtual void ValidateCameraView(bool bWithInterpolation, float DeltaTime);

	/*
	 * @return true if final interpolated value == @Value 
	 */
	bool ValidateRotationValue(float CompareValue, float& Value, bool bLessCompare, float DeltaTime, bool bInterpolate, FATPCInterploationSpeed& InterpSpeed);

	virtual void ShowDebug();
	void AddHitResultToDebug(const FHitResult& HitResult);

protected:
	TMap<FGameplayTag, TOptional<float>> CachedCameraModesDistance;

	FVector AttachCameraRelativeLocation = FVector::ZeroVector;
	float AttachCameraInterpSpeed = 0.f;
	bool bAttachCameraWithInterp = false;

	FATPCVectorOffset SocketOffset;
	FATPCVectorOffset OldSocketOffset;

	FATPCVectorOffset TargetOffset;

	TOptional<FRotator> OverrideCameraRotation;

	FCameraDistanceData CameraDistance;
	float PitchCameraDistanceModifier;

	bool bEnableRoofCollisionCheckRotationOffset = false;
	FATPCRuntimeCameraOffsetRotationSettings RuntimeOffsetRotationSettings;

	FATPCRuntimeCameraToActorRotationSettings RuntimeCameraToActorRotationSettings;

	FVector LocationLagDelta = FVector::ZeroVector;
	float LastCameraLagSpeed = 0.f;

	FRotator PreviousDesiredRot = FRotator::ZeroRotator;
	FVector PreviousArmOrigin = FVector::ZeroVector;

	FVector PreviousResultLoc = FVector::ZeroVector;

	FVector UnfixedCameraPosition = FVector::ZeroVector;
	bool bIsCameraFixed = false;
	/* Did use movement collision test in last update location(function UpdateDesiredArmLocation)*/
	bool bIsCameraUsedMovementCollisionTest = false;

	float LastTimeUseMovementCollisionTest = 0.f;

	FVector RelativeSocketLocation = FVector::ZeroVector;
	FQuat RelativeSocketRotation = FQuat::Identity;

	FRotator LastTargetRotation = FRotator::ZeroRotator;
	FRotator LastTickTargetRotationDelta = FRotator::ZeroRotator;

	FDebugData DebugData;
};