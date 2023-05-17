// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "SI_SunLight.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_SunLight : public AActor
{
	GENERATED_BODY()

public:

	ASI_SunLight();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDirectionalLightComponent* SunLightComponent;

	UFUNCTION()
	UDirectionalLightComponent* GetSunLightComponent();
	
};
