// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "AoS_SunLight.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API AAoS_SunLight : public AActor
{
	GENERATED_BODY()

public:

	AAoS_SunLight();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDirectionalLightComponent* SunLightComponent;

	UFUNCTION()
	UDirectionalLightComponent* GetSunLightComponent();
	
};
