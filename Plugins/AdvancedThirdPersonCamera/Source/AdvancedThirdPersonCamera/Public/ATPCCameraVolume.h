// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "GameFramework/Volume.h"
#include "GameplayTagContainer.h"

#include "ATPCCameraVolume.generated.h"

UCLASS(Blueprintable)
class ADVANCEDTHIRDPERSONCAMERA_API AATPCCameraVolume : public AVolume
{
	GENERATED_BODY()
public:
	AATPCCameraVolume(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FGameplayTag CameraModeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bChangeCameraModeWithInterp = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InlineEditConditionToggle))
	bool bCheckFilterActorClassWithCamera = false;
	//Exmp: Character or PlayerActor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bCheckFilterActorClassWithCamera"))
	TArray<TSubclassOf<AActor>> FilterActorClassesWithCamera;

protected:
	UFUNCTION()
	void OnVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnVolumeEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	virtual class UATPCCameraComponent* GetCameraFromActor(AActor* Actor);
};