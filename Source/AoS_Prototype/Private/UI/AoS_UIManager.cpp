// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_UIManager.h"
#include "AoS_GameInstance.h"

// Subsystems
#include "Data/Cases/AoS_CaseManager.h"
#include "Media/AoS_MediaManager.h"
#include "Levels/AoS_LevelManager.h"
#include "AoS_PlayerManager.h"

// Case Data
#include "Data/Cases/AoS_CaseData.h"
#include "Data/Cases/AoS_PartData.h"
#include "Data/Cases/AoS_ObjectiveData.h"

// UI
#include "AoS_GameplayTagManager.h"
#include "AoS_NativeGameplayTagLibrary.h"
#include "UI/AoS_DialogueBox.h"
#include "UI/AoS_HUD.h"
#include "UI/AoS_UserWidget.h"
#include "UI/AoS_MoviePlayerWidget.h"
#include "UI/AoS_InteractionWidget.h"
#include "UI/AoS_CaseTitleCard.h"
#include "UI/AoS_SkipWidget.h"


#include "Controllers/AoS_PlayerController.h"
#include "Data/Maps/AoS_MenuMapData.h"
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

void UAoS_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UAoS_UIManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	
}

void UAoS_UIManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	if(InAddedTag == AOSTag_Game_State_Loading)
	{
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_UI_Screen_Loading, AOSTag_UI);
	}
	
	if(!AoSTagManager->HasParentTag(InAddedTag, AOSTag_UI)){return;}

	AddUIDelegateContainer.Find(InAddedTag)->Execute();

	Super::OnGameplayTagAdded(InAddedTag);
}

void UAoS_UIManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	if(InRemovedTag == AOSTag_Game_State_Loading)
	{
		AoSTagManager->RemoveTag(AOSTag_UI_Screen_Loading);
	}
	
	if(!AoSTagManager->HasParentTag(InRemovedTag, AOSTag_UI)){return;}

	Super::OnGameplayTagRemoved(InRemovedTag);
	
	if (InRemovedTag == AOSTag_UI_Screen_Loading)
	{
		DisplayLoadingScreen(false, true);
		return;
	}
	if (InRemovedTag == AOSTag_UI_Screen_Video)
	{
		RemoveMoviePlayerWidget();
		return;
	}
	if (InRemovedTag == AOSTag_UI_Screen_TitleCard)
	{
		RemoveCaseTitleCard();
		return;
	}
	
	RemoveAOSWidget(GetWidgetByTag(InRemovedTag));
	UIWidgetContainer.Remove(InRemovedTag);
}

void UAoS_UIManager::BindCaseManagerDelegates()
{
	/*UAoS_CaseManager* CaseManager = GameInstance->GetSubsystem<UAoS_CaseManager>();
	if (!IsValid(CaseManager)) {return;}

	// Case Bindings
	CaseManager->OnCaseAccepted.AddDynamic(this, &ThisClass::OnCaseAccepted);
	CaseManager->OnCaseActivated.AddDynamic(this, &ThisClass::OnCaseActivated);
	CaseManager->OnCaseComplete.AddDynamic(this, &ThisClass::OnCaseCompleted);

	// Part Bindings
	CaseManager->OnPartActivated.AddDynamic(this, &ThisClass::OnPartActivated);
	CaseManager->OnPartComplete.AddDynamic(this, &ThisClass::OnPartCompleted);

	// Objective Bindings
	CaseManager->OnObjectiveActivated.AddDynamic(this, &ThisClass::OnObjectiveActivated);
	CaseManager->OnObjectiveComplete.AddDynamic(this, &ThisClass::OnObjectiveCompleted);*/
}

void UAoS_UIManager::InitializeDelegates()
{
	Super::InitializeDelegates();
	
	AddMapMenuDelegate.BindUObject(this, &ThisClass::CreateMapMenu);
	AddHUDDelegate.BindUObject(this, &ThisClass::CreatePlayerHUD);
	AddLoadingScreenDelegate.BindUObject(this, &ThisClass::DisplayLoadingScreen, true, true);
	AddVideoScreenDelegate.BindUObject(this, &ThisClass::CreateMoviePlayerWidget);
	AddSystemMenuDelegate.BindUObject(this, &ThisClass::CreateSystemMenu);
}

