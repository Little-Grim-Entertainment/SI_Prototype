// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "Subsystems\SI_LocalPlayerSubsystem.h"
#include "SI_PlayerManager.generated.h"

class USI_GameplayAbility;
class USI_AbilitySystemComponent;
class USI_UserWidget;
class ASI_PlayerController;
class USI_EnhancedInputComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogSI_PlayerManager, Log, All);

UCLASS()
class SI_PROTOTYPE_API USI_PlayerManager : public USI_LocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	void RequestNewPlayerState(const FGameplayTag& InPlayerState);
	const FGameplayTag& GetCurrentPlayerState() const;
	const FGameplayTag& GetPreviousPlayerState() const;
	void ShowWorld(bool bShouldShow, bool bShouldFade);

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag) override;
	virtual void OnPlayerStart() override;
	virtual void OnGameModeBeginPlay() override;
	
private:

	virtual void InitializeDelegates() override;
	virtual void InitializeDelegateMaps() override;
	void TryActivateAbilityByTag();
	void TryCancelAbilityByTag();

	void SetupDialogueState();
	void SetupExplorationState();
	void SetupInactiveState();	
	void SetupInterrogationState();
	void SetupMenuState();
	void SetupObservationState();
	void SetupPossessMovableState();
	
	UPROPERTY()
	ASI_PlayerController* PlayerController;
	UPROPERTY()
	USI_AbilitySystemComponent* NickAbilitySystemComponent;
	
	bool bShowWorld = false;
	
	FGameplayTag PreviousPlayerState;
	FGameplayTag CurrentPlayerState;
	FGameplayTag CurrentAbilityTag;
	FGameplayTag SecondaryMediaTag;

	TMap<FGameplayTag, FSimpleDelegate> PlayerDelegateContainer;
	TMap<FGameplayTag, USI_GameplayAbility*> ActiveAbilitiesContainer;
	
	FSimpleDelegate ActivateAbilityDelegate;
	FSimpleDelegate DialogueStateDelegate;
	FSimpleDelegate ExplorationStateDelegate;
	FSimpleDelegate InactiveStateDelegate;
	FSimpleDelegate InterrogationStateDelegate;
	FSimpleDelegate MediaStateDelegate;
	FSimpleDelegate MenuStateDelegate;
	FSimpleDelegate ObservationStateDelegate;
	FSimpleDelegate PossessMovableStateDelegate;

};
