// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_QuickActionWidget.h"
#include "TimerManager.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_UIManager.generated.h"

class USI_SkipWidget;
class USI_InteractionWidget;
class USI_InteractionPrompt;
class UMediaPlayer;
class USI_MoviePlayerWidget;
class USI_DialogueManager;
class USI_ObjectiveData;
class USI_PartData;
class USI_CaseData;
class ASI_PlayerController;
class USI_HUD;
class USI_UserWidget;
class USI_MapData;
class USI_CaseTitleCard;

enum class EPlayerMode : uint8;

DECLARE_LOG_CATEGORY_EXTERN(LogSI_UIManager, Log, All);

UCLASS()
class SI_PROTOTYPE_API USI_UIManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle the creation and display of the various UI in Ace of Spades
	
public:

	USI_UIManager();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreatePlayerHUD();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateMoviePlayerWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveMoviePlayerWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowCaseTitleCard();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateCaseTitleCard(USI_CaseData* InCase, bool bShouldFadeIn = false);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveCaseTitleCard();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateSIWidget(USI_UserWidget* InWidgetPtr, TSubclassOf<USI_UserWidget> InWidgetClass, FGameplayTag InUITag);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveSIWidget(USI_UserWidget* InWidgetPtr);
	UFUNCTION(BlueprintCallable, Category = "UI")
	USI_UserWidget* GetWidgetByTag(const FGameplayTag InWidgetTag);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateMapMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateSystemMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ToggleSystemMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	USI_SkipWidget* CreateSkipWidget();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade);
	
	// Case Manager Delegates
	UFUNCTION()
	void OnCaseAccepted(USI_CaseData* AcceptedCase);
	UFUNCTION()
	void OnCaseActivated(USI_CaseData* ActivatedCase);
	UFUNCTION()
	void OnCaseCompleted(USI_CaseData* CompletedCase);

	UFUNCTION()
	void OnPartActivated(USI_PartData* ActivatedPart);
	UFUNCTION()
	void OnPartCompleted(USI_PartData* CompletedPart);
	
	UFUNCTION()
	void AddActiveInteractionWidget(USI_InteractionWidget* InInteractionWidget);
	UFUNCTION()
	void RemoveActiveInteractionWidget(USI_InteractionWidget* InInteractionWidget);

	UFUNCTION()
	void UpdateQuickActionWidget();
	FGameplayTag GetQuickActionAbilityTag(const FGameplayTag& InQuickActionTag);

	UFUNCTION()
	void OnObjectiveActivated(USI_ObjectiveData* ActivatedObjective);
	UFUNCTION()
	void OnObjectiveCompleted(USI_ObjectiveData* CompletedObjective);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	TArray<USI_InteractionWidget*>& GetActiveInteractionWidgets();

	UFUNCTION(BlueprintPure, Category = "Media")
	USI_MoviePlayerWidget* GetMoviePlayerWidget() const;
	UFUNCTION(BlueprintPure, Category = "PlayerHUD")
	USI_HUD* GetPlayerHUD();

protected:

	virtual void OnGameInstanceInit() override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag) override;
	virtual void OnPlayerStart() override;
	
	void DisplayDialogueBox();
	void HideDialogueBox();
	void HideActiveInteractionWidgets();
	void LoadingScreenFadeDelay();


private:

	void BindCaseManagerDelegates();
	void DelayWidgetCreation(USI_UserWidget* InWidgetPtr, TSubclassOf<USI_UserWidget> InWidgetClass, FGameplayTag InUITag);
	
	virtual void InitializeDelegates() override;
	virtual void InitializeDelegateMaps() override;
	
	UPROPERTY()
	ASI_PlayerController* PlayerController;

	TMap<FGameplayTag, USI_UserWidget*> UIWidgetContainer;

	FGameplayTag CurrentUITag;
	
	UPROPERTY()
	USI_UserWidget* LoadingScreen;
	UPROPERTY()
	USI_HUD* PlayerHUD;
	UPROPERTY()
	USI_UserWidget* SystemMenu;
	UPROPERTY()
	USI_UserWidget* MapMenu;
	UPROPERTY()
	USI_SkipWidget* SkipWidget;
	UPROPERTY()
	USI_MoviePlayerWidget* MoviePlayerWidget;
	UPROPERTY()
	USI_CaseTitleCard* CaseTitleCardWidget;
	UPROPERTY()
	USI_QuickActionWidget* QuickActionWidget;
	UPROPERTY()
	TArray<USI_InteractionWidget*> ActiveInteractionWidgets;

	FTimerHandle LoadingScreenFadeDelayHandle;
	FTimerDelegate LoadingScreenFadeDelayDelegate;
	
	TArray<FSimpleDelegate> WidgetCreationDelayDelegates;
	FSimpleDelegate TitleCardDelayDelegate;

	TMap<FGameplayTag, FSimpleDelegate> AddUIDelegateContainer;
	
	FSimpleDelegate AddGameMenuDelegate;
	FSimpleDelegate AddHUDDelegate;
	FSimpleDelegate AddLoadingScreenDelegate;
	FSimpleDelegate AddMapMenuDelegate;
	FSimpleDelegate AddSystemMenuDelegate;
	FSimpleDelegate UpdateQuickActionDelegate;
	FSimpleDelegate AddVendorMenuDelegate;
	FSimpleDelegate AddVideoScreenDelegate;
};
