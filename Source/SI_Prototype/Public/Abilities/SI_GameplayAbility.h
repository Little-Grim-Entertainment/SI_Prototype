// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Abilities/GameplayAbility.h"
#include "LG_DebugMacros.h"
#include "SI_Prototype/SI_Prototype.h"
#include "SI_GameplayAbility.generated.h"

class USI_GameplayTagManager;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActiveSpecHandleDelegate, const FGameplayAbilitySpecHandle&, SpecHandle);
/**
 * 
 */
using namespace SI_NativeGameplayTagLibrary;

UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	FActiveSpecHandleDelegate ActiveSpecHandleDelegate;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	FGameplayAbilitySpecHandle ActiveSpecHandle;
	
};