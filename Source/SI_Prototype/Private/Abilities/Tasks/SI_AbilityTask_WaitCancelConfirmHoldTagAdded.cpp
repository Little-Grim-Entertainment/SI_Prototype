// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_WaitCancelConfirmHoldTagAdded.h"

#include "AbilitySystemGlobals.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

USI_AbilityTask_WaitCancelConfirmHoldTagAdded* USI_AbilityTask_WaitCancelConfirmHoldTagAdded::WaitCancelConfirmGameplayTagAdd(UGameplayAbility* OwningAbility,
	FGameplayTag InCancelTag, FGameplayTag InConfirmTag, FGameplayTag InHoldConfirmTag, AActor* InOptionalExternalTarget, bool OnlyTriggerOnce)
{
	USI_AbilityTask_WaitCancelConfirmHoldTagAdded* MyObj = NewAbilityTask<USI_AbilityTask_WaitCancelConfirmHoldTagAdded>(OwningAbility);
	MyObj->CancelTag = InCancelTag;
	MyObj->ConfirmTag = InConfirmTag;
	MyObj->HoldConfirmTag = InHoldConfirmTag;
	MyObj->SetExternalTarget(InOptionalExternalTarget);
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;

	return MyObj;
}

void USI_AbilityTask_WaitCancelConfirmHoldTagAdded::Activate()
{
	USI_AbilitySystemComponent* ASC = GetTargetASC();
	if(!IsValid(ASC)) {LG_LOG(LogLG_Ability, Error, "ASC is invalid!") return;}

	if (ASC)
	{
		CancelDelegateHandle = ASC->RegisterGameplayTagEvent(CancelTag).AddUObject(this, &USI_AbilityTask_WaitCancelConfirmHoldTagAdded::CancelGameplayTagCallback);
		ConfirmDelegateHandle = ASC->RegisterGameplayTagEvent(ConfirmTag).AddUObject(this, &USI_AbilityTask_WaitCancelConfirmHoldTagAdded::ConfirmGameplayTagCallback);
		HoldConfirmDelegateHandle = ASC->RegisterGameplayTagEvent(HoldConfirmTag).AddUObject(this, &USI_AbilityTask_WaitCancelConfirmHoldTagAdded::HoldConfirmGameplayTagCallback);
		RegisteredCallback = true;
	}
	
	Super::Activate();
}

void USI_AbilityTask_WaitCancelConfirmHoldTagAdded::CancelGameplayTagCallback(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount==1)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			CancelTagAdded.Broadcast();
		}
		if(OnlyTriggerOnce)
		{
			EndTask();
		}
	}
}

void USI_AbilityTask_WaitCancelConfirmHoldTagAdded::ConfirmGameplayTagCallback(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount==1)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			ConfirmTagAdded.Broadcast();
		}
		if(OnlyTriggerOnce)
		{
			EndTask();
		}
	}
}

void USI_AbilityTask_WaitCancelConfirmHoldTagAdded::HoldConfirmGameplayTagCallback(const FGameplayTag Tag,
	int32 NewCount)
{
	if (NewCount==1)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			HoldConfirmTagAdded.Broadcast();
		}
		if(OnlyTriggerOnce)
		{
			EndTask();
		}
	}
}

USI_AbilitySystemComponent* USI_AbilityTask_WaitCancelConfirmHoldTagAdded::GetTargetASC()
{
	if (UseExternalTarget)
	{
		return OptionalExternalTarget;
	}
	
	return Super::GetTargetASC();
}

void USI_AbilityTask_WaitCancelConfirmHoldTagAdded::OnDestroy(bool AbilityIsEnding)
{
	USI_AbilitySystemComponent* ASC = GetTargetASC();
	if (RegisteredCallback && ASC)
	{
		ASC->RegisterGameplayTagEvent(CancelTag).Remove(CancelDelegateHandle);
		ASC->RegisterGameplayTagEvent(ConfirmTag).Remove(ConfirmDelegateHandle);
		ASC->RegisterGameplayTagEvent(HoldConfirmTag).Remove(HoldConfirmDelegateHandle);		
	}

	GetWorld()->GetTimerManager().ClearTimer(EndTaskTimerHandle);
	
	Super::OnDestroy(AbilityIsEnding);
}

void USI_AbilityTask_WaitCancelConfirmHoldTagAdded::SetExternalTarget(AActor* Actor)
{
	if (Actor)
	{
		UseExternalTarget = true;
		OptionalExternalTarget = GetSIAbilitySystemComponentFromActor(Actor);
	}
}

void USI_AbilityTask_WaitCancelConfirmHoldTagAdded::StartEndTaskTimer()
{
	GetWorld()->GetTimerManager().SetTimer(EndTaskTimerHandle, this, &ThisClass::EndTask, 2.5f, false);
}