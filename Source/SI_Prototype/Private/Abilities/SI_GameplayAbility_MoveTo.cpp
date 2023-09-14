// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_MoveTo.h"

#include "Characters/SI_NPC.h"

void USI_GameplayAbility_MoveTo::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogSI_Ability,"Ability Activated");
	
	LG_PRINT(5.f, Red, "MoveTo Ability Activated");

	ASI_NPC* Actor = Cast<ASI_NPC>(ActorInfo->OwnerActor);
	if(!IsValid(Actor)) {LG_LOG(LogSI_Ability, Error, "Actor is not valid"); return;}
	
	Actor->SetCurrentBehavior(SITag_Behavior_MoveTo);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void USI_GameplayAbility_MoveTo::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	LG_PRINT(5.f, Red, "MoveTo Ability Ended");
}
