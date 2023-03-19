// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCInterpolationSpeed.h"
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"

#include "ATPCTypes.generated.h"

class UCurveVector;
class UCurveFloat;
class UCameraShakeBase;

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCCameraLocationLagSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bEnableCameraLagForXY = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bEnableCameraLagForZ = true;

	/**
	 * If is true, controls how quickly camera reaches target position. Low values are slower (more lag), high values are faster (less lag), while zero is instant (no lag).
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	float CameraLagSpeed = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float CameraLagMaxDistance = 30.f;

	/**
	 * If true and camera location lag is enabled, draws markers at the camera target (in green) and the lagged position (in yellow).
	 * A line is drawn between the two locations, in green normally but in red if the distance to the lag target has been clamped (by CameraLagMaxDistance).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bDrawDebugLagMarkers = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bUseCameraLagSubstepping = false;
	/** Max time step used when sub-stepping camera lag. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Editcondition = "bUseCameraLagSubstepping", ClampMin = "0.005", ClampMax = "0.5", UIMin = "0.005", UIMax = "0.5"))
	float CameraLagMaxTimeStep = 1 / 60.f;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCCameraRotationLagSettings
{
	GENERATED_BODY()
public:
	/** If is true, controls how quickly camera reaches target position. Low values are slower (more lag), high values are faster (less lag), while zero is instant (no lag). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	float CameraLagSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bUseCameraLagSubstepping = false;
	/** Max time step used when sub-stepping camera lag. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (editcondition = "bUseCameraLagSubstepping", ClampMin = "0.005", ClampMax = "0.5", UIMin = "0.005", UIMax = "0.5"))
	float CameraLagMaxTimeStep = 1 / 60.f;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCLocationSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableCameraLocationLag = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Editcondition = "bEnableCameraLocationLag"))
	FATPCCameraLocationLagSettings CameraLocationLagSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableCameraRotationLag = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Editcondition = "bEnableCameraRotationLag"))
	FATPCCameraRotationLagSettings CameraRotationLagSettings;

	/** If true, do a collision test using ProbeChannel and ProbeSize to prevent camera clipping into level.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bDoCollisionTest = true;

	/** How big should the query probe sphere be (in unreal units) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Editcondition = "bDoCollisionTest"))
	float ProbeSize = 12.f;

	/** Collision channel of the query probe */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Editcondition = "bDoCollisionTest"))
	TEnumAsByte<ECollisionChannel> ProbeChannel = ECC_Camera;

	/**
	* Ignoring collisions between the camera and the character(but not the camera itself) while camera moving for special objects. Enabled if standard collision test detected collision
	* see params @MovementCollisionTestDuration, @MovementCollisionTestMinLocationDelta, @MovementCollisionTestCollisionChannel
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|MovementCollisionTest")
	bool bDoMovementCollisionTest = true;

	/**
	* Duration of movement collision test after stopped movement
	* see @bDoMovementCollisionTest
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|MovementCollisionTest", meta = (Editcondition = "bDoMovementCollisionTest"))
	float MovementCollisionTestDuration = 1.f;

	/**
	* Minimal location delta for enable movement collision. Calc delta between @PreviousResultLoc and @desiredLoc from ATPCCameraLocationObject
	* see @bDoMovementCollisionTest
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|MovementCollisionTest", meta = (Editcondition = "bDoMovementCollisionTest"))
	float MovementCollisionTestMinLocationDelta = 1.f;

	/**
	* Ignoring collision works only for those objects for which collision @ObjectCollisionChannelForSkipCollision == Overlap
	* see @bDoMovementCollisionTest
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|MovementCollisionTest", meta = (Editcondition = "bDoMovementCollisionTest"))
	TEnumAsByte<ECollisionChannel> MovementCollisionTestCollisionChannel = ECC_Visibility;

	/** Minimal camera distance until character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MinCameraDistance = 100.f;
	/** Maximum camera distance from character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxCameraDistance = 1000.f;

	/** 
	* If is true, set current CameraDistance to DefaultCameraDistance on CameraMode changed
	* Disabled when @bCacheDistanceForCurrentCameraMode is true
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Editcondition = "!bCacheDistanceForCurrentCameraMode"))
	bool bSetDistanceToDefaultOnChangeCameraMode = true;
	/** If is true, set CameraDistance to this value in first CameraMode or  when CameraMode changed and if bSetDistanceToDefaultOnChangeCameraMode is true */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DefaultCameraDistance = 500.f;

	/** 
	* If is true, cached CameraDistance for current CameraMode and apply when it CameraMode again set
	* Override @bSetDistanceToDefaultOnChangeCameraMode
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bCacheDistanceForCurrentCameraMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed ZoomInterpolation = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ZoomDistance = 150.f;

	/** 
	* Offset at end of spring arm; use this instead of the relative offset of the attached component to ensure the line trace works as desired
	* X - x offset
	* Y - y offset
	* Z - z offset
	* Time - distance to character
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UCurveVector* SocketOffsetCurve = nullptr;
	/** SocketOffset change speed when changed CameraMode with a different SocketOffset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed SocketOffsetInterpolation = 20.f;

	/** Offset at start of spring, applied in world space.Use this if you want a world - space offset from the parent component instead of the usual relative - space offset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FVector TargetOffset = FVector::ZeroVector;
	/** TargetOffset change speed when changed CameraMode with a different TargetOffset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed TargetOffsetInterpolation = 20.f;

	/**
	* If is not null, add camera distance depending on current pitch rotation
	* Value - additional distance
	* Time - normalize pitch rotation
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UCurveFloat* PitchDistanceCurve = nullptr;

	/* DEPRECATED. See @ZoomInterpolation */
	UPROPERTY()
	EATPCInterpolationType ZoomInterpolationType_OLD = EATPCInterpolationType::SmoothInterpolation;
	/* DEPRECATED. See @ZoomInterpolation */
	UPROPERTY()
	float ZoomSpeed_OLD = 2.f;
	/* DEPRECATED. See @SocketOffsetInterpolation */
	UPROPERTY()
	float SocketOffsetInterpSpeed_OLD = 20.f;
	/* DEPRECATED. See @TargetOffsetInterpolation */
	UPROPERTY()
	float TargetOffsetInterpSpeed_OLD = 20.f;
};

