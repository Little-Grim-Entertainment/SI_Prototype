// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraModeScript.h"

#include "ATPCCameraModeScript_RotateActorToTarget.generated.h"

/* Rotate actor to target from UATPCCameraLockOnTargetObject */
UCLASS()
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraModeScript_RotateActorToTarget : public UATPCCameraModeScript
{
	GENERATED_BODY()
public:
	UATPCCameraModeScript_RotateActorToTarget();

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float RotationSpeed = 1.5f;
};
