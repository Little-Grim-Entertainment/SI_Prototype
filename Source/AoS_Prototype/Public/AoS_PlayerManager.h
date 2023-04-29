// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_LocalPlayerSubsystem.h"
#include "AoS_PlayerManager.generated.h"

class UAoS_UserWidget;
class AAoS_PlayerController;
class UAoS_EnhancedInputComponent;

UCLASS()
class AOS_PROTOTYPE_API UAoS_PlayerManager : public UAoS_LocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	void RequestNewPlayerState(const FGameplayTag& InPlayerState);

	const FGameplayTag& GetCurrentPlayerState() const;
	const FGameplayTag& GetPreviousPlayerState() const;


protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag) override;
	
private:

	virtual void InitializeDelegates() override;
	virtual void InitializeDelegateMaps() override;
	
	void SetupExplorationState();
	void SetupObservationState();
	void SetupMenuState();
	void SetupDialogueState();
	void SetupInterrogationState();
	void SetupInactiveState();
	
	UPROPERTY()
	AAoS_PlayerController* PlayerController;
	
	FGameplayTag PreviousPlayerState;
	FGameplayTag CurrentPlayerState;
	FGameplayTag SecondaryMediaTag;

	TMap<FGameplayTag, FSimpleDelegate> PlayerDelegateContainer;
	
	FSimpleDelegate ExplorationStateDelegate;
	FSimpleDelegate ObservationStateDelegate;
	FSimpleDelegate MenuStateDelegate;
	FSimpleDelegate MediaStateDelegate;
	FSimpleDelegate DialogueStateDelegate;
	FSimpleDelegate InterrogationStateDelegate;
	FSimpleDelegate InactiveStateDelegate;
};
