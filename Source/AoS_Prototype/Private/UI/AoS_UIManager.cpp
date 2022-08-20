// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"
#include "UI/AoS_UserWidget.h"


void UAoS_UIManager::DisplayLoadingScreen(bool bShouldDisplay)
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
			if (LoadingScreen)
			{
				LoadingScreen->FadeOutWidget();
			}
		}
	}
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
