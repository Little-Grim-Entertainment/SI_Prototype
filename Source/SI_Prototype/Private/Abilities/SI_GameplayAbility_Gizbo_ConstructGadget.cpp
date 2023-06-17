// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Gizbo_ConstructGadget.h"

#include "Characters/SI_Gizbo.h"

void USI_GameplayAbility_Gizbo_ConstructGadget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(ActorInfo->OwnerActor != TriggerEventData->Target)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Black,"Ability: ConstructGadget for Nick");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Ability: ConstructGadget for Gizbo");
	}
}
