// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_UIManager.h"
#include "SI_GameInstance.h"

// Subsystems
#include "GameplayTags/SI_GameplayTagManager.h"
#include "GameplayTags/SI_GameplayTagTypes.h"
#include "Cases/SI_CaseManager.h"
#include "Media/SI_MediaManager.h"
#include "Levels/SI_LevelManager.h"

// Case Data
#include "Cases/Data/SI_CaseData.h"

// UI
#include "UI/SI_DialogueBox.h"
#include "UI/SI_HUD.h"
#include "UI/SI_UserWidget.h"
#include "UI/SI_MoviePlayerWidget.h"
#include "UI/SI_InteractionWidget.h"
#include "UI/SI_CaseTitleCard.h"
#include "UI/SI_SkipWidget.h"

#include "Controllers/SI_PlayerController.h"
#include "Levels/Data/SI_MenuMapData.h"
#include "Media/Data/SI_VideoDataAsset.h"
#include "GameModes/SI_GameMode.h"

#if !UE_BUILD_SHIPPING
static TAutoConsoleVariable<int32> CvarDisableTitleCard(
	TEXT("CheatDisableTitleCards"),
	0,
	TEXT("Disables the titles cards after accepting a case.\n")
	TEXT("<=0: enabled\n")
	TEXT("  1: disabled\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);
#endif

USI_UIManager::USI_UIManager()
{
	bUIEnabled = true;
}

void USI_UIManager::OnGameInstanceInit()
{
	Super::OnGameInstanceInit();
	
}

void USI_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);	
}
//Called from listener of GameplayTagManager OnTagAddedDelegate.Broadcast() in AddNewGameplayTag()
void USI_UIManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{
	if(!bUIEnabled){return;}
	
	Super::OnGameplayTagAdded(InAddedTag);

	CurrentUITag = InAddedTag;
	
	if(InAddedTag == SITag_Game_State_Loading)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_UI_Screen_Loading, SITag_UI);
	}

	if(InAddedTag == SITag_Media_Video)
	{
		SITagManager->AddNewGameplayTag_Internal(SITag_UI_Screen_Video);
	}
	
	if(!SITagManager->HasParentTag(InAddedTag, SITag_UI)){return;}
	
	if(SITagManager->HasParentTag(InAddedTag, SITag_UI_HUD_QuickAction))
	{
		AddUIDelegateContainer.Find(SITag_UI_HUD_QuickAction)->Execute();

		if(InAddedTag != SITag_UI_HUD_QuickAction_GadgetsOne)
		{
			SITagManager->RemoveTag_Internal(SITag_UI_HUD_QuickAction_GadgetsOne);
		}
		return;
	}

	const FSimpleDelegate* FoundDelegate = AddUIDelegateContainer.Find(InAddedTag);
	if(FoundDelegate)
	{
		FoundDelegate->Execute();
	}
}	
//Called from listener of GameplayTagManager OnTagRemovedDelegate.Broadcast() in RemoveTag()
void USI_UIManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload)
{
	if(!bUIEnabled){return;}
	
	Super::OnGameplayTagRemoved(InRemovedTag);

	if(InRemovedTag == SITag_Game_State_Loading)
	{
		SITagManager->RemoveTag_Internal(SITag_UI_Screen_Loading);
	}

	if(InRemovedTag == SITag_Media_Video)
	{
		SITagManager->RemoveTag_Internal(SITag_UI_Screen_Video);
	}
	
	if(!SITagManager->HasParentTag(InRemovedTag, SITag_UI)){return;}
	
	if (InRemovedTag == SITag_UI_Screen_Loading)
	{
		DisplayLoadingScreen(false, true);
		return;
	}
	if (InRemovedTag == SITag_UI_Screen_Video)
	{
		RemoveMoviePlayerWidget();
		return;
	}
	if (InRemovedTag == SITag_UI_Screen_TitleCard)
	{
		RemoveCaseTitleCard();
		return;
	}

	if (InRemovedTag == SITag_UI_HUD)
	{
		ShowPlayerHUD(false);
		return;
	}

	if (InRemovedTag == SITag_UI_HUD_Dialogue)
	{
		HideDialogueBox();
		return;
	}

	if (InRemovedTag == SITag_UI_Menu_Map)
	{
		ShowMapMenu(false);
		return;
	}

	if(InRemovedTag != SITag_UI_HUD_QuickAction_GadgetsOne && SITagManager->HasParentTag(InRemovedTag, SITag_UI_HUD_QuickAction))
	{
		SITagManager->AddNewGameplayTag_Internal(SITag_UI_HUD_QuickAction_GadgetsOne);
	}
	
	RemoveSIWidget(GetActiveUIWidgetByTag<USI_UserWidget>(InRemovedTag));
}