void UAoS_UIManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();
	
	AddUIDelegateContainer.Add(AOSTag_UI_Menu_Game, AddGameMenuDelegate);
	AddUIDelegateContainer.Add(AOSTag_UI_Menu_Map, AddMapMenuDelegate);
	AddUIDelegateContainer.Add(AOSTag_UI_Menu_System, AddSystemMenuDelegate);
	AddUIDelegateContainer.Add(AOSTag_UI_Menu_Vendor, AddVendorMenuDelegate);
	AddUIDelegateContainer.Add(AOSTag_UI_HUD, AddHUDDelegate);
	AddUIDelegateContainer.Add(AOSTag_UI_Screen_Loading, AddLoadingScreenDelegate);
	AddUIDelegateContainer.Add(AOSTag_UI_Screen_Video, AddVideoScreenDelegate);
}

void UAoS_UIManager::CreatePlayerHUD()
{
	if (!IsValid(GameInstance->GetGameMode()) || IsValid(PlayerHUD)){return;}

	PlayerHUD = Cast<UAoS_HUD>(CreateAOSWidget(PlayerHUD, GameInstance->GetGameMode()->PlayerHUD_Class, AOSTag_UI_HUD));
}

void UAoS_UIManager::CreateMoviePlayerWidget()
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(GameInstance) || !IsValid(GameInstance->GetGameMode())){return;}
	
	MoviePlayerWidget = Cast<UAoS_MoviePlayerWidget>(CreateAOSWidget(MoviePlayerWidget, GameInstance->GetGameMode()->MoviePlayerWidget, AOSTag_UI_Screen_Video));
	
	if (IsValid(MoviePlayerWidget))
	{
		const UAoS_MediaManager* MediaManager = GetWorld()->GetSubsystem<UAoS_MediaManager>();
		if (IsValid(MediaManager) && IsValid(MediaManager->GetLoadedVideo()))
		{
			MoviePlayerWidget->SetMediaTexture(MediaManager->GetLoadedVideo()->MediaTexture);
			MoviePlayerWidget->SetMediaPlayer(MediaManager->GetLoadedVideo()->MediaPlayer);
			MoviePlayerWidget->SetMediaSource(MediaManager->GetLoadedVideo()->MediaSource);
			MoviePlayerWidget->AddToViewport();
			MoviePlayerWidget->PlayVideo();
		}
		else
		{
			
		}
	}
}

void UAoS_UIManager::RemoveMoviePlayerWidget()
{
	if (!IsValid(MoviePlayerWidget)){return;}
	
	MoviePlayerWidget->OnVideoStopped();
	RemoveAOSWidget(MoviePlayerWidget);
}

void UAoS_UIManager::ShowCaseTitleCard()
{
	if (!TitleCardDelayDelegate.IsBound()){return;}
#if !UE_BUILD_SHIPPING
	if (CvarDisableTitleCard.GetValueOnGameThread() == 1) {return;}
#endif
	
	TitleCardDelayDelegate.Execute();
	if (IsValid(CaseTitleCardWidget))
	{
	}
	TitleCardDelayDelegate.Unbind();
}

void UAoS_UIManager::CreateCaseTitleCard(UAoS_CaseData* InCase, bool bShouldFadeIn)
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
	RemoveAOSWidget(CaseTitleCardWidget);
	
	UAoS_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	
	CaseManager->OnCaseTitleCardComplete().Broadcast();
}

UAoS_UserWidget* UAoS_UIManager::CreateAOSWidget(UAoS_UserWidget* InWidgetPtr, TSubclassOf<UAoS_UserWidget> InWidgetClass, FGameplayTag InUITag)
{
	PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(PlayerController) || !IsValid(InWidgetClass)){return nullptr;}
	
	InWidgetPtr = CreateWidget<UAoS_UserWidget>(PlayerController, InWidgetClass);
	if (IsValid(InWidgetPtr))
	{
		InWidgetPtr->AddToViewport();
		UIWidgetContainer.Add(InUITag, InWidgetPtr);
		
		if (AoSTagManager->HasParentTag(InUITag, AOSTag_UI_Menu))
		{
			PlayerController->SetFocusedWidget(InWidgetPtr);
		}
	}
	
	return InWidgetPtr;
}

