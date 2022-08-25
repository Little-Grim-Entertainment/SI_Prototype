// Fill out your copyright notice in the Description page of Project Settings.


#include "World/AoS_WorldManager.h"
#include "AoS_GameInstance.h"
#include "Data/AoS_MapData.h"
#include "Actors/AoS_SkySphere.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "Levels/AoS_LevelManager.h"
#include "World/AoS_SunLight.h"


UAoS_WorldManager::UAoS_WorldManager()
{
	CurrentTimeStamp.Hour = 0;
	CurrentTimeStamp.Minute = 0;
	CurrentTimeStamp.Second = 0;
	CurrentTimeStamp.Millisecond = 0;
	CurrentTimeStamp.WeekDay = EWeekDay::WD_Sunday;
	CurrentTimeStamp.MeridiemIndicator = EMeridiemIndicator::WD_AM;	
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
	StartTimerByHandle(TimeOfDayHandle);
}

void UAoS_WorldManager::WorldOnLevelFinishLoad(UAoS_MapData* LoadedLevel)
{
	if (!bTimePaused && SkySphere)
	{
		SkySphere->SetSunLightActor(GetLevelSunLight());
	}
}

void UAoS_WorldManager::StartTimerByHandle(FTimerHandle TimerToStart)
{
	for (FAOSWorldTimer CurrentTimer : WorldTimers)
	{
		if (CurrentTimer.TimerHandle == TimerToStart)
		{
			GetWorld()->GetTimerManager().SetTimer(CurrentTimer.TimerHandle, this, CurrentTimer.TimerMethod, CurrentTimer.Rate, CurrentTimer.bShouldLoop);
			return;
		}
	}
}

void UAoS_WorldManager::PauseTimer(bool bShouldPause)
{
	if (bShouldPause)
	{
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), TimeOfDayHandle);
	}
	else
	{
		UKismetSystemLibrary::K2_UnPauseTimerHandle(GetWorld(), TimeOfDayHandle);
	}
}

void UAoS_WorldManager::SetTimeStamp(EWeekDay InWeekDay, int32 InHour, int32 InMin, EMeridiemIndicator InMeridiemIndicator)
{
	if (InHour <= 0 || InHour > 12 || InMin < 0 || InMin > 59)
	{
		// Log note to only use 12 hour time
		return;
	}
	
	CurrentTimeStamp.WeekDay = InWeekDay;	
	if (InHour == 12 && InMeridiemIndicator == EMeridiemIndicator::WD_AM)
	{
		CurrentTimeStamp.Hour = 0;
	}
	else if (InHour < 12 && InMeridiemIndicator == EMeridiemIndicator::WD_PM)
	{
		CurrentTimeStamp.Hour = InHour + 12;
	}
	else
	{
		CurrentTimeStamp.Hour = InHour;
	}
	
	CurrentTimeStamp.Minute = InMin;
	CurrentTimeStamp.Second = 0;
	CurrentTimeStamp.Millisecond = 0;
	CurrentTimeStamp.MeridiemIndicator = InMeridiemIndicator;
}

FTimeStamp UAoS_WorldManager::GetTimeStamp()
{
	FTimeStamp TimeStamp;
	TimeStamp.Hour = 12;
	if (CurrentTimeStamp.Hour == 0)
	{
		TimeStamp.Hour = 12;
	}
	else if (CurrentTimeStamp.Hour > 12)
	{
		TimeStamp.Hour = CurrentTimeStamp.Hour - 12;
	}
	TimeStamp.Minute = CurrentTimeStamp.Minute;
	TimeStamp.MeridiemIndicator = CurrentTimeStamp.MeridiemIndicator;
	TimeStamp.WeekDay = CurrentTimeStamp.WeekDay;
	TimeStamp.CurrentTimeFloat = CurrentTimeStamp.CurrentTimeFloat;
	return TimeStamp;
}

