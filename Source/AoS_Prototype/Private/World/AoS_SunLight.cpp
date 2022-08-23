// Fill out your copyright notice in the Description page of Project Settings.


#include "World/AoS_SunLight.h"

#include "Components/DirectionalLightComponent.h"

AAoS_SunLight::AAoS_SunLight()
{
	SunLightComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLightComponent"));
	SunLightComponent->SetupAttachment(RootComponent);
}

UDirectionalLightComponent* AAoS_SunLight::GetSunLightComponent()
{
	return SunLightComponent;
}
