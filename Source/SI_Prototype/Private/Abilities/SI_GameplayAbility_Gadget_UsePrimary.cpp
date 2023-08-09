// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Gadget_UsePrimary.h"

#include "Actors/Gadgets/SI_BaseGadget.h"
#include "Characters/SI_Character.h"

void USI_GameplayAbility_Gadget_UsePrimary::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogSI_Ability," Ability Activated");
	
	ASI_Character* Character = Cast<ASI_Character>(ActorInfo->OwnerActor.Get());
	TArray<AActor*> AttachedActors;
	Character->GetAttachedActors(AttachedActors, true, false);

	for (auto AttachedActor : AttachedActors)
	{
		EquippedGadget = Cast<ASI_BaseGadget>(AttachedActor);
		EquippedGadget->ActivatePrimaryAction();			
	}
	
}

void USI_GameplayAbility_Gadget_UsePrimary::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(IsValid(EquippedGadget))
	{
		EquippedGadget->CancelPrimaryAction();
	}
}
