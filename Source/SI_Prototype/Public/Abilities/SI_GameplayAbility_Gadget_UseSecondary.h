// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "SI_GameplayAbility_Gadget_UseSecondary.generated.h"

class ASI_BaseGadget;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_Gadget_UseSecondary : public USI_GameplayAbility
{
	GENERATED_BODY()

public:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	
	UPROPERTY()
	ASI_BaseGadget* EquippedGadget;
};