/** Settings for offset Pitch rotation*/
USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCRotationOffsetSettings
{
	GENERATED_BODY()
public:
	FATPCRotationOffsetSettings() = default;
	FATPCRotationOffsetSettings(float InStartOffsetDelay, const FATPCInterploationSpeed& InRotationInterpolatiion, float InPitchOffset)
	    : StartOffsetDelay(InStartOffsetDelay), RotationInterpolation(InRotationInterpolatiion), PitchOffset(InPitchOffset) {}

	/** Offset delay after the user manually changed rotation of camera (for example, moved the mouse or made an input via the gamepad)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float StartOffsetDelay = 1.2f;

	/** Pitch rotation change speed(from current to PitchOffset)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed RotationInterpolation = 1.3f;

	/** Pitch offset for camera relative 0*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float PitchOffset = -15.f;

	/** If true, offset settings will only be applied while Actor movement speed >= @MinMovementSpeedForActivate*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bActivateOnlyIfMovement = true;

	/** Minimal actor movement speed for applied offset settings(if @bActivateOnlyIfMovement true)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bActivateOnlyIfMovement"))
	float MinMovementSpeedForActivate = 1.f;

	/* DEPRECATED. See @RotationInterpolation */
	UPROPERTY()
	float ChangeRotationSpeed_OLD = 1.3f;
	/* DEPRECATED. See @RotationInterpolation */
	UPROPERTY()
	EATPCInterpolationType InterpolationType_OLD = EATPCInterpolationType::SmoothInterpolation;
};

