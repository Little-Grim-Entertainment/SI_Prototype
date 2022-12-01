// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"

// Subsystems
#include "Data/Cases/AoS_CaseManager.h"
#include "Levels/AoS_LevelManager.h"
#include "Dialogue/AoS_DialogueManager.h"
#include "Cinematics/AoS_CinematicsManager.h"

// Case Data
#include "Data/Cases/AoS_Case.h"
#include "Data/Cases/AoS_Part.h"
#include "Data/Cases/AoS_Objective.h"

// UI
#include "UI/AoS_DialogueBox.h"
#include "UI/AoS_HUD.h"
#include "UI/AoS_UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/AoS_MoviePlayerWidget.h"



#include "Controllers/AoS_PlayerController.h"
#include "Data/Maps/AoS_MapData.h"
#include "GameModes/AoS_GameMode.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSource.h"


UAoS_UIManager::UAoS_UIManager()
{

}

void UAoS_UIManager::OnGameInstanceInit()
{
	Super::OnGameInstanceInit();
	
	BindLevelManagerDelegates();
	BindCaseManagerDelegates();
}

void UAoS_UIManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	
}

void UAoS_UIManager::BindDialogueManagerDelegates(UAoS_DialogueManager* InDialogueManager)
{
	
}

void UAoS_UIManager::BindLevelManagerDelegates()
{
	GameInstance->GetLevelManager()->OnBeginLevelLoad.AddDynamic(this, &ThisClass::UAoS_UIManager::OnLevelBeginLoad);
	GameInstance->GetLevelManager()->OnLevelLoaded.AddDynamic(this, &ThisClass::UAoS_UIManager::OnLevelFinishLoad);
}

void UAoS_UIManager::BindCaseManagerDelegates()
{
	// Case Bindings
	GameInstance->GetCaseManager()->OnCaseAccepted.AddDynamic(this, &ThisClass::OnCaseAccepted);
	GameInstance->GetCaseManager()->OnCaseActivated.AddDynamic(this, &ThisClass::OnCaseActivated);
	GameInstance->GetCaseManager()->OnCaseComplete.AddDynamic(this, &ThisClass::OnCaseCompleted);

	// Part Bindings
	GameInstance->GetCaseManager()->OnPartActivated.AddDynamic(this, &ThisClass::OnPartActivated);
	GameInstance->GetCaseManager()->OnPartComplete.AddDynamic(this, &ThisClass::OnPartCompleted);

	// Objective Bindings
	GameInstance->GetCaseManager()->OnObjectiveActivated.AddDynamic(this, &ThisClass::OnObjectiveActivated);
	GameInstance->GetCaseManager()->OnObjectiveComplete.AddDynamic(this, &ThisClass::OnObjectiveCompleted);
}


void UAoS_UIManager::OnPlayerModeChanged(EPlayerMode NewPlayerMode)
{
	Super::OnPlayerModeChanged(NewPlayerMode);

	RemovePlayerHUD();
	RemoveMoviePlayerWidget();
	RemoveMainMenu();

	if(GameInstance->GetLevelManager()->GetCurrentLoadedLevel()->MapType == EMapType::MT_Menu && NewPlayerMode != EPlayerMode::PM_LevelLoadingMode)
	{
		SetMenuMode(true);	
	}
	else if (NewPlayerMode != EPlayerMode::PM_LevelLoadingMode)
	{
		CreatePlayerHUD();
		SetMenuMode(false);
	}
	
	switch (NewPlayerMode)
	{
		case EPlayerMode::PM_MainMenuMode:
		{
			CreateMainMenu();
			SetMenuMode(true, MainMenu);
			break;	
		}
		case EPlayerMode::PM_CinematicMode:
		{
			if (IsValid(PlayerHUD))
			{
				RemovePlayerHUD();
			}
			break;	
		}
		case EPlayerMode::PM_VideoMode:
		{
			CreateMoviePlayerWidget();
		}
		case EPlayerMode::PM_LevelLoadingMode:
		{
			if (IsValid(PlayerHUD))
			{
				RemovePlayerHUD();
			}
			if(!IsValid(PlayerController))
			{
				PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
				if(!IsValid(PlayerController)){break;}
			}
			SetMenuMode(false);
			PlayerController->SetShowMouseCursor(false);
			break;	
		}
		case EPlayerMode::PM_ObservationMode:
		{
			if (IsValid(PlayerHUD))
			{
				PlayerHUD->GetReticle()->SetVisibility(ESlateVisibility::Visible);
			}
		}
		default:
		{
			break;
		}
	}
}

void UAoS_UIManager::CreatePlayerHUD()
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(GameInstance)){return;}
	
	PlayerHUD =	CreateWidget<UAoS_HUD>(GameInstance, GameInstance->GetCurrentGameMode()->PlayerHUD_Class);
	if (IsValid(PlayerHUD))
	{
		PlayerHUD->AddToViewport();
	}
}

