// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraBaseObject.h"

#include "ATPCCameraFOVObject.generated.h"

UCLASS(classGroup = "ATPC")
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraFOVObject : public UATPCCameraBaseObject
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void Validate(bool bWithInterpolation) override;
	virtual void OnEnterCameraMode(bool bWithInterpolation) override;

	UFUNCTION(BlueprintPure, Category = "ATPC")
	float GetCurrentFOV() const;

protected:
	virtual void UpdateFOV(bool bWithInterpolation, float DeltaTime);
};