// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "Components/SceneComponent.h"

#include "ATPCLockOnTargetLocationComponent.generated.h"

UCLASS(Blueprintable, Category = "ATPC", meta = (BlueprintSpawnableComponent))
class ADVANCEDTHIRDPERSONCAMERA_API UATPCLockOnTargetLocationComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "ATPC")
	virtual FVector GetTargetLocation();
};