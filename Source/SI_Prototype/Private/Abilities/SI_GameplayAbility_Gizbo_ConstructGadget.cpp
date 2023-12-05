// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Gizbo_ConstructGadget.h"

#include "Actors/Gadgets/SI_BaseGadget.h"
#include "Characters/SI_Gizbo.h"

void USI_GameplayAbility_Gizbo_ConstructGadget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogLG_Ability," Ability Activated");
	
	TArray<ASI_BaseGadget> ActiveGadgets;
	if(ActiveGadgets.Num() > 2)
	{
		//Too Many Gadgets
	}

}
