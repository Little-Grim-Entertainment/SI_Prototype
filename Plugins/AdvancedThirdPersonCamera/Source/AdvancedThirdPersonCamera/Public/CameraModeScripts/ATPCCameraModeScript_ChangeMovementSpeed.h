// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraModeScript.h"

#include "ATPCCameraModeScript_ChangeMovementSpeed.generated.h"

UCLASS()
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraModeScript_ChangeMovementSpeed : public UATPCCameraModeScript
{
	GENERATED_BODY()
public:
	virtual void OnEnterCameraMode(UATPCCameraComponent* Camera) override;
	virtual void OnExitCameraMode() override;

	class UCharacterMovementComponent* GetMovementComponent(UATPCCameraComponent* Camera) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float NewMaxMovementSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bRestoreOldMovementSpeedOnExitCameraMode = true;

	UPROPERTY(BlueprintReadOnly, Category = "ATPC")
	float OldMaxMovementSpeed = 0.f;
};