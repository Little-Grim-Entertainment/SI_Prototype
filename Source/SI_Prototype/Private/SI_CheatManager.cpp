// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_CheatManager.h"
#include "World/SI_WorldManager.h"
#include "SI_GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Media/SI_MediaManager.h"
#include "Data/Cases/SI_CaseManager.h"
#include "Data/Media/SI_VideoDataAsset.h"
#include "Data/Media/SI_CinematicDataAsset.h"
#include "GameModes/SI_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SI_UIManager.h"
#include "UI/Debug/SI_GameplayTagViewer.h"
#include "GameplayTag/SI_GameplayTagManager.h"
#include "Widgets/SViewport.h"

USI_CheatManager::USI_CheatManager()
{
}

void USI_CheatManager::CheatEnableColor(bool bShouldEnable)
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

void USI_CheatManager::InitCheatManager()
{
	Super::InitCheatManager();
	
	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	SITagManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
}



void USI_CheatManager::CheatResetCase(const FString& CaseToResetName)
{
	if (USI_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_CaseManager>())
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

void USI_CheatManager::CheatResetPlayedVideos()
{
	if (USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>())
	{
		MediaManager->ResetAllVideos();
	}
}

void USI_CheatManager::CheatResetPlayedCinematics()
{
	if (USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>())
	{
		MediaManager->ResetAllCinematics();
	}
}

void USI_CheatManager::CheatSkipVideo()
{
	if (USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>())
	{
		if (IsValid(MediaManager->GetLoadedVideo()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedVideo());	
		}
	}
}

void USI_CheatManager::CheatSkipCinematic()
{
	if (USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>())
	{
		if (IsValid(MediaManager->GetLoadedCinematic()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedCinematic());
		}
	}
}

void USI_CheatManager::CheatHideHud(const bool bShouldHide)
{
	if (!IsValid(SITagManager)) {return;}
	
	if(bShouldHide)
	{
		SITagManager->RemoveTag(SITag_UI_HUD);
	}
	else
	{
		SITagManager->AddNewGameplayTag(SITag_UI_HUD);
	}		
}

void USI_CheatManager::CheatHideMapMenu(const bool bShouldHide)
{
	if (!IsValid(SITagManager)) {return;}
	
	if(bShouldHide)
	{
		SITagManager->RemoveTag(SITag_UI_Menu_Map);
	}
	else
	{
		SITagManager->AddNewGameplayTag(SITag_UI_Menu_Map);
	}	
}

void USI_CheatManager::CheatSetTimeStamp(FString Day, int32 Hour, int32 Minutes, FString AMPM)
{
	USI_WorldManager* WorldManager = GameInstance->GetSubsystem<USI_WorldManager>();
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

void USI_CheatManager::CheatIncreaseSunRotationSpeed(float Percentage)
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
	
	USI_WorldManager* WorldManager = GameInstance->GetSubsystem<USI_WorldManager>();

	WorldManager->SetSunRotationModifier(1.0f);
	WorldManager->SetSunRotationModifier(FinalRate);
}

void USI_CheatManager::CheatPauseWorldTimer(bool bShouldPause)
{
	USI_WorldManager* WorldManager = GameInstance->GetSubsystem<USI_WorldManager>();

	WorldManager->PauseTimerByName("TimeOfDay", bShouldPause);
}

void USI_CheatManager::DebugToggleGameplayTagViewer()
{
	if(!IsValid(GameInstance)) {return;}
	
	if(GameInstance->bGameplayTagViewerActive)
	{
		for (TObjectIterator<USI_GameplayTagViewer> It; It; ++It)
		{
			if(IsValid(*It))
			{
				USI_GameplayTagViewer* GameplayTagViewer = *It;
				GameInstance->GetGameViewportClient()->RemoveViewportWidgetContent(GameplayTagViewer->TakeWidget());
				GameInstance->bGameplayTagViewerActive = false;
			}
		}
	}
	else
	{
		USI_GameplayTagViewer* GameplayTagViewer = GameplayTagViewer = CreateWidget<USI_GameplayTagViewer>(GameInstance, GameInstance->GameplayTagViewerClass);
		
		if(IsValid(GameplayTagViewer))
		{
			GameInstance->GetGameViewportClient()->AddViewportWidgetContent(GameplayTagViewer->TakeWidget(), 99);
			GameInstance->bGameplayTagViewerActive = true;
		}
	}
}

void USI_CheatManager::CheatDisableUI()
{
	
}

void USI_CheatManager::CheatDisableHUD(const bool bShouldDisable)
{
	if(!IsValid(GameInstance)) {return;}
	
	USI_UIManager* UIManager = GameInstance->GetSubsystem<USI_UIManager>();
	if(!IsValid(UIManager)){return;}

	UIManager->ShowPlayerHUD(!bShouldDisable);
}
