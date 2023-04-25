// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"

#include "ATPCArrowDebugActor.generated.h"

UCLASS()
class ADVANCEDTHIRDPERSONCAMERA_API AATPCArrowDebugActor : public AActor
{
	GENERATED_BODY()
public:
	AATPCArrowDebugActor();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "ATPC")
	void PickActor(AActor* Actor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class USceneComponent* SceneRootcomponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class UArrowComponent* ArrowComponent;

private:
	float CurrentArrowAnimTime = 0.f;
	float CurrentArrowAnimTimeSign = 1.f;
};