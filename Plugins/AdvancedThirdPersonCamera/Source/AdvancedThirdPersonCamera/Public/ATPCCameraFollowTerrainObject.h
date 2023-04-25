// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraBaseObject.h"
#include "ATPCOffsetValue.h"

#include "ATPCCameraFollowTerrainObject.generated.h"

UCLASS(classGroup = "ATPC")
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraFollowTerrainObject : public UATPCCameraBaseObject
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void Validate(bool bWithInterpolation) override;
	virtual void OnEnterCameraMode(bool bWithInterpolation) override;

protected:
	virtual void DetermineTerrainData();
	virtual void TraceToTerrain(struct FHitResult& HitResult) const;

	virtual void UpdateRotationAndLocationOffset(bool bWithInterp, float DeltaTime);

	virtual void PrintDebug();

protected:
	bool bPendingNewTerrainAngle = false;
	float TimeChangeTerrainAngle = 0.f;
	float CurrentTerrainAngle = 0.f;

	FATPCOffsetValue<FVector> TerrainSocketOffset;
	float CurrentTerrainRotationPitchOffset = 0.f;
	float TargetTerrainRotationPitchOffset = 0.f;
};