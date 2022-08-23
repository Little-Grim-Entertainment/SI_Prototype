// Fill out your copyright notice in the Description page of Project Settings.


#include "World/AoS_WorldManager.h"

#include <string>

#include "AoS_GameInstance.h"
#include "Data/AoS_MapData.h"
#include "Actors/AoS_SkySphere.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/AoS_LevelManager.h"
#include "World/AoS_SunLight.h"


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

void UAoS_WorldManager::WorldOnMapTypeChange(EMapType InMapType)
{
	if (InMapType != EMapType::MT_Exterior)
	{
		bTimePaused = true;
	}
	else
	{
		bTimePaused = false;
	}
}

void UAoS_WorldManager::WorldManagerOnGameInstanceInit()
{
	if (GameInstance)
	{
		GameInstance->GetLevelManager()->OnMapTypeChanged.AddDynamic(this, &UAoS_WorldManager::WorldOnMapTypeChange);
	}
	StartTimer();
}

void UAoS_WorldManager::WorldOnLevelFinishLoad(UAoS_MapData* LoadedLevel)
{
	if (!bTimePaused && SkySphere)
	{
		SkySphere->SetSunLightActor(GetLevelSunLight());
	}
}

void UAoS_WorldManager::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimeOfDayHandle, this, &UAoS_WorldManager::UpdateTimer, 0.005f, true);
}

void UAoS_WorldManager::UpdateTimer()
{
	CurrentTimeMilSec++;

	if (CurrentTimeMilSec >= 9)
	{
		CurrentTimeMilSec = 0;
		CurrentTimeSec++;
		
		if (CurrentTimeSec >= 60)
		{
			CurrentTimeSec = 0;
			CurrentTimeMin++;

			if (CurrentTimeMin >= 60)
			{
				CurrentTimeMin = 0;
				CurrentTimeHour++;

				if (CurrentTimeHour >= 24)
				{
					CurrentTimeHour = 0;
					OnNewDayStarted.Broadcast();
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::Yellow, FString::Printf(TEXT("H: %s M: %s S: %s.%s"), *FString::FromInt(CurrentTimeHour), *FString::FromInt(CurrentTimeMin), *FString::FromInt(CurrentTimeSec), *FString::FromInt(CurrentTimeMilSec)));
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
		SkySphere->RotateSun(SkyRotationSpeed);
		SkySphere->RefreshMaterial();
	}
	return true;
}

AAoS_SunLight* UAoS_WorldManager::GetLevelSunLight()
{
	TArray<AActor*> SunLights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAoS_SunLight::StaticClass(), SunLights);

	for (AActor* CurrentActor : SunLights)
	{
		if (AAoS_SunLight* SunLight = Cast<AAoS_SunLight>(CurrentActor))
		{
			return SunLight;
		}
	}
	return nullptr;
}