void UAoS_UIManager::RemoveAOSWidget(UAoS_UserWidget* InWidgetPtr)
{
	if (!IsValid(InWidgetPtr)){return;}
	
	InWidgetPtr->RemoveFromParent();
	InWidgetPtr = nullptr;
}

UAoS_UserWidget* UAoS_UIManager::GetWidgetByTag(const FGameplayTag InWidgetTag)
{
	for (TPair<FGameplayTag, UAoS_UserWidget*>& CurrentWidgetPair : UIWidgetContainer)
	{
		if (CurrentWidgetPair.Key == InWidgetTag)
		{
			return CurrentWidgetPair.Value;
		}
	}
	
	return nullptr;
}

void UAoS_UIManager::CreateMapMenu()
{
	const UAoS_LevelManager* LevelManager = GameInstance->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager) || IsValid(MapMenu)){return;}

	const UAoS_MenuMapData* MenuMapData = Cast<UAoS_MenuMapData>(LevelManager->GetCurrentMap());
	if (!IsValid(MenuMapData) || !IsValid(MenuMapData->MapMenuWidgetClass)){return;}

	MapMenu = CreateAOSWidget(MapMenu, MenuMapData->MapMenuWidgetClass, AOSTag_UI_Menu_Map);
}

void UAoS_UIManager::CreateSystemMenu()
{
	if (!IsValid(GameInstance->GetGameMode())){return;}

	SystemMenu = CreateAOSWidget(SystemMenu, GameInstance->GetGameMode()->SystemMenuClass, AOSTag_UI_Menu_System);
}

void UAoS_UIManager::ToggleSystemMenu()
{
	if (!IsValid(SystemMenu))
	{
	}
	else
	{
	}
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
	const AAoS_GameMode* GameMode = Cast<AAoS_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)){return;}
	
	if (bShouldDisplay)
	{
		if (GameMode->LoadingScreens.Num() > 0)
		{
			const int32 RandNumb = FMath::RandRange(0, GameMode->LoadingScreens.Num() - 1);
			if (const TSubclassOf<UAoS_UserWidget> SelectedLoadingScreen = GameMode->LoadingScreens[RandNumb])
			{
				LoadingScreen = CreateAOSWidget(LoadingScreen, SelectedLoadingScreen, AOSTag_UI_Screen_Loading);
				
				if (IsValid(LoadingScreen) && IsValid(GameInstance))
				{
					GameInstance->GetGameViewportClient()->AddViewportWidgetContent(LoadingScreen->TakeWidget());
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
				LoadingScreen = nullptr;
			}
			else
			{
				GameInstance->GetGameViewportClient()->RemoveViewportWidgetContent(LoadingScreen->TakeWidget());
				LoadingScreen = nullptr;
			}
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

void UAoS_UIManager::OnCaseAccepted(UAoS_CaseData* AcceptedCase)
{
	if (!IsValid(AcceptedCase) || !IsValid(PlayerHUD)) {return;}
	
	if (IsValid(AcceptedCase->TitleCardWidget))
	{
		PlayerHUD->ShowCaseAcceptedWidget();
		//TitleCardDelayDelegate.BindUObject(this, &ThisClass::CreateCaseTitleCard, AcceptedCase, GameInstance->GetPreviousPlayerMode() == EPlayerMode::PM_ExplorationMode);
	}
}

void UAoS_UIManager::OnCaseActivated(UAoS_CaseData* ActivatedCase)
{
	
}

void UAoS_UIManager::OnCaseCompleted(UAoS_CaseData* CompletedCase)
{
	
}

void UAoS_UIManager::OnPartActivated(UAoS_PartData* ActivatedPart)
{
	
}

void UAoS_UIManager::OnPartCompleted(UAoS_PartData* CompletedPart)
{
	
}

void UAoS_UIManager::OnObjectiveActivated(UAoS_ObjectiveData* ActivatedObjective)
{
	
}

void UAoS_UIManager::OnObjectiveCompleted(UAoS_ObjectiveData* CompletedObjective)
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



