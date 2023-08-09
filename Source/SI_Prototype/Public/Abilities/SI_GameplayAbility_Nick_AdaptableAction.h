// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "SI_GameplayAbility_Nick_AdaptableAction.generated.h"

class USI_AbilityTask_HighlightInteractables;
class USI_AbilityTask_UpdateMoveToIndicator;

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_Nick_AdaptableAction : public USI_GameplayAbility
{
	GENERATED_BODY()

public:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	UPROPERTY()
	USI_AbilityTask_UpdateMoveToIndicator* UpdateMoveToIndicatorTask;
	UPROPERTY()
	USI_AbilityTask_HighlightInteractables* HighlightInteractablesTask;
};