/**
* Settings for finding collisions over character. This allows you to lower camera when the character passes through the door, under bridges, under trees and more.
* 2 traces are used, the first to search for a collision in front of the character, the second to search for a collision over the character.
* If there is no collision in front of the character and there is a collision above him, then the offset will be applied 
*/
USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCRoofCollisionCheckSettings
{
	GENERATED_BODY()
public:
	/** List of collisions oobjects to check(in trace)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes = { ObjectTypeQuery1 /*worldStatic*/ };

	/** Half size trace from actor eye(getting eyes viewpoint from AActor::GetActorEyesViewPoint using in BoxTrace) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FVector EyesBoxTraceHalfSize = FVector(450.f, 30, 5.f);

	/** Angle of rotation for character roof trace. See @ActorRoofBoxTraceHalfSize */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float RoofTraceAngleFirst = 15.f;

	/** Half size trace from character eyes(getting eyes viewpoint from AActor::GetActorEyesViewPoint using in BoxTrace) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FVector RoofBoxTraceHalfSizeFirst = FVector(600.f, 30.f, 90.f);

	/** Angle of rotation for camera roof trace. See @CameraRoofBoxTraceHalfSize */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float RoofTraceAngleSecond = 160.f;

	/** Half size trace from trace(using in BoxTrace) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FVector RoofBoxTraceHalfSizeSecond = FVector(100.f, 30.f, 60.f);

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCRotationOffsetSettings RotationOffsetSettings = FATPCRotationOffsetSettings(0.4f, FATPCInterploationSpeed(1.3f), 0.f);
};

/** Settings for controlling the camera’s rotation in the direction of the character’s movement */
USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCViewRotationToActorRotationSettings
{
	GENERATED_BODY()
public:
	/** The maximum difference between yaw rotation of actor and camera to start following rotation of camera to rotation of actor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaxDeltaForChange = 170.f;

	/** Delay after the user manually changed rotation of camera (for example, moved the mouse or made an input via the gamepad)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float StartChangeDelay = 0.7f;

	/** Change speed of rotation of camera in direction of rotation of actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed RotationInterpolation = 1.f;

	/* DEPRECATED. See @RotationInterpolation */
	UPROPERTY()
	float ChangeRotationSpeed_OLD = 1.f;

	/* DEPRECATED. See @RotationInterpolation */
	UPROPERTY()
	float ChangeRotationSpeedInterpSpeed_OLD = 1.f;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCRotationSettings
{
	GENERATED_BODY()
public:
	/** Minimum view pitch, in degrees. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "-90.0", ClampMax = "0.0", UIMin = "-90.0", UIMax = "0.0"))
	float ViewPitchMin = -80.f;
	/** Maximum view pitch, in degrees. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", ClampMax = "90.0", UIMin = "0.0", UIMax = "90.0"))
	float ViewPitchMax = 80.f;

	/** Minimum view yaw, in degrees. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", ClampMax = "359.999", UIMin = "0.0", UIMax = "359.999"))
	float ViewYawMin = 0.f;
	/** Maximum view yaw, in degrees. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", ClampMax = "359.999", UIMin = "0.0", UIMax = "359.999"))
	float ViewYawMax = 359.9999f;

	/**
	* Rate of change of camera view(pitch and yaw)
	* Interpolation used for validation settings between dif camera modes
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed ViewInterpolation = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableRotationOffset = true;
	/** The default offset settings. Used when the user does not change the camera rotation manually.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (editcondition = "bEnableRotationOffset"))
	FATPCRotationOffsetSettings RotationOffsetSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableRoofCollisionCheckSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (editcondition = "bEnableRoofCollisionCheckSettings"))
	FATPCRoofCollisionCheckSettings RoofCollisionCheckSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableViewRotationToActorRotation = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (editcondition = "bEnableViewRotationToActorRotation"))
	FATPCViewRotationToActorRotationSettings ViewRotationToActorRotationSettings;

	/**
	 * If this component is placed on a pawn, should it use the view/control rotation of the pawn where possible?
	 * When disabled, the component will revert to using the stored RelativeRotation of the component.
	 * Note that this component itself does not rotate, but instead maintains its relative rotation to its parent as normal,
	 * and just repositions and rotates its children as desired by the inherited rotation settings. Use GetTargetRotation()
	 * if you want the rotation target based on all the settings (UsePawnControlRotation, InheritPitch, etc).
	 *
	 * @see ATPCCameraLocationObject::GetTargetRotation(), APawn::GetViewRotation()
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bUsePawnControlRotation = true;

	/** Should we inherit pitch from parent component. Does nothing if using Absolute Rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bInheritPitch = true;

	/** Should we inherit yaw from parent component. Does nothing if using Absolute Rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bInheritYaw = true;

	/** Should we inherit roll from parent component. Does nothing if using Absolute Rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bInheritRoll = true;

	/* DEPRECATED. See @ViewInterpolation */
	UPROPERTY()
	float ViewInterpolationSpeed_OLD = 50.f;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCFOVSettings
{
	GENERATED_BODY()
public:
	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float CameraFOV = 90.f;

	/**
	* Rate of change of field of view(FOV)
	* Interpolation used for validation settings between dif camera modes
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed FOVInterpolation = 7.f;

	/*
	* Value - FOV modifier
	* Time - Distance until to character
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UCurveFloat* PitchRotationFOVModifier = nullptr;

	/*
	* Value - FOV modifier
	* Time - Movement speed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UCurveFloat* MovementSpeedFOVModifier = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool ChangeFOVWhenCineCamera = false;

	/* DEPRECATED. See @FOVInterpolation */
	UPROPERTY()
	float InterpolationSpeed_OLD = 7.f;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCFadeSettings
{
	GENERATED_BODY()
public:
	/**
	* Time to completely show the object (if the material parameter = MaterialFadeMaxValue)
	*
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float FadeInTime = 0.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float FadeOutTime = 0.8f;

	/** Material param. During fade process this. Not support changing between different camera modes */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaterialFadeMinValue = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaterialFadeMaxValue = 1.f;

	/** 
	* The set of material parameters that will be set to the minimum @MaterialFadeMinValue or maximum @MaterialFadeMaxValue value.
	* These parameters (usually only 1 here) should hide or show the object.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<FName> MaterialFadeParamNames;

	/** 
	* This channel used in trace for find for objects are between camera and character.
	* see @UATPCCameraFadingObject::FindCollidedActors
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TEnumAsByte<ECollisionChannel> FadeChannel = ECC_Camera;

	/** 
	* Do need hide self character if he collided with camera.
	* For camera check radius see @SelfFadeCheckRadius
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bFadeSelfIfCollision = true;

	/** If true, then custom fade time will be used @SelfFadeCustomFadeOutTime, otherwise will be used @FadeOutTime*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bUseCustomFadeOutTimeForSelfFade = false;

	/** Custom fade time if @bUseCustomFadeOutTimeForSelfFade is true. Overrides @FadeOutTime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bUseCustomFadeOutTimeForSelfFade", ClampMin = "0.0", UIMin = "0.0"))
	float SelfFadeCustomFadeOutTime = 1.f;

	/** Radius sphere trace to determine camera collision with character*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bFadeSelfIfCollision", ClampMin = "1.0", UIMin = "1.0"))
	float SelfFadeCheckRadius = 18.f;

	/** If true, and if bFadeSelfIfCollision true then all attached actors to character will be faded */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bFadeSelfIfCollision"))
	bool bSelfFadeAttachedActors = true;
};

/**
* Automatically change the camera angle based on the terrain
*/
USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCFollowTerrainSettings
{
	GENERATED_BODY()
public:
	/** 
	* Curve with Socket offset. This curve don't override current socket offset, it modifier it(via + operation)
	* Curve X - x offset
	* Curve Y - y offset
	* Curve Z - z offset
	* Curve Time - current terrain pitch angle
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UCurveVector* SocketOffsetCurve = nullptr;

	/** Socket offset change speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed SocketOffsetInterpolation = 7.f;

	/**
	* Curve with Pitch offset. This curve don't override current pitch angle, it modifier it(via + operation)
	* Curve Value - Pitch offset
	* Curve Time - current terrain pitch angle
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UCurveFloat* PitchRotationCurve = nullptr;

	/** Pitch offset change speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed PitchRotationInterpolation = 7.f;

	/** Delay for applying Socket offset from @SocketOffsetCurve and pitch offset from @PitchRotationCurve after changing the terrain angle*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ChangePitchRotationDelay = 1.f;

	/* DEPRECATED. See @SocketOffsetInterpolation */
	UPROPERTY()
	float SocketOffsetInterpSpeed_OLD = 1.f;

	/* DEPRECATED. See @PitchRotationInterpolation */
	UPROPERTY()
	float AngleRotationInterpSpeed_OLD = 1.3f;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCCameraShakesSettings
{
	GENERATED_BODY()
public:
	/** CameraShake that are activated when camera mode started */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UCameraShakeBase> EnterToModeCameraShake;

	/** 
	* CameraShake that are activated when camera mode started if EnterToModeCameraShake is null 
	* or activated after playing @EnterToModeCameraShake
	* IMPORTANT: This shake is looping
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UCameraShakeBase> RegularCameraShake;

	/* If true stop all camera shakes on camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bNeedStopAllCameraShakeOnEnterToCameraMode = false;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCLockOnTargetSettings
{
	GENERATED_BODY()
public:
	/** If true, reset TargetActor from CameraLockOnTargetObject when other camera mode is set */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bResetTargetOnChangeCameraMode = false;

	/** If true, rotate camera by yaw when target is set */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool RotateCameraByYaw = true;

	/** If true, rotate camera by pitch when target is set */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool RotateCameraByPitch = true;

	/** Camera rotation interpolation speed for aiming to target */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCInterploationSpeed CameraRotationInterpolation = 1.3f;

	/**If true, reset CameraRotationInterpolation speed after set new a non null target actor(when the target cleared interpolation speed will be always reset)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bResetInterpolationSpeedAfterChangeTarget = false;

	/** If true, use rotation limits @ViewPitchMin, @ViewPitchMax, @ViewYawhMin, @ViewYawMax from RotationSettings. Otherwise set camera rotation to a target without limits */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bClampByCameraModeRotationLimits = true;

	/** If true, set a target only if distance between the camera owner and the target less than @MaxLockDistance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bUseMaxLockDistance = true;

	/**If true, a target will be cleared if distance between the camera owner and the target more than @MaxLockDistance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bUseMaxLockDistance"))
	bool bResetTargetOnReachMaxDistance = false;

	/** Max distance between the camera owner and a target, see @bUseMaxLockDistance and @bResetTargetOnReachMaxDistance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bUseMaxLockDistance"))
	float MaxLockDistance = 1000.f;

	/** If true, set a target only if line trace from the camera location to the target is clear */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bUseCheckTargetVisibility = true;

	/** If true, clear a target if line trace from the camera location to the target blocked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bUseCheckTargetVisibility"))
	bool bResetLockOnLostVisibleTarget = false;

	/** Trace channel for checks by @bUseCheckTargetVisibility and @bResetLockOnLostVisibleTarget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bUseCheckTargetVisibility"))
	TEnumAsByte<ECollisionChannel> CheckVisibilityTraceChannel = ECC_Visibility;

	/** If true, disable a player rotation input and hard rotate the camera to a target. Otherwise, allow the player input, but the camera will continue rotation to the target */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bHardLockOnTarget = false;

	/** If true, @bHardLockOnTarget is false and the camera has a target, then after a player input camera will stop rotating for @PauseLockAfterPlayerInputTime time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "!bHardLockOnTarget"))
	bool bPauseLockAfterPlayerInput = false;

	/** See @bPauseLockAfterPlayerInput */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bPauseLockAfterPlayerInput && !bHardLockOnTarget"))
	float PauseLockAfterPlayerInputTime = 1.f;

	/** If true, reset a target after a certain player rotation input @RequiredPlayerInputForResetTarget (usually via mouse or gamepad) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "!bHardLockOnTarget"))
	bool bResetTargetAfterPlayerInput = false;

	/**
	* Required a player input for reset a target. Input will be accumulated and after accumulated input is great then @RequiredPlayerInputForResetTarget on any axis the target will be reset 
	* If @ResetAccumulatedPlayerInputForResetTargetDelay > 0 accumulated input will be reset after player stop input and expiration time. Otherwise, input immediately will be reset after player stop input 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bResetTargetAfterPlayerInput && !bHardLockOnTarget"))
	FRotator RequiredPlayerInputForResetTarget = FRotator(30.f, 30.f, 0.f);

	/** See @RequiredPlayerInputForResetTarget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bResetTargetAfterPlayerInput && !bHardLockOnTarget"))
	float ResetAccumulatedPlayerInputForResetTargetDelay = 0.1f;

	/**
	* If true, use approximate cone @DeisredConeRotationYaw camera aiming to a target. For visualize enable @CameraDebugRules::bEnableLockOnTargetDebug from ATPCCameraComponent
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bUseDesiredConeRotation = false;

	/** See @bUseDesiredConeRotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bUseDesiredConeRotation"))
	float DeisredConeRotationYaw = 30.f;

	/* DEPRECATED. See @CameraRotationInterpolation */
	UPROPERTY()
	float CameraRotationSpeed_OLD = 3.f;

	/* DEPRECATED. See @CameraRotationInterpolation */
	UPROPERTY()
	float AdditionalSmoothRotationSpeed_OLD = 0.65f;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCCameraMode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableLocationSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bEnableLocationSettings"))
	FATPCLocationSettings LocationSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableRotationSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bEnableRotationSettings"))
	FATPCRotationSettings RotationSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableFOVSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bEnableFOVSettings"))
	FATPCFOVSettings FOVSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableFadeSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bEnableFadeSettings"))
	FATPCFadeSettings FadeSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableFollowTerrainSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bEnableFollowTerrainSettings"))
	FATPCFollowTerrainSettings FollowTerrainSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bEnableCameraShakesSettings = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bEnableCameraShakesSettings"))
	FATPCCameraShakesSettings CameraShakesSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FATPCLockOnTargetSettings LockOnTargetSettings;
};

USTRUCT(BlueprintType)
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCCameraDebugRules
{
	GENERATED_BODY()
public:
	/** Put errors to log and screen, otherwise put only to log */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logs")
	bool bPrintErrorsToScreen = true;

	/**
	* Debug object - CameraLocationObject
	* Show debug information about location object
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bEnableLocationObjectDebug = false;

	/** 
	* Debug object - CameraLocationObject
	* Show traces from roof collision and print info 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bEnableRoofCollisionCheckDebug = false;

	/**
	* Debug object - CameraFadingObject
	* Show debug trace for find objects between camera and character
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bEnableDrawFadeShapeDebug = false;

	/**
	* Debug object - CameraFollowTerrainObject
	* Print debug data
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bFollowTerrainEnableDebug = false;

	/**
	* Debug object - CameraLockOnTargetObject
	* Print and draw debug data
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bEnableLockOnTargetDebug = false;

	/*
	* Debug object - CameraLockOnTargetObject
	* Highlights target on scene via debug arrow
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bLockOnTargetShowTargetDebug = false;
};
