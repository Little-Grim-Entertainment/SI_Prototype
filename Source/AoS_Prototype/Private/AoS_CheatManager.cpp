// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_CheatManager.h"
#include "World/AoS_WorldManager.h"
#include "AoS_GameInstance.h"
#include "Cinematics/AoS_CinematicsManager.h"
#include "Data/Cases/AoS_CaseManager.h"
#include "Data/Videos/AoS_VideoDataAsset.h"

UAoS_CheatManager::UAoS_CheatManager()
{
}

void UAoS_CheatManager::InitCheatManager()
{
	Super::InitCheatManager();
	
	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
}



void UAoS_CheatManager::CheatResetCase(FString CaseToResetName)
{
	if (UAoS_CaseManager* CaseManager = GameInstance->GetCaseManager())
	{
		if (CaseToResetName == "All")
		{
			CaseManager->ResetAllCases();
		}
		else
		{
			CaseManager->ResetCase(CaseToResetName);
		}
	}
}

void UAoS_CheatManager::CheatResetPlayedVideos()
{
	if (UAoS_CinematicsManager* CinematicsManager = GetWorld()->GetSubsystem<UAoS_CinematicsManager>())
	{
		CinematicsManager->ResetAllVideos();
	}
}

void UAoS_CheatManager::CheatSkipVideo()
{
	if (UAoS_CinematicsManager* CinematicsManager = GetWorld()->GetSubsystem<UAoS_CinematicsManager>())
	{
		CinematicsManager->GetLoadedVideo()->SkipVideo();
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
