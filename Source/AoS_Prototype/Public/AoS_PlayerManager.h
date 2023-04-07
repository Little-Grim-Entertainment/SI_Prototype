// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_LocalPlayerSubsystem.h"
#include "AoS_PlayerManager.generated.h"

class AAoS_PlayerController;

UCLASS()
class AOS_PROTOTYPE_API UAoS_PlayerManager : public UAoS_LocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	void RequestNewPlayerState(const FGameplayTag& InPlayerState);

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

	TMap<FGameplayTag, FSimpleDelegate> AddPlayerDelegateContainer;
	
	FSimpleDelegate AddExplorationStateDelegate;
	FSimpleDelegate AddObservationStateDelegate;
	FSimpleDelegate AddMenuStateDelegate;
	FSimpleDelegate AddMediaStateDelegate;
	FSimpleDelegate AddDialogueStateDelegate;
	FSimpleDelegate AddInterrogationStateDelegate;
	FSimpleDelegate AddInactiveStateDelegate;

	TMap<FGameplayTag, FSimpleDelegate> RemovePlayerDelegateContainer;

	FSimpleDelegate RemoveExplorationStateDelegate;
	FSimpleDelegate RemoveObservationStateDelegate;
	FSimpleDelegate RemoveMenuStateDelegate;
	FSimpleDelegate RemoveMediaStateDelegate;
	FSimpleDelegate RemoveDialogueStateDelegate;
	FSimpleDelegate RemoveInterrogationStateDelegate;
	FSimpleDelegate RemoveInactiveStateDelegate;
};
