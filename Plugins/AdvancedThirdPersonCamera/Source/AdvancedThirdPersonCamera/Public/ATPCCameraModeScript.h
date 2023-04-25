// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCTypes.h"
#include "CoreMinimal.h"

#include "ATPCCameraModeScript.generated.h"

class UATPCCameraComponent;

UENUM()
enum class EATPCCameraModeScriptTickGroup
{
	PreCameraObjectTick,
	PostCameraObjectTick
};

/*
* Camera mode script is a special object that is created upon activation of the camera mode. 
* It is convenient for writing user logic, which should be linked to the camera mode.
*/
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew)
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraModeScript : public UObject
{
	GENERATED_BODY()
public:
	UATPCCameraModeScript();

	//~ Begin UObject Interface
#if WITH_ENGINE
	virtual class UWorld* GetWorld() const override;
#endif //WITH_ENGINE
	//~ End UObject Interface

	UATPCCameraComponent* GetCamera() const;

	virtual void OnEnterCameraMode(UATPCCameraComponent* Camera);
	virtual void OnExitCameraMode();
	virtual void Tick(float DeltaSeconds);

	bool IsEnableTick() const { return bEnableTick; }
	EATPCCameraModeScriptTickGroup GetTickGroup() const { return TickGroup; }

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnEnterCameraMode"))
	void K2_OnEnterCameraMode(UATPCCameraComponent* Camera);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnExitCameraMode"))
	void K2_OnExitCameraMode(UATPCCameraComponent* Camera);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))
	void K2_Tick(UATPCCameraComponent* Camera, float DeltaSeconds);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	UATPCCameraComponent* OwningCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Tick")
	bool bEnableTick = false;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Tick")
	EATPCCameraModeScriptTickGroup TickGroup = EATPCCameraModeScriptTickGroup::PostCameraObjectTick;

private:
	bool bHasK2TickImpl = false;
};
