// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/SI_AbilityTask.h"
#include "SI_AbilityTask_SuccessFailEvent.generated.h"

class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuccessFailEventDelegate, FGameplayEventData, Payload);

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask_SuccessFailEvent : public USI_AbilityTask
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FSuccessFailEventDelegate	SuccessEventReceived;
	UPROPERTY(BlueprintAssignable)
	FSuccessFailEventDelegate	FailedEventReceived;

	/*
	 * Wait until the specified gameplay tag event is triggered. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes
	 * It will keep listening as long as OnlyTriggerOnce = false
	 * If OnlyMatchExact = false it will trigger for nested tags
	 */
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static USI_AbilityTask_SuccessFailEvent* WaitGameplayEvent(UGameplayAbility* OwningAbility, FGameplayTag EventTag, AActor* OptionalExternalTarget=nullptr, bool OnlyTriggerOnce=false, bool OnlyMatchExact = true);

	void SetExternalTarget(AActor* Actor);

	UAbilitySystemComponent* GetTargetASC();

	virtual void Activate() override;

	virtual void GameplayEventCallback(const FGameplayEventData* Payload);
	virtual void GameplayEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload);

	void OnDestroy(bool AbilityEnding) override;

	FGameplayTag Tag;

	UPROPERTY()
	UAbilitySystemComponent* OptionalExternalTarget;

	bool UseExternalTarget;	
	bool OnlyTriggerOnce;
	bool OnlyMatchExact;

	FDelegateHandle SuccessEventHandle;
	FDelegateHandle FailedEventHandle;
};