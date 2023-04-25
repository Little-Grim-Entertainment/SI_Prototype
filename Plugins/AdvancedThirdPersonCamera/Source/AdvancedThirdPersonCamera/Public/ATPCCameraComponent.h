// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCTypes.h"
#include "Components/SceneComponent.h"
#include "GameplayTagContainer.h"

#include "ATPCCameraComponent.generated.h"

class UATPCCameraModeDataAsset;

class AATPCCameraVolume;
class UATPCCameraBaseObject;
class UATPCCameraLocationObject;
class UATPCCameraFOVObject;
class UATPCCameraFadingObject;
class UATPCCameraFollowTerrainObject;
class UATPCCameraLockOnTargetObject;
class UATPCCameraShakesObject;
class UATPCCameraModeScript;
class APawn;
class APlayerController;
class APlayerCameraManager;

/** Main component in plugin*/
UCLASS(Blueprintable, classGroup = "ATPC", meta = (BlueprintSpawnableComponent))
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraComponent : public USceneComponent
{
	GENERATED_BODY()

	/** Called when camera mode is changed(set new camera mode, set override camera mode, reset override camera mode) */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraModeChangedDelegate);

public:
	UATPCCameraComponent();

	//~Begin USceneComponent Interface
	virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;
	//~End USceneComponent Interface

	//~ Begin UActorComponent Interface
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~ End UActorComponent Interface

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	virtual void ValidateComponents(bool bWithInterpolation);

	virtual void OnBeginOverlapCameraVolume(AATPCCameraVolume* CameraVolume);
	virtual void OnEndOverlapCameraVolume(AATPCCameraVolume* CameraVolume);

	//~ Begin Zoom Func
	UFUNCTION(BlueprintCallable, Category = "ATPC|Zoom")
	void ZoomIn();
	UFUNCTION(BlueprintCallable, Category = "ATPC|Zoom")
	void ZoomOut();
	UFUNCTION(BlueprintCallable, Category = "ATPC|Zoom")
	void SetCameraDistance(float NewDistance, bool bInterpolate);
	//~ End Zoom Func

	/** 
	* Set camera mode with @CameraModeTag from CameraModesAssets
	* @param bForceSet - if set true, ignores CanSetCameraMode
	*/
	UFUNCTION(BlueprintCallable, Category = "ATPC|CameraMode")
	virtual void SetCameraMode(FGameplayTag CameraModeTag, bool bWithInterpolation, bool bForceSet = false);

	/** This function for override */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "ATPC|CameraMode")
	bool CanSetCameraMode(FGameplayTag CameraModeTag) const;

	/** Find cameraVolume and return tag if volume is valid, otherwise return @DefaultCameraModeTag */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "ATPC|CameraMode")
	FGameplayTag GetInitialCameraModeTag() const;

	/** Find overlap camera volume via @FindOverlapCameraVolume and if volume and tag is valid return tag. Otherwise return invalid tag */
	UFUNCTION(BlueprintPure, Category = "ATPC|CameraMode")
	FGameplayTag GetCameraModeTagFromOverlapCameraVolume() const;

	/** This function for override. By default return current tag if it is valid, otherwise return @DefaultCameraModeTag */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "ATPC|CameraMode")
	FGameplayTag GetDesiredCameraModeTag() const;

	UFUNCTION(BlueprintPure, Category = "ATPC|CameraMode")
	FGameplayTag GetCurrentCameraModeTag() const;

	const UATPCCameraModeDataAsset* GetCurrentCameraMode() const;
	UFUNCTION(BlueprintPure, Category = "ATPC|CameraMode")
	UATPCCameraModeDataAsset* GetCurrentCameraMode();

	/** Override current camera mode(don't change current camera mode. For override used other variable) */
	UFUNCTION(BlueprintCallable, Category = "ATPC|CameraMode")
	virtual void SetCustomCameraMode(UATPCCameraModeDataAsset* CameraMode, bool bWithInterpolation);
	UFUNCTION(BlueprintCallable, Category = "ATPC|CameraMode")
	void ResetCustomCameraMode(bool bWithInterpolation);
	UFUNCTION(BlueprintCallable, Category = "ATPC|CameraMode")
	bool IsSetCustomCameraMode() const;

	//~ Begin functions for managing camera modes
	UFUNCTION(BlueprintCallable, Category = "ATPC|CameraMode")
	void AddCameraMode(UATPCCameraModeDataAsset* CameraMode);
	UFUNCTION(BlueprintCallable, Category = "ATPC|CameraMode")
	void RemoveCameraMode(FGameplayTag CameraModeName);
	UFUNCTION(BlueprintPure, Category = "ATPC|CameraMode")
	bool HasCameraMode(FGameplayTag CameraModeName) const;
	UATPCCameraModeDataAsset* GetCameraMode(FGameplayTag CameraModeName) const;
	UFUNCTION(BlueprintPure, Category = "ATPC|CameraMode")
	UATPCCameraModeDataAsset* GetCameraMode(FGameplayTag CameraModeName);
	UFUNCTION(BlueprintCallable, Category = "ATPC|CameraMode")
	void ClearAllCameraModes();
	//~ End functions for managing camera modes

	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual AATPCCameraVolume* FindOverlapCameraVolume() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	float GetCameraDistance() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	FVector GetCameraLocation() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	FRotator GetCameraRotation() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	UATPCCameraLocationObject* GetCameraLocationObject() const { return LocationObject; }
	UFUNCTION(BlueprintPure, Category = "ATPC")
	UATPCCameraFOVObject* GetCameraFOVObject() const { return FOVObject; }
	UFUNCTION(BlueprintPure, Category = "ATPC")
	UATPCCameraFadingObject* GetCameraFadingObject() const { return FadingObject; }
	UFUNCTION(BlueprintPure, Category = "ATPC")
	UATPCCameraFollowTerrainObject* GetCameraFollowTerrainObject() const { return FollowTerrainObject; }
	UFUNCTION(BlueprintPure, Category = "ATPC")
	UATPCCameraShakesObject* GetCameraShakesObject() const { return CameraShakesObject; }
	UFUNCTION(BlueprintPure, Category = "ATPC")
	UATPCCameraLockOnTargetObject* GetCameraLockOnTargetObject() const { return LockOnTargetObject; }

	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual bool IsCineCameraActive() const;

	/** Return true if initial camera mode is sets now(need for correct initialization some camera objects)*/
	bool IsSettingInitialCameraMode() const;

	template<typename T>
	T* CreateCameraObject(TSubclassOf<T> ObjectClass)
	{
		static_assert(TPointerIsConvertibleFromTo<T, const UATPCCameraBaseObject>::Value, "'T' template parameter to CreateCameraObject must be derived from UATPCCameraBaseObject");
		UClass* objClass = ObjectClass != nullptr ? ObjectClass.Get() : T::StaticClass();
		return CastChecked<T>(CreateCameraObjectImpl(objClass));
	}

	UFUNCTION(BlueprintPure, Category = "ATPC")
	APawn* GetOwningPawn() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	APlayerController* GetPlayerController() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	APlayerCameraManager* GetPlayerCameraManager() const;

