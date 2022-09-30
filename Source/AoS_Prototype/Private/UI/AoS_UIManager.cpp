// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"
#include "Levels/AoS_LevelManager.h"
#include "UI/AoS_UserWidget.h"


UAoS_UIManager::UAoS_UIManager()
{

}

void UAoS_UIManager::DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade)
{
	if(GameInstance)
	{
		if (bShouldDisplay)
		{
			if (GameInstance->LoadingScreens.Num() > 0)
			{
				const int32 RandNumb = FMath::RandRange(0, GameInstance->LoadingScreens.Num() - 1);
				if (const TSubclassOf<UAoS_UserWidget> SelectedLoadingScreen = GameInstance->LoadingScreens[RandNumb])
				{
					LoadingScreen = Cast<UAoS_UserWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), SelectedLoadingScreen));
					if (LoadingScreen)
					{
						LoadingScreen->AddToViewport();
					}
				}
			}
		}
		else
		{
			if (IsValid(LoadingScreen))
			{
				if (bShouldFade)
				{
					LoadingScreen->FadeOutWidget();	
				}
				else
				{
					LoadingScreen->RemoveFromParent();
				}
			}
		}
	}
}

void UAoS_UIManager::UIOnLevelBeginLoad(UAoS_MapData* LoadingLevel, bool bShouldFade)
{
	DisplayLoadingScreen(true, bShouldFade);
}

void UAoS_UIManager::UIOnLevelFinishLoad(UAoS_MapData* LoadingLevel, bool bShouldFade)
{
	DisplayLoadingScreen(false, bShouldFade);
}

void UAoS_UIManager::UIManagerOnGameInstanceInit()
{

}

void UAoS_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	World = GetWorld();
	if (World)
	{
		GameInstance = Cast<UAoS_GameInstance>(World->GetGameInstance());
		if (GameInstance)
		{

		}
	}
}
