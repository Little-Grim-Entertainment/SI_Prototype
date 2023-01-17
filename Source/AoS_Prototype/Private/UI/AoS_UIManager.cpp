// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"

// Subsystems
#include "Data/Cases/AoS_CaseManager.h"
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
#include "UI/AoS_InteractionWidget.h"
#include "UI/AoS_CaseTitleCard.h"
#include "UI/AoS_SkipWidget.h"


#include "Controllers/AoS_PlayerController.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "GameModes/AoS_GameMode.h"
#include "MediaAssets/Public/MediaPlayer.h"


#if !UE_BUILD_SHIPPING
static TAutoConsoleVariable<int32> CvarDisableTitleCard(
	TEXT("CheatDisableTitleCards"),
	0,
	TEXT("Disables the titles cards after accepting a case.\n")
	TEXT("<=0: enabled\n")
	TEXT("  1: disabled\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);
#endif

UAoS_UIManager::UAoS_UIManager()
{

}

void UAoS_UIManager::OnGameInstanceInit()
{
	Super::OnGameInstanceInit();
	
	BindCaseManagerDelegates();
}

void UAoS_UIManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	
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


void UAoS_UIManager::OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode)
{
	Super::OnPlayerModeChanged(NewPlayerMode, InPreviousPlayerMode);

	switch (InPreviousPlayerMode)
	{
		case EPlayerMode::PM_ExplorationMode:
		{
			RemovePlayerHUD();
			break;
		}
		case EPlayerMode::PM_LevelLoadingMode:
		{
			if(NewPlayerMode != EPlayerMode::PM_VideoMode)
			{
				DisplayLoadingScreen(false, true);
			}
			else
			{
				LoadingScreenFadeDelay();
			}
			break;
		}
		case EPlayerMode::PM_ObservationMode:
		{
			if (IsValid(PlayerHUD))
			{
				PlayerHUD->GetReticle()->SetVisibility(ESlateVisibility::Hidden);
			}
			break;
		}
		case EPlayerMode::PM_DialogueMode:
			{
				HideDialogueBox();
				break;
			}
		case EPlayerMode::PM_VideoMode:
		{
			RemoveMoviePlayerWidget();
			break;
		}
		case EPlayerMode::PM_MainMenuMode:
		{
			RemoveMainMenu();
			break;
		}
		case EPlayerMode::PM_InterrogationMode:
		{
			HideDialogueBox();
			break;
		}
		default:
		{
			break;
		}
	}
		
	switch (NewPlayerMode)
	{
		case EPlayerMode::PM_ExplorationMode:
		{
			CreatePlayerHUD();
			SetMenuMode(false);
			break;
		}
		case EPlayerMode::PM_MainMenuMode:
		{
			CreateMainMenu();
			SetMenuMode(true, MainMenu);
			break;	
		}
		case EPlayerMode::PM_CinematicMode:
		{
			SetMenuMode(false);
			break;	
		}
		case EPlayerMode::PM_VideoMode:
		{
			HideActiveInteractionWidgets();
			CreateMoviePlayerWidget();
			DisplayLoadingScreen(false, false);
			SetMenuMode(false, MoviePlayerWidget);
			break;
		}
		case EPlayerMode::PM_LevelLoadingMode:
		{
			HideActiveInteractionWidgets();
			DisplayLoadingScreen(true, true);
			break;	
		}
		case EPlayerMode::PM_ObservationMode:
		{
			CreatePlayerHUD();
			if (IsValid(PlayerHUD))
			{
				PlayerHUD->GetReticle()->SetVisibility(ESlateVisibility::Visible);
			}
			break;
		}
		case EPlayerMode::PM_DialogueMode:
		{
			CreatePlayerHUD();
			DisplayDialogueBox();
			break;
		}
		case EPlayerMode::PM_InterrogationMode:
		{
			break;
		}
		case EPlayerMode::PM_TitleCardMode:
		{
			break;
		}
		default:
		{
			CreatePlayerHUD();
			SetMenuMode(false);
			break;
		}
	}
}

void UAoS_UIManager::CreatePlayerHUD()
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(GameInstance) || !IsValid(GameInstance->GetGameMode())){return;}
	
	PlayerHUD =	CreateWidget<UAoS_HUD>(GameInstance, GameInstance->GetGameMode()->PlayerHUD_Class);
	if (IsValid(PlayerHUD))
	{
		PlayerHUD->AddToViewport();
	}
}

void UAoS_UIManager::CreateMoviePlayerWidget()
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(GameInstance) || !IsValid(GameInstance->GetGameMode())){return;}
	
	MoviePlayerWidget =	CreateWidget<UAoS_MoviePlayerWidget>(GameInstance, GameInstance->GetGameMode()->MoviePlayerWidget);
	if (IsValid(MoviePlayerWidget))
	{
		const UAoS_CinematicsManager* CinematicsManager = GetWorld()->GetSubsystem<UAoS_CinematicsManager>();
		if (IsValid(CinematicsManager) && IsValid(CinematicsManager->GetLoadedVideo()))
		{
			MoviePlayerWidget->SetMediaTexture(CinematicsManager->GetLoadedVideo()->MediaTexture);
			MoviePlayerWidget->SetMediaPlayer(CinematicsManager->GetLoadedVideo()->MediaPlayer);
			MoviePlayerWidget->SetMediaSource(CinematicsManager->GetLoadedVideo()->MediaSource);
			MoviePlayerWidget->AddToViewport();
			MoviePlayerWidget->PlayVideo();
		}
		else
		{
			GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
		}
	}
}

