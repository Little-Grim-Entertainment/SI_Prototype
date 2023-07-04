// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Interact.h"
<<<<<<< HEAD

#include "Controllers/SI_PlayerController.h"
#include "Interfaces/SI_InteractInterface.h"
=======
#include "Actors/SI_InteractableActor.h"
#include "Interfaces/SI_InteractInterface.h"
#include "Characters/SI_Nick.h"
>>>>>>> parent of 9b8aad05 (.)

void USI_GameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

<<<<<<< HEAD
	ASI_PlayerController* PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());

	if(!IsValid(PlayerController)) { return; }

	if(PlayerController->GetInteractableActor())
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(PlayerController->GetInteractableActor()))
		{
			InterfaceActor->Execute_OnInteract(PlayerController->GetInteractableActor(), PlayerController->GetInteractableActor());
		}
	}
=======
	ASI_Nick* Nick = Cast<ASI_Nick>(ActorInfo->AvatarActor.Get());
	if(!IsValid(Nick)) { return; }

	ASI_InteractableActor* ObservableActor = Cast<ASI_InteractableActor>(Nick->GetCurrentInteractableActor());
	if(!IsValid(ObservableActor)) { return; }
	
	ObservableActor->Execute_OnObserved(Cast<UObject>(ObservableActor), ObservableActor);
>>>>>>> parent of 9b8aad05 (.)

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USI_GameplayAbility_Interact::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