void UAoS_UIManager::CreateMoviePlayerWidget()
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(GameInstance)){return;}
	
	MoviePlayerWidget =	CreateWidget<UAoS_MoviePlayerWidget>(GameInstance, GameInstance->GetCurrentGameMode()->MoviePlayerWidget);
	if (IsValid(MoviePlayerWidget))
	{
		UAoS_CinematicsManager* CinematicsManager = GetWorld()->GetSubsystem<UAoS_CinematicsManager>();
		MoviePlayerWidget->SetMediaTexture(CinematicsManager->GetCurrentMediaTexture());
		MoviePlayerWidget->SetMediaPlayer(CinematicsManager->GetCurrentMediaPlayer());
		MoviePlayerWidget->SetMediaSource(CinematicsManager->GetCurrentMediaSource());
		MoviePlayerWidget->AddToViewport();
		MoviePlayerWidget->PlayVideo();
	}
}

void UAoS_UIManager::RemoveMoviePlayerWidget()
{
	if (!IsValid(MoviePlayerWidget)){return;}
	
	MoviePlayerWidget->RemoveFromParent();
}

void UAoS_UIManager::ShowPlayerHUD(bool bShouldShow)
{
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
	if (!IsValid(PlayerHUD)){return;}
	
	PlayerHUD->RemoveFromParent();
}

void UAoS_UIManager::CreateMainMenu()
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(PlayerController)){return;}
	
	MainMenu =	CreateWidget<UAoS_UserWidget>(PlayerController,  GameInstance->GetCurrentGameMode()->MainMenuClass);
	if (IsValid(MainMenu))
	{
		MainMenu->AddToViewport();
	}
}

void UAoS_UIManager::RemoveMainMenu()
{
	if (!IsValid(MainMenu)){return;}
	
	MainMenu->RemoveFromParent();
}

void UAoS_UIManager::SetMenuMode(bool bInMenu, UAoS_UserWidget* WidgetToFocus)
{
	if(!IsValid(PlayerController))
	{
		PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
		if(!IsValid(PlayerController)){return;}
	}
	
	if (bInMenu)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, WidgetToFocus);
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
	}
}

void UAoS_UIManager::DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade)
{
	if (!IsValid(GameInstance)){return;}
	
	if (bShouldDisplay)
	{
		if (GameInstance->LoadingScreens.Num() > 0)
		{
			const int32 RandNumb = FMath::RandRange(0, GameInstance->LoadingScreens.Num() - 1);
			if (const TSubclassOf<UAoS_UserWidget> SelectedLoadingScreen = GameInstance->LoadingScreens[RandNumb])
			{
				LoadingScreen = Cast<UAoS_UserWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), SelectedLoadingScreen));
				
				if (IsValid(LoadingScreen))
				{
					GameInstance->GetGameViewportClient()->AddViewportWidgetContent(LoadingScreen->TakeWidget());
					if(!IsValid(PlayerController))
					{
						PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
						if(!IsValid(PlayerController)){return;}
					}
					PlayerController->SetIgnoreMoveInput(true);
					PlayerController->SetIgnoreLookInput(true);
					SetMenuMode(true, LoadingScreen);
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
				GameInstance->GetGameViewportClient()->RemoveViewportWidgetContent(LoadingScreen->TakeWidget());
			}
			if(!IsValid(PlayerController))
			{
				PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
				if(!IsValid(PlayerController)){return;}
			}
			PlayerController->SetIgnoreMoveInput(false);
			PlayerController->SetIgnoreLookInput(false);
		}
	}
}

void UAoS_UIManager::DisplayDialogueBox()
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())){return;}
	
	PlayerHUD->GetDialogueBox()->SetVisibility(ESlateVisibility::Visible);
}

void UAoS_UIManager::OnLevelBeginLoad(UAoS_MapData* LoadingLevel, bool bShouldFade)
{
	DisplayLoadingScreen(true, bShouldFade);
}

void UAoS_UIManager::OnLevelFinishLoad(UAoS_MapData* LoadingLevel, bool bShouldFade)
{
	DisplayLoadingScreen(false, bShouldFade);
}

void UAoS_UIManager::OnCaseAccepted(UAoS_Case* AcceptedCase)
{
	
}

void UAoS_UIManager::OnCaseActivated(UAoS_Case* ActivatedCase)
{
	
}

void UAoS_UIManager::OnCaseCompleted(UAoS_Case* CompletedCase)
{
	
}

void UAoS_UIManager::OnPartActivated(UAoS_Part* ActivatedPart)
{
	
}

void UAoS_UIManager::OnPartCompleted(UAoS_Part* CompletedPart)
{
	
}

void UAoS_UIManager::OnObjectiveActivated(UAoS_Objective* ActivatedObjective)
{
	
}

void UAoS_UIManager::OnObjectiveCompleted(UAoS_Objective* CompletedObjective)
{
	
}



