// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_QuickActionWidget.h"
#include "GameplayTag/SI_GameplayTagTypes.h"
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
	void RemoveSIWidget(USI_UserWidget* InWidgetPtr);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateMapMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateSystemMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ToggleSystemMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateSkipWidget();

	UFUNCTION(BlueprintPure, Category = "UI")
	USI_UserWidget* GetSIWidgetByTag(const FGameplayTag& InWidgetTag);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPlayerHUD(bool bShouldShow);

	
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
	USI_MoviePlayerWidget* GetMoviePlayerWidget();
	UFUNCTION(BlueprintPure, Category = "PlayerHUD")
	USI_HUD* GetPlayerHUD();
	
	UFUNCTION()
	void SetUIEnabled(bool bInShouldEnable);
	
	template <class T>
	TArray<T*>& GetActiveUIWidgets();
	
	template <class T>
	T* GetActiveUIWidget();

	template <class T>
	T* GetActiveUIWidgetByTag(const FGameplayTag& InWidgetTag);

	template <class WidgetC>
	WidgetC* CreateSIWidget(FGameplayTag InUITag, TSubclassOf<UUserWidget> UserWidgetClass = WidgetC::StaticClass(), FName WidgetName = NAME_None );

		
protected:

	virtual void OnGameInstanceInit() override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload = nullptr) override;
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload = nullptr) override;
	virtual void OnPlayerStart() override;
	
	void DisplayDialogueBox();
	void HideDialogueBox();
	void HideActiveInteractionWidgets();
	void LoadingScreenFadeDelay();


private:

	void BindCaseManagerDelegates();
	void DelayWidgetCreation(const FSimpleDelegate& InDelegate);

	void ShowMapMenu(bool bShouldShow);
	
	virtual void InitializeDelegates() override;
	virtual void InitializeDelegateMaps() override;

	USI_UserWidget* CreateSIWidget_Internal(TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);
	
	UPROPERTY()
	ASI_PlayerController* PlayerController;

	FGameplayTag CurrentUITag;

	TMap<FGameplayTag, TSoftObjectPtr<USI_UserWidget>> ActiveUIWidgetsArray;
	
	UPROPERTY()
	TArray<USI_InteractionWidget*> ActiveInteractionWidgets;

	bool bUIEnabled;
	
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

template <class T>
TArray<T*>& USI_UIManager::GetActiveUIWidgets()
{
	TArray<T*> TempArray;
	
	for(TPair<FGameplayTag, TSoftObjectPtr<USI_UserWidget>>& CurrentWidget : ActiveUIWidgetsArray)
	{
		T* TWidget = Cast<T>(CurrentWidget.Value.Get());
		if(TWidget)
		{
			TempArray.Add(TWidget);
		}
	}
	return TempArray;
}

template <class T>
T* USI_UIManager::GetActiveUIWidget()
{
	for( TPair<FGameplayTag, TSoftObjectPtr<USI_UserWidget>>& CurrentWidget : ActiveUIWidgetsArray)
	{
		T* TWidget = Cast<T>(CurrentWidget.Value.Get());
		return TWidget;
	}
	return nullptr;
}

template <class T>
T* USI_UIManager::GetActiveUIWidgetByTag(const FGameplayTag& InWidgetTag)
{
	for(TPair<FGameplayTag, TSoftObjectPtr<USI_UserWidget>>& CurrentWidget : ActiveUIWidgetsArray)
	{
		if(CurrentWidget.Key == InWidgetTag)
		{
			T* TWidget = Cast<T>(CurrentWidget.Value.Get());
			return TWidget;
		}
	}
	return nullptr;
}

template <class WidgetC>
WidgetC* USI_UIManager::CreateSIWidget(FGameplayTag InUITag, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName)
{
	USI_UserWidget* NewUserWidget = CreateSIWidget_Internal(UserWidgetClass, WidgetName);
	if(IsValid(NewUserWidget))
	{
		ActiveUIWidgetsArray.Add(InUITag, NewUserWidget);

		WidgetC* NewWidgetType = Cast<WidgetC>(NewUserWidget);
		if(NewWidgetType != nullptr)
		{
			return NewWidgetType;
		}
	}
	return nullptr;
}
