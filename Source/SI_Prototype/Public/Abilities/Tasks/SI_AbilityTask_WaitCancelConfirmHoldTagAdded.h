// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_AbilityTask.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "SI_AbilityTask_WaitCancelConfirmHoldTagAdded.generated.h"

class USI_AbilityManager;

UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask_WaitCancelConfirmHoldTagAdded : public USI_AbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWaitGameplayTagDelegate	CancelTagAdded;
	UPROPERTY(BlueprintAssignable)
	FWaitGameplayTagDelegate	ConfirmTagAdded;
	UPROPERTY(BlueprintAssignable)
	FWaitGameplayTagDelegate	HoldConfirmTagAdded;

	/**
	 * 	Wait until the specified gameplay tag is Added. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes. 
	 *  If the tag is already present when this task is started, it will immediately broadcast the Added event. It will keep listening as long as OnlyTriggerOnce = false.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static USI_AbilityTask_WaitCancelConfirmHoldTagAdded* WaitCancelConfirmGameplayTagAdd(UGameplayAbility* OwningAbility, FGameplayTag InCancelTag, FGameplayTag InConfirmTag, FGameplayTag InHoldConfirmTag, AActor* InOptionalExternalTarget=nullptr, bool OnlyTriggerOnce=false);

	virtual void Activate() override;
	UFUNCTION()
	void CancelGameplayTagCallback(const FGameplayTag Tag, int32 NewCount);
	UFUNCTION()
	void ConfirmGameplayTagCallback(const FGameplayTag Tag, int32 NewCount);
	UFUNCTION()
	void HoldConfirmGameplayTagCallback(const FGameplayTag Tag, int32 NewCount);
	
	void SetExternalTarget(AActor* Actor);
	void StartEndTaskTimer();

	FGameplayTag CancelTag;
	FGameplayTag ConfirmTag;
	FGameplayTag HoldConfirmTag;

protected:

	virtual USI_AbilitySystemComponent* GetTargetASC() override;

	virtual void OnDestroy(bool AbilityIsEnding) override;

	UPROPERTY()
	USI_AbilitySystemComponent* OptionalExternalTarget;
	
	bool RegisteredCallback;
	bool UseExternalTarget;	
	bool OnlyTriggerOnce;

	FDelegateHandle CancelDelegateHandle;
	FDelegateHandle ConfirmDelegateHandle;
	FDelegateHandle HoldConfirmDelegateHandle;

	FTimerHandle EndTaskTimerHandle;
};