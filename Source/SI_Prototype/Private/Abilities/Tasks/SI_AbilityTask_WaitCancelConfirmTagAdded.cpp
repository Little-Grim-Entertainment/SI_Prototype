// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_WaitCancelConfirmTagAdded.h"

#include "AbilitySystemGlobals.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

USI_AbilityTask_WaitCancelConfirmTagAdded* USI_AbilityTask_WaitCancelConfirmTagAdded::WaitCancelConfirmGameplayTagAdd(UGameplayAbility* OwningAbility,
	FGameplayTag InCancelTag, FGameplayTag InConfirmTag, AActor* InOptionalExternalTarget, bool OnlyTriggerOnce)
{
	USI_AbilityTask_WaitCancelConfirmTagAdded* MyObj = NewAbilityTask<USI_AbilityTask_WaitCancelConfirmTagAdded>(OwningAbility);
	MyObj->CancelTag = InCancelTag;
	MyObj->ConfirmTag = InConfirmTag;
	MyObj->SetExternalTarget(InOptionalExternalTarget);
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;

	return MyObj;
}

void USI_AbilityTask_WaitCancelConfirmTagAdded::Activate()
{
	USI_AbilitySystemComponent* ASC = GetTargetASC();
	if(!IsValid(ASC)) {LG_LOG(LogSI_AbilityTask, Error, "ASC is invalid!") return;}

	if (ASC)
	{
		CancelDelegateHandle = ASC->RegisterGameplayTagEvent(CancelTag).AddUObject(this, &USI_AbilityTask_WaitCancelConfirmTagAdded::CancelGameplayTagCallback);
		ConfirmDelegateHandle = ASC->RegisterGameplayTagEvent(ConfirmTag).AddUObject(this, &USI_AbilityTask_WaitCancelConfirmTagAdded::ConfirmGameplayTagCallback);
		RegisteredCallback = true;
	}
	
	if (ASC && ASC->HasMatchingGameplayTag(CancelTag))
	{	
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			CancelTagAdded.Broadcast();
		}
		if(OnlyTriggerOnce)
		{
			EndTask();
			return;
		}
	}
	if (ASC && ASC->HasMatchingGameplayTag(ConfirmTag))
	{	
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			ConfirmTagAdded.Broadcast();
		}
		if(OnlyTriggerOnce)
		{
			EndTask();
			return;
		}
	}

	Super::Activate();
}

void USI_AbilityTask_WaitCancelConfirmTagAdded::CancelGameplayTagCallback(const FGameplayTag Tag, int32 NewCount)
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

void USI_AbilityTask_WaitCancelConfirmTagAdded::ConfirmGameplayTagCallback(const FGameplayTag Tag, int32 NewCount)
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

USI_AbilitySystemComponent* USI_AbilityTask_WaitCancelConfirmTagAdded::GetTargetASC()
{
	if (UseExternalTarget)
	{
		return OptionalExternalTarget;
	}
	
	return Super::GetTargetASC();
}

void USI_AbilityTask_WaitCancelConfirmTagAdded::OnDestroy(bool AbilityIsEnding)
{
	USI_AbilitySystemComponent* ASC = GetTargetASC();
	if (RegisteredCallback && ASC)
	{
		ASC->RegisterGameplayTagEvent(CancelTag).Remove(CancelDelegateHandle);
		ASC->RegisterGameplayTagEvent(ConfirmTag).Remove(ConfirmDelegateHandle);		
	}

	Super::OnDestroy(AbilityIsEnding);
}

void USI_AbilityTask_WaitCancelConfirmTagAdded::SetExternalTarget(AActor* Actor)
{
	if (Actor)
	{
		UseExternalTarget = true;
		OptionalExternalTarget = GetSIAbilitySystemComponentFromActor(Actor);
	}
}
