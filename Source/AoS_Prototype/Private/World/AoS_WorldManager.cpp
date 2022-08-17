// Fill out your copyright notice in the Description page of Project Settings.


#include "World/AoS_WorldManager.h"
#include "AoS_GameInstance.h"
#include "Actors/AoS_SkySphere.h"
#include "Engine/DirectionalLight.h"


UAoS_WorldManager::UAoS_WorldManager()
{
	
}

void UAoS_WorldManager::SetSkySphere(AAoS_SkySphere* SkySphereToSet)
{
	if (SkySphereToSet)
	{
		SkySphere = SkySphereToSet;
	}
}

void UAoS_WorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	TickerDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UAoS_WorldManager::Tick));

	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
}

void UAoS_WorldManager::Deinitialize()
{

	FTSTicker::GetCoreTicker().RemoveTicker(TickerDelegateHandle);

	Super::Deinitialize();
}

bool UAoS_WorldManager::Tick(float DeltaSeconds)
{
	if (!bTimePaused && GameInstance && SkySphere)
	{
		const FRotator SkyRotationSpeed = FRotator(0, GameInstance->TimeModifier * DeltaSeconds ,0);
		SkySphere->DirectionalLightActor->AddActorLocalRotation(SkyRotationSpeed);
		SkySphere->RefreshMaterial();
	}
	return true;
}