void UAoS_UIManager::RemoveMoviePlayerWidget()
{
	if (!IsValid(MoviePlayerWidget)){return;}
	
	MoviePlayerWidget->OnVideoStopped();
	MoviePlayerWidget = nullptr;
}

void UAoS_UIManager::ShowCaseTitleCard()
{
	if (!TitleCardDelayDelegate.IsBound() || CvarDisableTitleCard.GetValueOnGameThread() == 1) {return;}
	
	TitleCardDelayDelegate.Execute();
	if (IsValid(CaseTitleCardWidget))
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_TitleCardMode);
	}
	TitleCardDelayDelegate.Unbind();
}

void UAoS_UIManager::CreateCaseTitleCard(UAoS_Case* InCase, bool bShouldFadeIn)
{
	if (!IsValid(InCase)) {return;}

	CaseTitleCardWidget = CreateWidget<UAoS_CaseTitleCard>(GetWorld()->GetFirstPlayerController(), InCase->TitleCardWidget);
	if (IsValid(CaseTitleCardWidget))
	{
		CaseTitleCardWidget->AddToViewport();
		CaseTitleCardWidget->ShowTitleCard(InCase->CaseName, InCase->TitleCardBackground, InCase->TitleCardMusic, InCase->TitleCardLength, bShouldFadeIn);
	}
}

void UAoS_UIManager::RemoveCaseTitleCard()
{
	CaseTitleCardWidget->RemoveFromParent();
	CaseTitleCardWidget = nullptr;
	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
	GameInstance->GetCaseManager()->OnCaseTitleCardComplete.Broadcast();
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
	if (!IsValid(PlayerController) || !IsValid(GameInstance->GetGameMode())){return;}
	
	MainMenu =	CreateWidget<UAoS_UserWidget>(PlayerController,  GameInstance->GetGameMode()->MainMenuClass);
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

UAoS_SkipWidget* UAoS_UIManager::CreateSkipWidget()
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(PlayerController) || !IsValid(GameInstance->GetGameMode())){return nullptr;}
	
	SkipWidget = CreateWidget<UAoS_SkipWidget>(PlayerController,  GameInstance->GetGameMode()->SkipWidget);
	if (IsValid(SkipWidget))
	{
		SkipWidget->AddToViewport();
	}
	return SkipWidget;
}

void UAoS_UIManager::RemoveSkipWidget()
{
	if (!IsValid(SkipWidget)){return;}
	
	SkipWidget->RemoveFromParent();
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

void UAoS_UIManager::AddActiveInteractionWidget(UAoS_InteractionWidget* InInteractionWidget)
{
	if (IsValid(InInteractionWidget))
	{
		ActiveInteractionWidgets.AddUnique(InInteractionWidget);
	}
}

void UAoS_UIManager::RemoveActiveInteractionWidget(UAoS_InteractionWidget* InInteractionWidget)
{
	if (IsValid(InInteractionWidget))
	{
		ActiveInteractionWidgets.Remove(InInteractionWidget);
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
					SetMenuMode(false, LoadingScreen);
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
			SetMenuMode(false);
		}
	}
}

void UAoS_UIManager::DisplayDialogueBox()
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())){return;}

	PlayerHUD->GetDialogueBox()->RefreshDialogueBox();
	PlayerHUD->GetDialogueBox()->SetVisibility(ESlateVisibility::Visible);
}

void UAoS_UIManager::HideDialogueBox()
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())) { return; }

	PlayerHUD->GetDialogueBox()->SetVisibility(ESlateVisibility::Hidden);
}

void UAoS_UIManager::HideActiveInteractionWidgets()
{
	if (ActiveInteractionWidgets.Num() <= 0){return;}
	for (UAoS_InteractionWidget* CurrentInteractionWidget : ActiveInteractionWidgets)
	{
		if (IsValid(CurrentInteractionWidget))
		{
			CurrentInteractionWidget->HideWidget();
		}
	}
	
	ActiveInteractionWidgets.Empty();
}

void UAoS_UIManager::LoadingScreenFadeDelay()
{
	LoadingScreenFadeDelayDelegate.BindUObject(this, &UAoS_UIManager::DisplayLoadingScreen, false, false);
	GetWorld()->GetTimerManager().SetTimer(LoadingScreenFadeDelayHandle, LoadingScreenFadeDelayDelegate, 20.0f, false);
}

void UAoS_UIManager::OnCaseAccepted(UAoS_Case* AcceptedCase)
{
	if (!IsValid(AcceptedCase) || !IsValid(PlayerHUD)) {return;}
	
	if (IsValid(AcceptedCase->TitleCardWidget))
	{
		PlayerHUD->ShowCaseAcceptedWidget();
		TitleCardDelayDelegate.BindUObject(this, &ThisClass::CreateCaseTitleCard, AcceptedCase, GameInstance->GetPreviousPlayerMode() == EPlayerMode::PM_ExplorationMode);
	}
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

TArray<UAoS_InteractionWidget*>& UAoS_UIManager::GetActiveInteractionWidgets()
{
	return ActiveInteractionWidgets;
}

UAoS_MoviePlayerWidget* UAoS_UIManager::GetMoviePlayerWidget() const
{
	return MoviePlayerWidget;
}

UAoS_HUD* UAoS_UIManager::GetPlayerHUD()
{
	return PlayerHUD;
}



