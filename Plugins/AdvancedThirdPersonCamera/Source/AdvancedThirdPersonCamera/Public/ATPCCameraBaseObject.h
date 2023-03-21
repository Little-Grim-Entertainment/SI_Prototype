// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "ATPCCameraBaseObject.generated.h"

class UATPCCameraComponent;

/** 
* Base object for all camera objects in this plugin 
* All K2(blueprint) functions are called from native functions(example: K2Tick from Tick)
*/
UCLASS(classGroup = "ATPC", Blueprintable, BlueprintType)
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraBaseObject : public UObject
{
	GENERATED_BODY()
public:
	//~ Begin UObject Interface
#if WITH_ENGINE
	virtual class UWorld* GetWorld() const override;
#endif //WITH_ENGINE
	//~ End UObject Interface

	virtual void Tick(float DeltaSeconds);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))
	void K2_Tick(float DeltaSeconds);

	/** Validate params in object */
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	virtual void Validate(bool bWithInterpolation);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Validate"))
	void K2_Validate(bool bWithInterpolation);

	virtual void OnExitCameraMode();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnExitCameraMode"))
	void K2_OnExitCameraMode();
	virtual void OnEnterCameraMode(bool bWithInterpolation);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnEnterCameraMode"))
	void K2_OnEnterCameraMode(bool bWithInterpolation);

	virtual void SwitchToCineCamera();

	void SetCamera(UATPCCameraComponent* Camera);
	UATPCCameraComponent& GetCamera();
	const UATPCCameraComponent& GetCamera() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	UATPCCameraComponent* GetOwningCamera() const;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	class AActor* GetOwningActor() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	class APawn* GetOwningPawn() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	class APlayerController* GetPlayerController() const;
	UFUNCTION(BlueprintPure, Category = "ATPC")
	class APlayerCameraManager* GetPlayerCameraManager() const;

private:
	UPROPERTY()
	UATPCCameraComponent* OwningCamera;
};
