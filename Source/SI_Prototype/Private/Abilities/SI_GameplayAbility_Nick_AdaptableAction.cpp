// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Nick_AdaptableAction.h"

#include "Abilities/Tasks/SI_AbilityTask_HighlightInteractables.h"
#include "Abilities/Tasks/SI_AbilityTask_UpdateMoveToIndicator.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"


void USI_GameplayAbility_Nick_AdaptableAction::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogSI_Ability," Ability Activated");
	
	UpdateMoveToIndicatorTask->ReadyForActivation();
	HighlightInteractablesTask->ReadyForActivation();
}

void USI_GameplayAbility_Nick_AdaptableAction::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UpdateMoveToIndicatorTask->EndTask();
	HighlightInteractablesTask->EndTask();
}

