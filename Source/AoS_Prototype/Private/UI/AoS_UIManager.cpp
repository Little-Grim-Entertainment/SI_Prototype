// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"
#include "UI/AoS_DialogueBox.h"
#include "UI/AoS_HUD.h"
#include "UI/AoS_UserWidget.h"


UAoS_UIManager::UAoS_UIManager()
{

}

void UAoS_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	World = GetWorld();
	if (World)
	{
		GameInstance = Cast<UAoS_GameInstance>(World->GetGameInstance());
		if (IsValid(GameInstance))
		{
			GameInstance->OnGameInstanceInit.AddDynamic(this, &ThisClass::UAoS_UIManager::OnGameInstanceInit);
		}
		PlayerController = Cast<AAoS_PlayerController>(World->GetFirstPlayerController());
	}
}

void UAoS_UIManager::OnGameInstanceInit()
{
	GameInstance->GetLevelManager()->OnBeginLevelLoad.AddDynamic(this, &ThisClass::UAoS_UIManager::OnLevelBeginLoad);
	GameInstance->GetLevelManager()->OnLevelLoaded.AddDynamic(this, &ThisClass::UAoS_UIManager::OnLevelFinishLoad);
}

void UAoS_UIManager::CreatePlayerHUD()
{
	PlayerHUD =	CreateWidget<UAoS_HUD>(PlayerController);
	if (IsValid(PlayerHUD))
	{
		PlayerHUD->AddToViewport();
	}
}

void UAoS_UIManager::ShowPlayerHUD(bool bShouldShow)
{
	if(!IsValid(PlayerHUD))
	{
		return;
	}

	if (bShouldShow)
	{
		PlayerHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PlayerHUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAoS_UIManager::RemovePlayerHUD()
{
	if (!IsValid(PlayerHUD))
	{
		return;
	}
	
	PlayerHUD->RemoveFromParent();
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

void UAoS_UIManager::DisplayDialogueBox(UDlgContext* DlgContext)
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox()))
	{
		return;
	}
	
	PlayerHUD->GetDialogueBox()->SetVisibility(ESlateVisibility::Visible);
	PlayerHUD->GetDialogueBox()->UpdateDialogueBox(DlgContext);
}

void UAoS_UIManager::OnLevelBeginLoad(UAoS_MapData* LoadingLevel, bool bShouldFade)
{
	DisplayLoadingScreen(true, bShouldFade);
}

void UAoS_UIManager::OnLevelFinishLoad(UAoS_MapData* LoadingLevel, bool bShouldFade)
{
	DisplayLoadingScreen(false, bShouldFade);
}

