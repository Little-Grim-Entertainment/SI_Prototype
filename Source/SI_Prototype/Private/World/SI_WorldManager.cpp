// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SI_WorldManager.h"
#include "SI_GameInstance.h"
#include "Actors/SI_SkySphere.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "Levels/SI_LevelManager.h"
#include "World/SI_SunLight.h"


USI_WorldManager::USI_WorldManager()
{
	CurrentTimeStamp.Hour = 0;
	CurrentTimeStamp.Minute = 0;
	CurrentTimeStamp.Second = 0;
	CurrentTimeStamp.Millisecond = 0;
	CurrentTimeStamp.WeekDay = EWeekDay::WD_Sunday;
	CurrentTimeStamp.MeridiemIndicator = EMeridiemIndicator::WD_AM;	
}

void USI_WorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	TickerDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &USI_WorldManager::Tick));

	Super::Initialize(Collection);
	
	InitializeWorldTimers();
	SetTimeStamp(EWeekDay::WD_Sunday, 10, 00, EMeridiemIndicator::WD_AM);
}

void USI_WorldManager::Deinitialize()
{

	FTSTicker::GetCoreTicker().RemoveTicker(TickerDelegateHandle);

	Super::Deinitialize();
}

void USI_WorldManager::OnGameInstanceInit()
{
	Super::OnGameInstanceInit();
	
	//GameInstance->GetLevelManager()->OnMapTypeChanged.AddDynamic(this, &ThisClass::OnMapTypeChange);
	//GameInstance->GetLevelManager()->OnLevelLoaded.AddDynamic(this, &ThisClass::OnLevelFinishLoad);

	StartTimerByHandle(TimeOfDayHandle);
	PauseTimerByHandle(TimeOfDayHandle, true);
}

void USI_WorldManager::SetSkySphere(ASI_SkySphere* SkySphereToSet)
{
	if (SkySphereToSet)
	{
		SkySphere = SkySphereToSet;
	}
}

void USI_WorldManager::OnLevelFinishLoad(USI_MapData* LoadedLevel, bool bShouldFade)
{
	if (bRotateSun && SkySphere)
	{
		SkySphere->SetSunLightActor(GetLevelSunLight());
	}
}

