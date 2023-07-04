// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Interact.h"

#include "Controllers/SI_PlayerController.h"
#include "Interfaces/SI_InteractInterface.h"

void USI_GameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASI_PlayerController* PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());

	if(!IsValid(PlayerController)) { return; }

	if(PlayerController->GetInteractableActor())
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(PlayerController->GetInteractableActor()))
		{
			InterfaceActor->Execute_OnInteract(PlayerController->GetInteractableActor(), PlayerController->GetInteractableActor());
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
