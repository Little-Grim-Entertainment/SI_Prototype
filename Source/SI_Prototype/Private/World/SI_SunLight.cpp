// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SI_SunLight.h"

#include "Components/DirectionalLightComponent.h"

ASI_SunLight::ASI_SunLight()
{
	SunLightComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLightComponent"));
	SunLightComponent->SetupAttachment(RootComponent);
}

UDirectionalLightComponent* ASI_SunLight::GetSunLightComponent()
{
	return SunLightComponent;
}
