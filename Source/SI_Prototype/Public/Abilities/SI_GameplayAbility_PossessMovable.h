// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "SI_GameplayAbility_PossessMovable.generated.h"

class USI_GameplayTagManager;
class ASI_PlayerCameraManager;
class ASI_PlayerController;
class ASI_Nick;
class ASI_PossessedMovable;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_PossessMovable : public USI_GameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	TSubclassOf<ASI_PossessedMovable> GetPossessedMovableClass() const { return PossessedMovableClass;}
	bool PossessTarget(const FGameplayAbilityActorInfo* InActorInfo, const FGameplayEventData* InTriggerEventData);
	
protected:
	ASI_PossessedMovable* SpawnPossessedMovable(const FVector InHitLocation);
	void UpdateMoveToLocation();
	void StartUpdateIndicatorPositionTimer();
	void CancelUpdateIndicatorPositionTimer();

	UPROPERTY()
	ASI_Nick* Nick;
	UPROPERTY()
	ASI_PlayerController* PC;
	UPROPERTY()
	ASI_PlayerCameraManager* SICameraManger;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_PossessedMovable> PossessedMovableClass;
	UPROPERTY()
	ASI_PossessedMovable* PossessedMovable;
	UPROPERTY()
	USI_GameplayTagManager* SITagManager;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AdaptableActionMaximumRadius = 2500.0f;
	float UpdateIndicatorDelay = 0.001f;
	FTimerHandle GhostActorPositionTimerHandle;
};
