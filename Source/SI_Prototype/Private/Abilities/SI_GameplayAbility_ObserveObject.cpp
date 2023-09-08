// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities\SI_GameplayAbility_ObserveObject.h"
#include "Actors/SI_InteractableActor.h"
#include "Interfaces/SI_InteractInterface.h"
#include "Characters/SI_Nick.h"

void USI_GameplayAbility_ObserveObject::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogSI_Ability," Ability Activated");
	
	ASI_Nick* Nick = Cast<ASI_Nick>(ActorInfo->AvatarActor.Get());
	if(!IsValid(Nick)) {LG_LOG_LOG(LogSI_Ability,"Nick is not valid");return; }

	ASI_InteractableActor* ObservableActor = Cast<ASI_InteractableActor>(Nick->GetCurrentInteractableActor());
	if(!IsValid(ObservableActor)) {LG_LOG_LOG(LogSI_Ability,"ObservableActor is not valid");return; }
	
	ObservableActor->Execute_OnObserved(Cast<UObject>(ObservableActor), ObservableActor);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USI_GameplayAbility_ObserveObject::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
