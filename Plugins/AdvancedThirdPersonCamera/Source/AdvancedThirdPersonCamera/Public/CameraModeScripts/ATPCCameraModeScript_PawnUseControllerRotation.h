// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraModeScript.h"

#include "ATPCCameraModeScript_PawnUseControllerRotation.generated.h"

/** Override params @OrientRotationToMovement and @UseControllerDesiredRotation in CharacterMovementComponent */
UCLASS()
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraModeScript_PawnUseControllerRotation : public UATPCCameraModeScript
{
	GENERATED_BODY()
public:
	virtual void OnEnterCameraMode(UATPCCameraComponent* Camera) override;
	virtual void OnExitCameraMode() override;

	class UCharacterMovementComponent* GetMovementComponent(UATPCCameraComponent* Camera) const;

public:
	/** Set @OrientRotationToMovement to CharacterMovementComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool OrientRotationToMovement = false;

	/** Set @UseControllerDesiredRotation to CharacterMovementComponent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool UseControllerDesiredRotation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bRestoreOldValuesOnExitCameraMode = true;

	UPROPERTY(BlueprintReadOnly, Category = "ATPC")
	bool OldOrientRotationToMovement = false;

	UPROPERTY(BlueprintReadOnly, Category = "ATPC")
	bool OldUseControllerDesiredRotation = false;
};
