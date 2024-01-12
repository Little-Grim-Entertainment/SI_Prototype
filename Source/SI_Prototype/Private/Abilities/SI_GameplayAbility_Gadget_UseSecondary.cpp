// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Gadget_UseSecondary.h"

#include "Actors/Gadgets/SI_BaseGadget.h"
#include "Characters/SI_Character.h"

void USI_GameplayAbility_Gadget_UseSecondary::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogLG_Ability," Ability Activated");
	
	ASI_Character* Character = Cast<ASI_Character>(ActorInfo->OwnerActor.Get());
	TArray<AActor*> AttachedActors;
	Character->GetAttachedActors(AttachedActors, true, false);

	for (auto AttachedActor : AttachedActors)
	{
		// Todo: (Anu) Does this need an IsValid check?
		EquippedGadget = Cast<ASI_BaseGadget>(AttachedActor);
		EquippedGadget->ActivateSecondaryAction();			
	}
}

void USI_GameplayAbility_Gadget_UseSecondary::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(IsValid(EquippedGadget))
	{
		EquippedGadget->CancelSecondaryAction();
	}
}

