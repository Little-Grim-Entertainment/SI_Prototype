﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility.h"


void USI_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG(LogLG_Ability, Log, "Ability Activated");
	
	ActiveSpecHandle = GetCurrentAbilitySpec()->Handle;
	ActiveSpecHandleDelegate.Broadcast(ActiveSpecHandle);
}

void USI_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