public:
	UPROPERTY(BlueprintAssignable, Category = "ATPC")
	FOnCameraModeChangedDelegate OnCameraModeChangedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATPC")
	FATPCCameraDebugRules DebugRules;

protected:
	/* Create camera modes from CameraModeAssets */
	virtual void CreateCameraModesFromAssets();

	virtual void SetInitialCameraMode();

	virtual void InternalSetCameraMode(UATPCCameraModeDataAsset* NewCameraMode, TOptional<FGameplayTag> CameraModeTag, bool bWithInterpolation);

	virtual void NotifyExitCameraMode();
	virtual void NotifyEnterCameraMode(bool bWithInterpolation);

	virtual void CreateAllCameraObjects();

	void CheckCameraModesErros();
	void PutLog(const FString& Message, float MessageTime = 5.f);

	void RegisterConsoleCommands();

protected:
	UATPCCameraBaseObject* CreateCameraObjectImpl(TSubclassOf<UATPCCameraBaseObject> ObjectClass);

protected:
	bool bIsSettingInitialCameraMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ATPC|Settings")
	FGameplayTag DefaultCameraModeTag;

	/** Data assets with camera modes */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ATPC|Settings")
	TArray<UATPCCameraModeDataAsset*> CameraModesAssets;

	/** Storage for instanced camera modes sorted by FGameplayTag */
	UPROPERTY()
	TMap<FGameplayTag, UATPCCameraModeDataAsset*> SortedCameraModes;

	UPROPERTY()
	UATPCCameraModeDataAsset* CustomCameraMode;

	FGameplayTag CurrentCameraModeTag;

	UPROPERTY(EditAnywhere, NoClear, Category = "ATPC|Settings|CameraObjects")
	TSubclassOf<UATPCCameraLocationObject> LocationObjectClass;
	UPROPERTY(EditAnywhere, NoClear, Category = "ATPC|Settings|CameraObjects")
	TSubclassOf<UATPCCameraFOVObject> FOVObjectClass;
	UPROPERTY(EditAnywhere, NoClear, Category = "ATPC|Settings|CameraObjects")
	TSubclassOf<UATPCCameraFadingObject> FadingObjectClass;
	UPROPERTY(EditAnywhere, NoClear, Category = "ATPC|Settings|CameraObjects")
	TSubclassOf<UATPCCameraFollowTerrainObject> FollowTerrainObjectClass;
	UPROPERTY(EditAnywhere, NoClear, Category = "ATPC|Settings|CameraObjects")
	TSubclassOf<UATPCCameraShakesObject> CameraShakesObjectClass;
	UPROPERTY(EditAnywhere, NoClear, Category = "ATPC|Settings|CameraObjects")
	TSubclassOf<UATPCCameraLockOnTargetObject> LockOnTargetObjectClass;

	UPROPERTY(Transient)
	UATPCCameraLocationObject* LocationObject;
	UPROPERTY(Transient)
	UATPCCameraFOVObject* FOVObject;
	UPROPERTY(Transient)
	UATPCCameraFadingObject* FadingObject;
	UPROPERTY(Transient)
	UATPCCameraFollowTerrainObject* FollowTerrainObject;
	UPROPERTY(Transient)
	UATPCCameraShakesObject* CameraShakesObject;
	UPROPERTY(Transient)
	UATPCCameraLockOnTargetObject* LockOnTargetObject;

	UPROPERTY(Transient)
	TArray<UATPCCameraBaseObject*> CameraObjList;

	//Handled cine camera after switch target view?
	bool bHandledCineCamera = false;

private:
	UPROPERTY()
	UATPCCameraModeDataAsset* EmptyCameraMode;
	/* For correct view FATPCCameraMode in Blueprints Details panel */
	UPROPERTY()
	FATPCCameraMode CameraModeDEV;
};
