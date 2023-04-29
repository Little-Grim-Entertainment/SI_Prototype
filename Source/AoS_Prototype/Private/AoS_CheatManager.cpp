// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_CheatManager.h"
#include "World/AoS_WorldManager.h"
#include "AoS_GameInstance.h"
#include "Media/AoS_MediaManager.h"
#include "Data/Cases/AoS_CaseManager.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Kismet/GameplayStatics.h"

UAoS_CheatManager::UAoS_CheatManager()
{
}

void UAoS_CheatManager::CheatEnableColor(bool bShouldEnable)
{
	if (!bShouldEnable)
	{
		const FLatentActionInfo LatentActionInfo;
		UGameplayStatics::LoadStreamLevel(this, FName(TEXT("M_PostProcess")), true, true, LatentActionInfo);
	}
	else
	{
		const FLatentActionInfo LatentActionInfo;
		UGameplayStatics::UnloadStreamLevel(this, FName(TEXT("M_PostProcess")), LatentActionInfo, false);
	}
}

void UAoS_CheatManager::InitCheatManager()
{
	Super::InitCheatManager();
	
	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
}



void UAoS_CheatManager::CheatResetCase(const FString& CaseToResetName)
{
	if (UAoS_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_CaseManager>())
	{
		if (CaseToResetName == "All")
		{
			CaseManager->ResetAllCases();
		}
		else
		{
			CaseManager->ResetCase(CaseManager->GetCaseByName(CaseToResetName));
		}
	}
}

void UAoS_CheatManager::CheatResetPlayedVideos()
{
	if (UAoS_MediaManager* MediaManager = GetWorld()->GetSubsystem<UAoS_MediaManager>())
	{
		MediaManager->ResetAllVideos();
	}
}

void UAoS_CheatManager::CheatResetPlayedCinematics()
{
	if (UAoS_MediaManager* MediaManager = GetWorld()->GetSubsystem<UAoS_MediaManager>())
	{
		MediaManager->ResetAllCinematics();
	}
}

void UAoS_CheatManager::CheatSkipVideo()
{
	if (UAoS_MediaManager* MediaManager = GetWorld()->GetSubsystem<UAoS_MediaManager>())
	{
		if (IsValid(MediaManager->GetLoadedVideo()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedVideo());	
		}
	}
}

void UAoS_CheatManager::CheatSkipCinematic()
{
	if (UAoS_MediaManager* MediaManager = GetWorld()->GetSubsystem<UAoS_MediaManager>())
	{
		if (IsValid(MediaManager->GetLoadedCinematic()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedCinematic());
		}
	}
}

void UAoS_CheatManager::CheatSetTimeStamp(FString Day, int32 Hour, int32 Minutes, FString AMPM)
{
	UAoS_WorldManager* WorldManager = GameInstance->GetSubsystem<UAoS_WorldManager>();
	EWeekDay WeekDay = EWeekDay::WD_Sunday;
	EMeridiemIndicator MeridiemIndicator = EMeridiemIndicator::WD_AM;

	for (const EWeekDay CurrentWeekDay : TEnumRange<EWeekDay>())
	{
		FString DayToString = UEnum::GetDisplayValueAsText(CurrentWeekDay).ToString();
		if (DayToString == Day)
		{
			WeekDay = CurrentWeekDay;
		}
	}
	for (const EMeridiemIndicator CurrentMeridiemIndicator : TEnumRange<EMeridiemIndicator>())
	{
		FString MeridiemIndicatorToString = UEnum::GetDisplayValueAsText(CurrentMeridiemIndicator).ToString();
		if (MeridiemIndicatorToString == AMPM)
		{
			MeridiemIndicator = CurrentMeridiemIndicator;
		}
	}
	
	WorldManager->SetTimeStamp(WeekDay, Hour, Minutes, MeridiemIndicator);
}

void UAoS_CheatManager::CheatIncreaseSunRotationSpeed(float Percentage)
{
	float FinalRate;
	if (Percentage <= 0)
	{
		FinalRate = 1;
	}
	else
	{
		FinalRate = Percentage/100;
	}	
	
	UAoS_WorldManager* WorldManager = GameInstance->GetSubsystem<UAoS_WorldManager>();

	WorldManager->SetSunRotationModifier(1.0f);
	WorldManager->SetSunRotationModifier(FinalRate);
}

void UAoS_CheatManager::CheatPauseWorldTimer(bool bShouldPause)
{
	UAoS_WorldManager* WorldManager = GameInstance->GetSubsystem<UAoS_WorldManager>();

	WorldManager->PauseTimerByName("TimeOfDay", bShouldPause);
}