void USI_UIManager::DelayWidgetCreation(const FSimpleDelegate& InDelegate)
{
	WidgetCreationDelayDelegates.Add(InDelegate);
}

void USI_UIManager::ShowPlayerHUD(bool bShouldShow)
{
	USI_HUD* PlayerHUD = GetActiveUIWidget<USI_HUD>();
	if(!IsValid(PlayerHUD) && bShouldShow)
	{	
		CreatePlayerHUD();
	}
	else if(IsValid(PlayerHUD) && !bShouldShow)
	{
		PlayerHUD->RemoveFromParent();
	}
}

void USI_UIManager::ShowMapMenu(bool bShouldShow)
{
	USI_UserWidget* MapMenu = GetActiveUIWidgetByTag<USI_UserWidget>(SITag_UI_Menu_Map);
	if(!IsValid(MapMenu) && bShouldShow)
	{
		CreateMapMenu();
	}
	else if(IsValid(MapMenu) && !bShouldShow)
	{
		MapMenu->RemoveFromParent();
		MapMenu = nullptr;
	}
}

void USI_UIManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();

	FSimpleDelegate AddGameMenuDelegate;
	AddGameMenuDelegate.BindUObject(this, &ThisClass::CreateMapMenu);
	AddUIDelegateContainer.Add(SITag_UI_Menu_Game, AddGameMenuDelegate);

	FSimpleDelegate AddMapMenuDelegate;
	AddMapMenuDelegate.BindUObject(this, &ThisClass::CreateMapMenu);
	AddUIDelegateContainer.Add(SITag_UI_Menu_Map, AddMapMenuDelegate);

	FSimpleDelegate AddSystemMenuDelegate;
	AddSystemMenuDelegate.BindUObject(this, &ThisClass::ToggleSystemMenu);
	AddUIDelegateContainer.Add(SITag_UI_Menu_System, AddSystemMenuDelegate);

	FSimpleDelegate AddHUDDelegate;
	AddHUDDelegate.BindUObject(this, &ThisClass::CreatePlayerHUD);
	AddUIDelegateContainer.Add(SITag_UI_HUD, AddHUDDelegate);

	FSimpleDelegate UpdateQuickActionDelegate;
	UpdateQuickActionDelegate.BindUObject(this, &ThisClass::UpdateQuickActionWidget);
	AddUIDelegateContainer.Add(SITag_UI_HUD_QuickAction, UpdateQuickActionDelegate);

	FSimpleDelegate AddLoadingScreenDelegate;
	AddLoadingScreenDelegate.BindUObject(this, &ThisClass::DisplayLoadingScreen, true, true);
	AddUIDelegateContainer.Add(SITag_UI_Screen_Loading, AddLoadingScreenDelegate);

	FSimpleDelegate AddVideoScreenDelegate;
	AddVideoScreenDelegate.BindUObject(this, &ThisClass::CreateMoviePlayerWidget);
	AddUIDelegateContainer.Add(SITag_UI_Screen_Video, AddVideoScreenDelegate);

	FSimpleDelegate AddDialogueBoxDelegate;
	AddDialogueBoxDelegate.BindUObject(this, &ThisClass::DisplayDialogueBox);
	AddUIDelegateContainer.Add(SITag_UI_HUD_Dialogue, AddDialogueBoxDelegate);
	
	/*
	FSimpleDelegate AddVendorMenuDelegate;
	AddUIDelegateContainer.Add(SITag_UI_Menu_Vendor, AddVendorMenuDelegate);
	*/
}

USI_UserWidget* USI_UIManager::CreateSIWidget_Internal(TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName)
{
	USI_UserWidget* NewUserWidget = CreateWidget<USI_UserWidget>(GetWorld()->GetFirstPlayerController(), UserWidgetClass, WidgetName);
	return NewUserWidget;
}

void USI_UIManager::CreatePlayerHUD()
{
	if (!IsValid(GameInstance->GetGameMode())){return;}

	USI_HUD* PlayerHUD = CreateSIWidget<USI_HUD>(SITag_UI_HUD, GameInstance->GetGameMode()->PlayerHUD_Class);
	if(!IsValid(PlayerHUD))
	{
		FSimpleDelegate LoadingScreenDelayDelegate;
		LoadingScreenDelayDelegate.BindUObject(this, &ThisClass::CreatePlayerHUD);
		DelayWidgetCreation(LoadingScreenDelayDelegate);
		return;
	}
	
	PlayerHUD->AddToViewport();
}

