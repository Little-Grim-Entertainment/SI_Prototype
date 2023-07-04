// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Interact.h"
#include "Interfaces/SI_InteractInterface.h"
#include "Characters/SI_Nick.h"
#include "Controllers/SI_PlayerController.h"

void USI_GameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASI_PlayerController* Controller = Cast<ASI_PlayerController>(ActorInfo->AvatarActor.Get()->GetInstigatorController());
	if(!IsValid(Controller)) { return; }

	if(Controller->GetInteractableActor())
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(Controller->GetInteractableActor()))
		{
			InterfaceActor->Execute_OnInteract(Controller->GetInteractableActor(), Controller->GetInteractableActor());
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USI_GameplayAbility_Interact::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
