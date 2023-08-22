// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/SI_AbilityTask.h"
#include "SI_AbilityTask_SuccessFailEvent.generated.h"

class USI_AbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSuccessFailEventDelegate, FGameplayEventData, Payload);

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask_WaitSuccessFailEvent : public USI_AbilityTask
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FWaitSuccessFailEventDelegate	SuccessEventReceived;
	
	UPROPERTY(BlueprintAssignable)
	FWaitSuccessFailEventDelegate	FailedEventReceived;

	/*
	 * Wait until the specified gameplay tag event is triggered. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes
	 * It will keep listening as long as OnlyTriggerOnce = false
	 * If OnlyMatchExact = false it will trigger for nested tags
	 */
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static USI_AbilityTask_WaitSuccessFailEvent* WaitSuccessFailEvent(UGameplayAbility* OwningAbility, FGameplayTag SuccessTag, FGameplayTag FailedTag, AActor* OptionalExternalTarget=nullptr, bool OnlyTriggerOnce=false, bool OnlyMatchExact = true);

	void SetExternalTarget(AActor* Actor);

	virtual void Activate() override;

	virtual void SuccessEventCallback(const FGameplayEventData* Payload);
	virtual void FailedEventCallback(const FGameplayEventData* Payload);
	virtual void SuccessEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload);
	virtual void FailedEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload);

	UPROPERTY()
	USI_AbilitySystemComponent* OptionalExternalTarget;
	
	void OnDestroy(bool AbilityEnding) override;

	FGameplayTag SuccessTag;
	FGameplayTag FailedTag;
	
	bool OnlyMatchExact;

	FDelegateHandle SuccessEventHandle;
	FDelegateHandle FailedEventHandle;
};