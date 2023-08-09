// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_HighlightInteractables.h"

#include "Actors/SI_InteractableActor.h"
#include "EngineUtils.h" // ActorIterator

USI_AbilityTask_HighlightInteractables* USI_AbilityTask_HighlightInteractables::ObservationTask(UGameplayAbility* InOwningAbility)
{
	USI_AbilityTask_HighlightInteractables* HighlightInteractables = NewAbilityTask<USI_AbilityTask_HighlightInteractables>(InOwningAbility);

	HighlightInteractables->OwningAbility = InOwningAbility;

	return HighlightInteractables;
}

void USI_AbilityTask_HighlightInteractables::Activate()
{
	Super::Activate();

	StartHighlightInteractablesTimer();
}

void USI_AbilityTask_HighlightInteractables::OnDestroy(bool bInOwnerFinished)
{
	CancelInteractableHighlight();
	
	Super::OnDestroy(bInOwnerFinished);
	EndTask();
}

void USI_AbilityTask_HighlightInteractables::HighlightInteractables()
{
	for(TActorIterator<ASI_InteractableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASI_InteractableActor* HitInteractableActor = *ActorItr;
		if(FVector::Distance(HitInteractableActor->GetActorLocation(), OwningAbility->GetActorInfo().OwnerActor->GetActorLocation()) < 2000.0f)
		{
			HitInteractableActor->HighlightMesh->SetVisibility(true);	
		}
		else
		{
			HitInteractableActor->HighlightMesh->SetVisibility(false);
		}
	}
	StartHighlightInteractablesTimer();
}

void USI_AbilityTask_HighlightInteractables::StartHighlightInteractablesTimer()
{
	GetWorld()->GetTimerManager().SetTimer(HighlightInteractablesTimerHandle, this, &ThisClass::StartHighlightInteractablesTimer, HighlightInteractablesDelay, true);
}

void USI_AbilityTask_HighlightInteractables::CancelHighlightInteractablesTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HighlightInteractablesTimerHandle);
}

void USI_AbilityTask_HighlightInteractables::CancelInteractableHighlight()
{
	CancelHighlightInteractablesTimer();
	
	for(TActorIterator<ASI_InteractableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(ASI_InteractableActor* HitInteractableActor = *ActorItr)
		{
			HitInteractableActor->HighlightMesh->SetVisibility(false);
		}
	}
}