// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Observation.h"

#include "Abilities/Tasks/SI_AbilityTask_Observation.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

void USI_GameplayAbility_Observation::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogSI_Ability," Ability Activated");
	
	Task = USI_AbilityTask_Observation::ObservationTask(this);
	Task->ReadyForActivation();
}

void USI_GameplayAbility_Observation::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	Task->EndTask();
}
