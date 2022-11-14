// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"

// Subsystems
#include "Data/Cases/AoS_CaseManager.h"
#include "Levels/AoS_LevelManager.h"
#include "Dialogue/AoS_DialogueManager.h"

// Case Data
#include "Data/Cases/AoS_Case.h"
#include "Data/Cases/AoS_Part.h"
#include "Data/Cases/AoS_Objective.h"

// UI
#include "UI/AoS_DialogueBox.h"
#include "UI/AoS_HUD.h"
#include "UI/AoS_UserWidget.h"

#include "Controllers/AoS_PlayerController.h"


UAoS_UIManager::UAoS_UIManager()
{

}

void UAoS_UIManager::OnGameInstanceInit()
{
	Super::OnGameInstanceInit();
	
	BindLevelManagerDelegates();
	BindCaseManagerDelegates();
}

void UAoS_UIManager::BindDialogueManagerDelegates(UAoS_DialogueManager* InDialogueManager)
{
	InDialogueManager->GetOnBeginDialogue().AddDynamic(this, &ThisClass::OnBeginDialogue);
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
	
	switch (NewPlayerMode)
	{
		case EPlayerMode::PM_ExplorationMode:
		{
			if(!IsValid(PlayerHUD))
			{
				CreatePlayerHUD();	
			}
			else
			{
				ShowPlayerHUD(true);
			}
			break;	
		}
		case EPlayerMode::PM_GameMenuMode:
		{
			
			break;	
		}
		case EPlayerMode::PM_CinematicMode:
		{
			if (IsValid(PlayerHUD))
			{
				ShowPlayerHUD(false);
			}
			break;	
		}
		case EPlayerMode::PM_DialogueMode:
		{
				
			break;	
		}
		case EPlayerMode::PM_InspectionMode:
		{
			break;	
		}
		case EPlayerMode::PM_InterrogationMode:
		{
			break;	
		}
		case EPlayerMode::PM_ObservationMode:
		{
			break;	
		}
		case EPlayerMode::PM_VendorMode:
		{
			break;	
		}
		case EPlayerMode::PM_LevelLoadingMode:
		{
			if (IsValid(PlayerHUD))
			{
				ShowPlayerHUD(false);
			}
			break;	
		}
		default:
		{
			break;
		}
	}
}

void UAoS_UIManager::CreatePlayerHUD()
{
	PlayerController = GameInstance->GetAOSPlayerController();
	if (!IsValid(PlayerController)){return;}
	
	PlayerHUD =	CreateWidget<UAoS_HUD>(PlayerController, PlayerController->GetPlayerHUDClass());
	if (IsValid(PlayerHUD))
	{
		PlayerHUD->AddToViewport();
	}
}

void UAoS_UIManager::ShowPlayerHUD(bool bShouldShow)
{
	if(!IsValid(PlayerHUD)){return;}

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

void UAoS_UIManager::DisplayDialogueBox(UDlgContext* DlgContext)
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())){return;}
	
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

void UAoS_UIManager::OnBeginDialogue(UDlgDialogue* DlgDialogue)
{
	
}



