// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraBaseObject.h"
#include "Engine/EngineTypes.h"

#include "ATPCCameraShakesObject.generated.h"

class UCameraShakeBase;

UCLASS(classGroup = "ATPC")
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraShakesObject : public UATPCCameraBaseObject
{
	GENERATED_BODY()
public:
	virtual void OnEnterCameraMode(bool bWithInterpolation) override;
	virtual void OnExitCameraMode() override;

protected:
	/*
	* @return - key: isInfinite, value: duration
	*/
	TPair<bool, float> GetCameraShakeDuration(TSubclassOf<UCameraShakeBase> CameraShake) const;

	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake);
	void OnCameraShakeEnd();

protected:
	bool bPlayRegularCameraMode = false;
	FTimerHandle CameraShakeEndTimerHandle;
};