// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "SI_GameplayAbility_Gizbo_DeconstructGadget.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_Gizbo_DeconstructGadget : public USI_GameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
