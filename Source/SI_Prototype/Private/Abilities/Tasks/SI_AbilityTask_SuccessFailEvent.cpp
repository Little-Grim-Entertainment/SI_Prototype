// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_SuccessFailEvent.h"

#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

USI_AbilityTask_WaitSuccessFailEvent::USI_AbilityTask_WaitSuccessFailEvent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	OnlyMatchExact = true;
	OnlyTriggerOnce = true;
}

USI_AbilityTask_WaitSuccessFailEvent* USI_AbilityTask_WaitSuccessFailEvent::WaitSuccessFailEvent(UGameplayAbility* OwningAbility, FGameplayTag SuccessTag, FGameplayTag FailedTag, AActor* OptionalExternalTarget, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	USI_AbilityTask_WaitSuccessFailEvent* MyObj = NewAbilityTask<USI_AbilityTask_WaitSuccessFailEvent>(OwningAbility);
	MyObj->SuccessTag = SuccessTag;
	MyObj->FailedTag = FailedTag;
	MyObj->SetExternalTarget(OptionalExternalTarget);
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;

	return MyObj;
}

void USI_AbilityTask_WaitSuccessFailEvent::Activate()
{
	USI_AbilitySystemComponent* ASC = Cast<USI_AbilitySystemComponent>(GetTargetASC());
	if (ASC)
	{
		if (OnlyMatchExact)
		{
			SuccessEventHandle = ASC->GenericGameplayEventCallbacks.FindOrAdd(SuccessTag).AddUObject(this, &USI_AbilityTask_WaitSuccessFailEvent::SuccessEventCallback);
			FailedEventHandle = ASC->GenericGameplayEventCallbacks.FindOrAdd(FailedTag).AddUObject(this, &USI_AbilityTask_WaitSuccessFailEvent::FailedEventCallback);
	
		}
		else
		{
			SuccessEventHandle = ASC->AddGameplayEventTagContainerDelegate(FGameplayTagContainer(SuccessTag), FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &USI_AbilityTask_WaitSuccessFailEvent::SuccessEventContainerCallback));
			FailedEventHandle = ASC->AddGameplayEventTagContainerDelegate(FGameplayTagContainer(FailedTag), FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &USI_AbilityTask_WaitSuccessFailEvent::FailedEventContainerCallback));
	
		}	
	}
	Super::Activate();
}

void USI_AbilityTask_WaitSuccessFailEvent::SuccessEventCallback(const FGameplayEventData* Payload)
{
	SuccessEventContainerCallback(SuccessTag, Payload);
}

void USI_AbilityTask_WaitSuccessFailEvent::FailedEventCallback(const FGameplayEventData* Payload)
{
	SuccessEventContainerCallback(FailedTag, Payload);
}

void USI_AbilityTask_WaitSuccessFailEvent::SuccessEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempPayload = *Payload;
		TempPayload.EventTag = MatchingTag;
		SuccessEventReceived.Broadcast(MoveTemp(TempPayload));
	}
	if (OnlyTriggerOnce)
	{
		EndTask();
	}
}

void USI_AbilityTask_WaitSuccessFailEvent::FailedEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempPayload = *Payload;
		TempPayload.EventTag = MatchingTag;
		FailedEventReceived.Broadcast(MoveTemp(TempPayload));
	}
	if (OnlyTriggerOnce)
	{
		EndTask();
	}
}

void USI_AbilityTask_WaitSuccessFailEvent::SetExternalTarget(AActor* Actor)
{
	if (Actor)
	{
		UseExternalTarget = true;
		OptionalExternalTarget = GetSIAbilitySystemComponentFromActor(Actor);
	}
}

void USI_AbilityTask_WaitSuccessFailEvent::OnDestroy(bool AbilityEnding)
{
	USI_AbilitySystemComponent* ASC = GetTargetASC();
	if (ASC && SuccessEventHandle.IsValid())
	{
		if (OnlyMatchExact)
		{
			ASC->GenericGameplayEventCallbacks.FindOrAdd(SuccessTag).Remove(SuccessEventHandle);
		}
		else
		{
			ASC->RemoveGameplayEventTagContainerDelegate(FGameplayTagContainer(SuccessTag), SuccessEventHandle);
		}
		
	}

	if (ASC && FailedEventHandle.IsValid())
	{
		if (OnlyMatchExact)
		{
			ASC->GenericGameplayEventCallbacks.FindOrAdd(FailedTag).Remove(FailedEventHandle);
		}
		else
		{
			ASC->RemoveGameplayEventTagContainerDelegate(FGameplayTagContainer(FailedTag), FailedEventHandle);
		}
		
	}

	Super::OnDestroy(AbilityEnding);
}