void USI_UIManager::CreateMoviePlayerWidget()
{
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(GameInstance) || !IsValid(GameInstance->GetGameMode())){return;}

	USI_MoviePlayerWidget* MoviePlayerWidget = CreateSIWidget<USI_MoviePlayerWidget>(SITag_UI_Screen_Video, GameInstance->GetGameMode()->MoviePlayerWidget);
	
	if (!IsValid(MoviePlayerWidget))
	{
		FSimpleDelegate MoviePlayerDelayDelegate;
		//TODO: Fix this JEFF!!!! Possible Infinite loop
		MoviePlayerDelayDelegate.BindUObject(this, &ThisClass::CreateMoviePlayerWidget);
		DelayWidgetCreation(MoviePlayerDelayDelegate);
		return;
	}

	const USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>();
	if (IsValid(MediaManager) && IsValid(MediaManager->GetLoadedVideo()))
	{
		MoviePlayerWidget->SetMediaTexture(MediaManager->GetLoadedVideo()->MediaTexture);
		MoviePlayerWidget->SetMediaPlayer(MediaManager->GetLoadedVideo()->MediaPlayer);
		MoviePlayerWidget->SetMediaSource(MediaManager->GetLoadedVideo()->MediaSource);
		MoviePlayerWidget->AddToViewport();
		MoviePlayerWidget->PlayVideo();
	}
}

void USI_UIManager::RemoveMoviePlayerWidget()
{
	USI_MoviePlayerWidget* MoviePlayerWidget = GetActiveUIWidget<USI_MoviePlayerWidget>();
	if (!IsValid(MoviePlayerWidget)){return;}
	
	MoviePlayerWidget->OnVideoStopped();
	RemoveSIWidget(MoviePlayerWidget);
}

void USI_UIManager::ShowCaseTitleCard()
{
	if (!TitleCardDelayDelegate.IsBound()){return;}
#if !UE_BUILD_SHIPPING
	if (CvarDisableTitleCard.GetValueOnGameThread() == 1) {return;}
#endif
	
	TitleCardDelayDelegate.Execute();
	TitleCardDelayDelegate.Unbind();
}

void USI_UIManager::CreateCaseTitleCard(USI_CaseData* InCase, bool bShouldFadeIn)
{
	if (!IsValid(InCase)) {return;}

	USI_CaseTitleCard* CaseTitleCardWidget = CreateSIWidget<USI_CaseTitleCard>(SITag_UI_Screen_TitleCard, InCase->TitleCardWidget);
	if (!IsValid(CaseTitleCardWidget))
	{
		FSimpleDelegate CaseTitleCardDelayDelegate;
		CaseTitleCardDelayDelegate.BindUObject(this, &ThisClass::CreateCaseTitleCard, InCase, bShouldFadeIn);
		DelayWidgetCreation(CaseTitleCardDelayDelegate);
		return;
	}

	CaseTitleCardWidget->AddToViewport();
	CaseTitleCardWidget->ShowTitleCard(InCase->TitleCardBackground, InCase->TitleCardMusic, InCase->TitleCardLength, bShouldFadeIn);
}

void USI_UIManager::RemoveCaseTitleCard()
{
	USI_CaseTitleCard* CaseTitleCardWidget = GetActiveUIWidget<USI_CaseTitleCard>();
	RemoveSIWidget(CaseTitleCardWidget);
	
	USI_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	
	CaseManager->OnCaseTitleCardComplete().Broadcast();
}

void USI_UIManager::RemoveSIWidget(USI_UserWidget* InWidgetPtr)
{
	if (!IsValid(InWidgetPtr)){return;}

	for(const TPair<FGameplayTag, TSoftObjectPtr<USI_UserWidget>> CurrentWidget : ActiveUIWidgetsArray)
	{
		if(InWidgetPtr == CurrentWidget.Value.Get())
		{
			ActiveUIWidgetsArray.Remove(CurrentWidget.Key);
			break;
		}
	}
	
	InWidgetPtr->RemoveFromParent();
	InWidgetPtr = nullptr;
}

