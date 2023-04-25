// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "ATPCCameraBaseObject.h"
#include "Engine/EngineTypes.h"

#include "ATPCCameraFadingObject.generated.h"

class AActor;

struct FATPCFadingActorInfo
{
public:
	FATPCFadingActorInfo() = default;
	FATPCFadingActorInfo(AActor* InActor, bool bInFadeOut, float InFadeTimeSpeed, float InFadeValue = 1.f);

	bool operator==(const FATPCFadingActorInfo& other) const;

public:
	TWeakObjectPtr<AActor> Actor;
	// bFadeOut is Disappear
	bool bFadeOut;
	float FadeOutTime;
	float FadeValue;
};

UCLASS(classGroup = "ATPC")
class ADVANCEDTHIRDPERSONCAMERA_API UATPCCameraFadingObject : public UATPCCameraBaseObject
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void Validate(bool bWithInterpolation) override;
	virtual void OnEnterCameraMode(bool bWithInterpolation) override;

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void AddIgnoredActor(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void RemoveIgnoredActor(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void ClearIgnoredActors();

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void AddManualFadeActor(AActor* Actor, bool bWithCustomTime = false, float CustomFadeOutTime = 0.f);
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void RemoveManualFadeActor(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void ClearManualFadeActors();

protected:
	virtual void SelfFade();

	// Trace and find collided actors
	virtual TArray<FHitResult> FindCollidedActors() const;
	virtual TArray<AActor*> FilterCollidedActors(const TArray<FHitResult>& HitResults);

	virtual void UpdateFadingActorsList(TArray<AActor*> RelevantActors);
	virtual void ApplyFade(float DeltaSeconds);

protected:
	TArray<FATPCFadingActorInfo> FadingActors;

	TSet<TWeakObjectPtr<AActor>> IgnoredActors;
	TSet<TWeakObjectPtr<AActor>> ManualFadingActors;
};