void UAoS_WorldManager::UpdateTimer()
{
	
	CurrentTimeStamp.Millisecond++;

	if (CurrentTimeStamp.Millisecond >= 9)
	{
		CurrentTimeStamp.Millisecond = 0;
		CurrentTimeStamp.Second++;
		
		if (CurrentTimeStamp.Second >= 60)
		{
			CurrentTimeStamp.Second = 0;
			CurrentTimeStamp.Minute++;

			if (CurrentTimeStamp.Minute >= 60)
			{
				CurrentTimeStamp.Minute = 0;
				CurrentTimeStamp.Hour++;
				if (CurrentTimeStamp.Hour >= 12)
				{
					CurrentTimeStamp.MeridiemIndicator = EMeridiemIndicator::WD_PM;
				}
				if (CurrentTimeStamp.Hour >= 24)
				{
					CurrentTimeStamp.Hour = 0;
					CurrentTimeStamp.MeridiemIndicator = EMeridiemIndicator::WD_AM;
					uint8 CurrentDayInt = static_cast<uint8>(CurrentTimeStamp.WeekDay);
					CurrentDayInt++;
					if (CurrentDayInt >= 7)
					{
						CurrentDayInt = 0;
					}
					CurrentTimeStamp.WeekDay = static_cast<EWeekDay>(CurrentDayInt);
					OnNewDayStarted.Broadcast(CurrentTimeStamp.WeekDay);
				}
			}
		}
	}
	UpdateFloatTime();
}

void UAoS_WorldManager::UpdateSky()
{
	if (!bTimePaused && GameInstance && SkySphere)
	{
		const float TimeFloat = GetTimeStamp().CurrentTimeFloat;
		const float RotationSpeed = ((TimeFloat / 24.0f) *  360.0f) + 90.0f;
		const FRotator SunRotation = FRotator(RotationSpeed, SkySphere->GetActorRotation().Yaw , SkySphere->GetActorRotation().Roll);
		SkySphere->RotateSun(SunRotation);
	}
}

void UAoS_WorldManager::UpdateFloatTime()
{
	constexpr  float PercentModifier = 1.67f;
	const float ModifiedMin = FMath::Floor(CurrentTimeStamp.Minute * PercentModifier) * 0.01f;
	const float ModifiedSec = FMath::Floor(CurrentTimeStamp.Second * PercentModifier) * 0.0001f;

	CurrentTimeStamp.CurrentTimeFloat = CurrentTimeStamp.Hour + ModifiedMin + ModifiedSec;
}

void UAoS_WorldManager::CreateNewWorldTimer(FTimerHandle InTimerHandle, FString InTimerName, FTimerDelegate::TMethodPtr<UAoS_WorldManager> InTimerMethod, float InRate, bool bInShouldLoop)
{
	FAOSWorldTimer NewTimer;
	NewTimer.TimerHandle = InTimerHandle;
	NewTimer.TimerName = InTimerName;
	NewTimer.TimerMethod = InTimerMethod;
	NewTimer.Rate = InRate;
	NewTimer.bShouldLoop = bInShouldLoop;

	WorldTimers.Add(NewTimer);
}

void UAoS_WorldManager::InitializeWorldTimers()
{
	CreateNewWorldTimer(TimeOfDayHandle, "TimeOfDay", &UAoS_WorldManager::UpdateWorld, 0.005f, true);
}

void UAoS_WorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	TickerDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UAoS_WorldManager::Tick));

	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	InitializeWorldTimers();
}

void UAoS_WorldManager::Deinitialize()
{

	FTSTicker::GetCoreTicker().RemoveTicker(TickerDelegateHandle);

	Super::Deinitialize();
}

bool UAoS_WorldManager::Tick(float DeltaSeconds)
{

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

void UAoS_WorldManager::UpdateWorld()
{
	UpdateTimer();
	UpdateSky();
	FString DayString = UEnum::GetDisplayValueAsText(GetTimeStamp().WeekDay).ToString();
	int32 Hour = GetTimeStamp().Hour;
	FString HourString = UKismetTextLibrary::Conv_IntToText(Hour, false, true, 2, 2).ToString();
	int32 Minute = GetTimeStamp().Minute;
	FString MinuteString = UKismetTextLibrary::Conv_IntToText(Minute, false, true, 2, 2).ToString();
	FString MeridiemIndicatorStr = UEnum::GetDisplayValueAsText(GetTimeStamp().MeridiemIndicator).ToString();
		
	GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::Red, FString::Printf(TEXT("%s %s:%s %s"), *DayString, *HourString, *MinuteString, *MeridiemIndicatorStr));
}

void UAoS_WorldManager::SetSunRotationModifier(int32 Percentage)
{
	
}

