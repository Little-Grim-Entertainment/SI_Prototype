// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_SuccessFailEvent.h"

#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

USI_AbilityTask_SuccessFailEvent::USI_AbilityTask_SuccessFailEvent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

USI_AbilityTask_SuccessFailEvent* USI_AbilityTask_SuccessFailEvent::WaitGameplayEvent(UGameplayAbility* OwningAbility, FGameplayTag Tag, AActor* OptionalExternalTarget, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	USI_AbilityTask_SuccessFailEvent* MyObj = NewAbilityTask<USI_AbilityTask_SuccessFailEvent>(OwningAbility);
	MyObj->Tag = Tag;
	MyObj->SetExternalTarget(OptionalExternalTarget);
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;

	return MyObj;
}

void USI_AbilityTask_SuccessFailEvent::Activate()
{
	USI_AbilitySystemComponent* ASC = Cast<USI_AbilitySystemComponent>(GetTargetASC());
	if (ASC)
	{
		if (OnlyMatchExact)
		{
			SuccessEventHandle = ASC->GenericGameplayEventCallbacks.FindOrAdd(Tag).AddUObject(this, &USI_AbilityTask_SuccessFailEvent::GameplayEventCallback);
		}
		else
		{
			SuccessEventHandle = ASC->AddGameplayEventTagContainerDelegate(FGameplayTagContainer(Tag), FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &USI_AbilityTask_SuccessFailEvent::GameplayEventContainerCallback));
		}	
	}

	if (ASC)
	{
		if (OnlyMatchExact)
		{
			FailedEventHandle = ASC->GenericGameplayEventCallbacks.FindOrAdd(Tag).AddUObject(this, &USI_AbilityTask_SuccessFailEvent::GameplayEventCallback);
		}
		else
		{
			FailedEventHandle = ASC->AddGameplayEventTagContainerDelegate(FGameplayTagContainer(Tag), FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &USI_AbilityTask_SuccessFailEvent::GameplayEventContainerCallback));
		}	
	}

	Super::Activate();
}

void USI_AbilityTask_SuccessFailEvent::GameplayEventCallback(const FGameplayEventData* Payload)
{
	GameplayEventContainerCallback(Tag, Payload);
}

void USI_AbilityTask_SuccessFailEvent::GameplayEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload)
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

void USI_AbilityTask_SuccessFailEvent::SetExternalTarget(AActor* Actor)
{
	if (Actor)
	{
		UseExternalTarget = true;
		OptionalExternalTarget = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
	}
}

UAbilitySystemComponent* USI_AbilityTask_SuccessFailEvent::GetTargetASC()
{
	if (UseExternalTarget)
	{
		return OptionalExternalTarget;
	}

	return nullptr; //AbilitySystemComponent;
}

void USI_AbilityTask_SuccessFailEvent::OnDestroy(bool AbilityEnding)
{
	UAbilitySystemComponent* ASC = GetTargetASC();
	if (ASC && SuccessEventHandle.IsValid())
	{
		if (OnlyMatchExact)
		{
			ASC->GenericGameplayEventCallbacks.FindOrAdd(Tag).Remove(SuccessEventHandle);
		}
		else
		{
			ASC->RemoveGameplayEventTagContainerDelegate(FGameplayTagContainer(Tag), SuccessEventHandle);
		}
		
	}

	if (ASC && FailedEventHandle.IsValid())
	{
		if (OnlyMatchExact)
		{
			ASC->GenericGameplayEventCallbacks.FindOrAdd(Tag).Remove(FailedEventHandle);
		}
		else
		{
			ASC->RemoveGameplayEventTagContainerDelegate(FGameplayTagContainer(Tag), FailedEventHandle);
		}
		
	}

	Super::OnDestroy(AbilityEnding);
}