void USI_WorldManager::StartTimerByHandle(FTimerHandle& InTimerHandle)
{
	FSIWorldTimer& TimerToStart = GetTimerByHandle(InTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(InTimerHandle, this, TimerToStart.TimerMethod, TimerToStart.Rate, TimerToStart.bShouldLoop);
	TimerToStart.TimerHandle = InTimerHandle;
}

void USI_WorldManager::PauseTimerByHandle(FTimerHandle& InTimerHandle, bool bShouldPause)
{
	if (bShouldPause)
	{
		GetWorld()->GetTimerManager().PauseTimer(InTimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().UnPauseTimer(InTimerHandle);
	}
}

void USI_WorldManager::PauseTimerByName(FString InTimerName, bool bShouldPause)
{
	FSIWorldTimer& TimerToPause = GetTimerByName(InTimerName);

	if (bShouldPause)
	{
		GetWorld()->GetTimerManager().PauseTimer(TimerToPause.TimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().UnPauseTimer(TimerToPause.TimerHandle);
	}
}

void USI_WorldManager::SetTimeStamp(EWeekDay InWeekDay, int32 InHour, int32 InMin, EMeridiemIndicator InMeridiemIndicator)
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

FTimeStamp USI_WorldManager::GetTimeStamp()
{
	FTimeStamp TimeStamp;
	TimeStamp.Hour = CurrentTimeStamp.Hour;
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

FSIWorldTimer& USI_WorldManager::GetTimerByHandle(FTimerHandle& InTimerHandle)
{
	for (FSIWorldTimer& CurrentTimer : WorldTimers)
	{
		if (CurrentTimer.TimerHandle == InTimerHandle)
		{
			return CurrentTimer;
		}
	}
	return DefaultTimer;
}

FSIWorldTimer& USI_WorldManager::GetTimerByName(FString InTimerName)
{
	for (FSIWorldTimer& CurrentTimer : WorldTimers)
	{
		if (CurrentTimer.TimerName == InTimerName)
		{
			return CurrentTimer;
		}
	}
	return DefaultTimer;
}

void USI_WorldManager::ResetTimerByHandle(FTimerHandle& InTimerHandle)
{
	FSIWorldTimer& TimerToReset = GetTimerByHandle(InTimerHandle);
	
	GetWorld()->GetTimerManager().ClearTimer(InTimerHandle);
	TimerToReset.TimerHandle = InTimerHandle;
	StartTimerByHandle(InTimerHandle);
}

void USI_WorldManager::UpdateTimer()
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

void USI_WorldManager::UpdateSky()
{
	if (bRotateSun && GameInstance && SkySphere)
	{
		const float TimeFloat = GetTimeStamp().CurrentTimeFloat;
		const float RotationSpeed = ((TimeFloat / 24.0f) *  360.0f) + 90.0f;
		const FRotator SunRotation = FRotator(RotationSpeed, SkySphere->GetActorRotation().Yaw , SkySphere->GetActorRotation().Roll);
		SkySphere->RotateSun(SunRotation);
	}
}

void USI_WorldManager::UpdateFloatTime()
{
	constexpr  float PercentModifier = 1.67f;
	const float ModifiedMin = FMath::Floor(CurrentTimeStamp.Minute * PercentModifier) * 0.01f;
	const float ModifiedSec = FMath::Floor(CurrentTimeStamp.Second * PercentModifier) * 0.0001f;

	CurrentTimeStamp.CurrentTimeFloat = CurrentTimeStamp.Hour + ModifiedMin + ModifiedSec;
}

void USI_WorldManager::CreateNewWorldTimer(FTimerHandle& InTimerHandle, FString InTimerName, FTimerDelegate::TMethodPtr<USI_WorldManager> InTimerMethod, float InRate, bool bInShouldLoop)
{
	const FSIWorldTimer& CurrentTimer = GetTimerByHandle(InTimerHandle);
	if (CurrentTimer.TimerName != "NULL") {return;}
	FSIWorldTimer NewTimer;
	NewTimer.TimerHandle = InTimerHandle;
	NewTimer.TimerName = InTimerName;
	NewTimer.TimerMethod = InTimerMethod;
	NewTimer.Rate = InRate;
	NewTimer.bShouldLoop = bInShouldLoop;

	WorldTimers.Add(NewTimer);
}

void USI_WorldManager::InitializeWorldTimers()
{
	CreateNewWorldTimer(TimeOfDayHandle, "TimeOfDay", &USI_WorldManager::UpdateWorld, SunRotationModifier * SunRotationSpeed, true);
}

bool USI_WorldManager::Tick(float DeltaSeconds)
{

	return true;
}

ASI_SunLight* USI_WorldManager::GetLevelSunLight()
{
	TArray<AActor*> SunLights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASI_SunLight::StaticClass(), SunLights);

	for (AActor* CurrentActor : SunLights)
	{
		if (ASI_SunLight* SunLight = Cast<ASI_SunLight>(CurrentActor))
		{
			return SunLight;
		}
	}
	return nullptr;
}

void USI_WorldManager::UpdateWorld()
{
	UpdateTimer();
	UpdateSky();
	FString DayString = UEnum::GetDisplayValueAsText(GetTimeStamp().WeekDay).ToString();
	int32 Hour = GetTimeStamp().Hour;
	FString HourString = UKismetTextLibrary::Conv_IntToText(Hour, false, true, 2, 2).ToString();
	int32 Minute = GetTimeStamp().Minute;
	FString MinuteString = UKismetTextLibrary::Conv_IntToText(Minute, false, true, 2, 2).ToString();
	FString MeridiemIndicatorStr = UEnum::GetDisplayValueAsText(GetTimeStamp().MeridiemIndicator).ToString();
	
	//GEngine->AddOnScreenDebugMessage(-1, 0.005f, FColor::Red, FString::Printf(TEXT("%s %s:%s %s"), *DayString, *HourString, *MinuteString, *MeridiemIndicatorStr));
}

void USI_WorldManager::SetSunRotationModifier(float InRate)
{
	FSIWorldTimer& SunTimer = GetTimerByHandle(TimeOfDayHandle);
	SunRotationModifier = InRate;
	SunTimer.Rate = SunRotationSpeed * SunRotationModifier;
	ResetTimerByHandle(TimeOfDayHandle);
}

