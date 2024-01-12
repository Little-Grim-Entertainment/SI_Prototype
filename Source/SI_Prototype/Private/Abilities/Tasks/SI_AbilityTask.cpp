// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask.h"

#include "AbilitySystemInterface.h"
#include "LG_DebugMacros.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

/** Helping function to avoid having to manually cast */
USI_AbilitySystemComponent* USI_AbilityTask::GetSIAbilitySystemComponentFromActor(const AActor* Actor)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}

	// Fall back to a component search to better support BP-only actors
	return Actor->FindComponentByClass<USI_AbilitySystemComponent>();

}

USI_AbilitySystemComponent* USI_AbilityTask::GetTargetASC()
{
	SI_AbilitySystemComponent = Cast<USI_AbilitySystemComponent>(AbilitySystemComponent);
	if(!IsValid(SI_AbilitySystemComponent)) LG_LOG(LogLG_Ability, Error, "AI_AbilitySystemCompoenet is invalid!")
	return SI_AbilitySystemComponent;
}