void USI_UIManager::CreateMapMenu()
{
	USI_LevelManager* LevelManager = GameInstance->GetSubsystem<USI_LevelManager>();
	if (!IsValid(LevelManager)){return;}

	const USI_MenuMapData* MenuMapData = Cast<USI_MenuMapData>(LevelManager->GetCurrentMap());
	if (!IsValid(MenuMapData) || !IsValid(MenuMapData->MapMenuWidgetClass)){return;}

	USI_UserWidget* MapMenu = CreateSIWidget<USI_UserWidget>(SITag_UI_Menu_Map, MenuMapData->MapMenuWidgetClass);
	if(!IsValid(MapMenu))
	{
		FSimpleDelegate MapMenuDelayDelegate;
		MapMenuDelayDelegate.BindUObject(this, &ThisClass::CreateMapMenu);
		DelayWidgetCreation(MapMenuDelayDelegate);
		return;
	}
	MapMenu->AddToViewport();
}

void USI_UIManager::CreateSystemMenu()
{
	if (!IsValid(GameInstance->GetGameMode())){return;}

	USI_UserWidget* SystemMenu = CreateSIWidget<USI_UserWidget>(SITag_UI_Menu_System, GameInstance->GetGameMode()->SystemMenuClass);
	if(!IsValid(SystemMenu))
	{
		FSimpleDelegate SystemMenuDelayDelegate;
		SystemMenuDelayDelegate.BindUObject(this, &ThisClass::CreateSystemMenu);
		DelayWidgetCreation(SystemMenuDelayDelegate);
		return;
	}
	
	SystemMenu->AddToViewport();
}

void USI_UIManager::ToggleSystemMenu()
{
	USI_UserWidget* SystemMenu = GetActiveUIWidgetByTag<USI_UserWidget>(SITag_UI_Menu_System);
	if (!IsValid(SystemMenu))
	{
		CreateSystemMenu();
	}
	else
	{
		SystemMenu->RemoveFromParent();
	}
}

void USI_UIManager::CreateSkipWidget()
{
	if (!IsValid(GameInstance->GetGameMode())){return;}
	
	USI_SkipWidget* SkipWidget = CreateSIWidget<USI_SkipWidget>(SITag_UI_Prompt_Skip, GameInstance->GetGameMode()->SkipWidget);
	if (!IsValid(SkipWidget))
	{
		FSimpleDelegate SkipWidgetDelayDelegate;
		SkipWidgetDelayDelegate.BindUObject(this, &ThisClass::CreateSkipWidget);
		DelayWidgetCreation(SkipWidgetDelayDelegate);
		return;
	}
	
	SkipWidget->AddToViewport();
}

USI_UserWidget* USI_UIManager::GetSIWidgetByTag(const FGameplayTag& InWidgetTag)
{
	return GetActiveUIWidgetByTag<USI_UserWidget>(InWidgetTag);
}

void USI_UIManager::AddActiveInteractionWidget(USI_InteractionWidget* InInteractionWidget)
{
	if (IsValid(InInteractionWidget))
	{
		ActiveInteractionWidgets.AddUnique(InInteractionWidget);
	}
}

void USI_UIManager::RemoveActiveInteractionWidget(USI_InteractionWidget* InInteractionWidget)
{
	if (IsValid(InInteractionWidget))
	{
		ActiveInteractionWidgets.Remove(InInteractionWidget);
	}
}

void USI_UIManager::UpdateQuickActionWidget()
{
	USI_HUD* PlayerHUD = GetActiveUIWidget<USI_HUD>();
	if(!IsValid(PlayerHUD)){return;}
	
	PlayerHUD->UpdateQuickActionWidget(CurrentUITag);
}

FGameplayTag USI_UIManager::GetQuickActionAbilityTag(const FGameplayTag& InQuickActionTag)
{
	const USI_HUD* PlayerHUD = GetActiveUIWidget<USI_HUD>();
	if(!IsValid(PlayerHUD)){return SITag_None;}
	
	return PlayerHUD->GetQuickActionAbilityTag(InQuickActionTag);
}

