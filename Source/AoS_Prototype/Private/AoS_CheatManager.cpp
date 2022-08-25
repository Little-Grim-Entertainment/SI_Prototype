// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_CheatManager.h"
#include "World/AoS_WorldManager.h"
#include "AoS_GameInstance.h"

UAoS_CheatManager::UAoS_CheatManager()
{
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

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("TimeStampCheat Called!"));
		
	WorldManager->SetTimeStamp(WeekDay, Hour, Minutes, MeridiemIndicator);
}

void UAoS_CheatManager::CheatIncreaseSunRotationSpeed(int32 Percentage)
{
	if (Percentage < 0 || Percentage > 100) {return;}
	
}

void UAoS_CheatManager::InitCheatManager()
{
	Super::InitCheatManager();
	
	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
}