void USI_UIManager::DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade)
{
	const ASI_GameMode* GameMode = Cast<ASI_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)){return;}

	USI_UserWidget* LoadingScreen = nullptr;
	
	if (bShouldDisplay)
	{
		if (GameMode->LoadingScreens.Num() > 0)
		{
			const int32 RandNumb = FMath::RandRange(0, GameMode->LoadingScreens.Num() - 1);
			if (const TSubclassOf<USI_UserWidget> SelectedLoadingScreen = GameMode->LoadingScreens[RandNumb])
			{
				LoadingScreen = CreateSIWidget<USI_UserWidget>(SITag_UI_Screen_Loading, SelectedLoadingScreen);
				if(!IsValid(LoadingScreen))
				{
					FSimpleDelegate LoadingScreenDelayDelegate;
					LoadingScreenDelayDelegate.BindUObject(this, &ThisClass::DisplayLoadingScreen, bShouldDisplay, bShouldFade);
					DelayWidgetCreation(LoadingScreenDelayDelegate);
					return;
				}

				if(IsValid(GameInstance))
				{
					GameInstance->GetGameViewportClient()->AddViewportWidgetContent(LoadingScreen->TakeWidget());
				}
			}
		}
	}
	else
	{
		LoadingScreen = GetActiveUIWidgetByTag<USI_UserWidget>(SITag_UI_Screen_Loading);
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

void USI_UIManager::DisplayDialogueBox()
{
	USI_HUD* PlayerHUD = GetActiveUIWidget<USI_HUD>();
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())){return;}

	USI_DialogueBox* DialogueBox = PlayerHUD->GetDialogueBox();
	if(!IsValid(DialogueBox)) {return;}
	
	DialogueBox->RefreshDialogueBox();
	DialogueBox->SetVisibility(ESlateVisibility::Visible);
}

void USI_UIManager::HideDialogueBox()
{
	USI_HUD* PlayerHUD = GetActiveUIWidget<USI_HUD>();
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())) { return; }

	PlayerHUD->GetDialogueBox()->SetVisibility(ESlateVisibility::Hidden);
}

void USI_UIManager::HideActiveInteractionWidgets()
{
	if (ActiveInteractionWidgets.Num() <= 0){return;}
	for (USI_InteractionWidget* CurrentInteractionWidget : ActiveInteractionWidgets)
	{
		if (IsValid(CurrentInteractionWidget))
		{
			CurrentInteractionWidget->HideWidget();
		}
	}
	
	ActiveInteractionWidgets.Empty();
}

void USI_UIManager::LoadingScreenFadeDelay()
{
	LoadingScreenFadeDelayDelegate.BindUObject(this, &USI_UIManager::DisplayLoadingScreen, false, false);
	GetWorld()->GetTimerManager().SetTimer(LoadingScreenFadeDelayHandle, LoadingScreenFadeDelayDelegate, 20.0f, false);
}

void USI_UIManager::OnCaseAccepted(USI_CaseData* AcceptedCase)
{
	USI_HUD* PlayerHUD = GetActiveUIWidget<USI_HUD>();
	if (!IsValid(AcceptedCase) || !IsValid(PlayerHUD)) {return;}
	
	if (IsValid(AcceptedCase->TitleCardWidget))
	{
		PlayerHUD->ShowCaseAcceptedWidget();
		//TitleCardDelayDelegate.BindUObject(this, &ThisClass::CreateCaseTitleCard, AcceptedCase, GameInstance->GetPreviousPlayerMode() == EPlayerMode::PM_ExplorationMode);
	}
}

void USI_UIManager::OnCaseActivated(USI_CaseData* ActivatedCase)
{
	
}

void USI_UIManager::OnCaseCompleted(USI_CaseData* CompletedCase)
{
	
}

void USI_UIManager::OnPartActivated(USI_PartData* ActivatedPart)
{
	
}

void USI_UIManager::OnPartCompleted(USI_PartData* CompletedPart)
{
	
}

void USI_UIManager::OnPlayerStart()
{
	Super::OnPlayerStart();

	for(FSimpleDelegate& CurrentDelegate : WidgetCreationDelayDelegates)
	{
		if(CurrentDelegate.IsBound())
		{
			CurrentDelegate.Execute();
			CurrentDelegate.Unbind();
		}
	}
	WidgetCreationDelayDelegates.Empty();
}

void USI_UIManager::OnObjectiveActivated(USI_ObjectiveData* ActivatedObjective)
{
	
}

void USI_UIManager::OnObjectiveCompleted(USI_ObjectiveData* CompletedObjective)
{
	
}

TArray<USI_InteractionWidget*>& USI_UIManager::GetActiveInteractionWidgets()
{
	return ActiveInteractionWidgets;
}

USI_MoviePlayerWidget* USI_UIManager::GetMoviePlayerWidget() 
{
	return GetActiveUIWidget<USI_MoviePlayerWidget>();
}

USI_HUD* USI_UIManager::GetPlayerHUD()
{
	return GetActiveUIWidget<USI_HUD>();
}

void USI_UIManager::SetUIEnabled(bool bInShouldEnable)
{
	bUIEnabled = bInShouldEnable;
}
