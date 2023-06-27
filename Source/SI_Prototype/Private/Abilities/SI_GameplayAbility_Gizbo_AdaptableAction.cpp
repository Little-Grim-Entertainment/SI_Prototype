// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Gizbo_AdaptableAction.h"

#include "Actors/SI_MoveToIndicator.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "Characters/SI_Nick.h"
#include "Controllers/SI_PlayerController.h"
#include "EngineUtils.h" // ActorIterator
#include "Actors/SI_MovableActor.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "Interfaces/SI_MovableInterface.h"

void USI_GameplayAbility_Gizbo_AdaptableAction::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Nick = Cast<ASI_Nick>(ActorInfo->OwnerActor);
	if(!IsValid(Nick)) return;
	PC = Cast<ASI_PlayerController>(Nick->GetController());
	if(!IsValid(PC)) return;
	SICameraManger = Cast<ASI_PlayerCameraManager>(PC->PlayerCameraManager);
	if(!IsValid(SICameraManger)) return;

	HighlightInteractables(Nick);
	StartAdaptableAction(Nick);
}


void USI_GameplayAbility_Gizbo_AdaptableAction::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	CancelInteractableHighlight();
	HideMoveToIndicator();
	CancelUpdateIndicatorPositionTimer();
}

void USI_GameplayAbility_Gizbo_AdaptableAction::StartAdaptableAction(const AActor* InActor)
{	
	FVector TraceStart = SICameraManger->GetCameraLocation();
	FVector TraceEnd =  TraceStart + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(SICameraManger);
	QueryParams.AddIgnoredActor(InActor);
	
	FHitResult OutHit;
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECC_WorldDynamic, QueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 30.0f, 0, 1.0f);

	if(bBlockingHit)
	{
		MoveToIndicator = SpawnMoveToIndicator(OutHit.Location);
		StartUpdateIndicatorPositionTimer();
	}	
}

void USI_GameplayAbility_Gizbo_AdaptableAction::StartUpdateIndicatorPositionTimer()
{
		GetWorld()->GetTimerManager().SetTimer(IndicatorPositionTimerHandle, this, &ThisClass::UpdateMoveToIndicatorPosition, UpdateIndicatorDelay, true);
}

void USI_GameplayAbility_Gizbo_AdaptableAction::CancelUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(IndicatorPositionTimerHandle);
}

void USI_GameplayAbility_Gizbo_AdaptableAction::UpdateMoveToIndicatorPosition() const
{
	if(!MoveToIndicator) return;
	
	FHitResult HitResult;
	FVector Start = SICameraManger->GetCameraLocation();
	FVector End = SICameraManger->GetCameraLocation() + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel2);

	//TODO: Liam ... Amend later once GAS is implemented, to check specifically for surfaces that can be traversed.
	if (HitResult.GetActor())
	{
		FVector HitLocation = HitResult.ImpactPoint;
		
		if (HitResult.GetActor()->Implements<USI_MovableInterface>())
		{
			FGameplayEventData Payload;
			Payload.Target = HitResult.GetActor();
			Payload.EventTag = SITag_Ability_PossessMovable;
			Nick->GetSIAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
		}
	MoveToIndicator->SetActorLocation(HitLocation);
	}
}

ASI_MoveToIndicator* USI_GameplayAbility_Gizbo_AdaptableAction::SpawnMoveToIndicator(const FVector InHitLocation)
{
	MoveToIndicatorClass = GetMoveToIndicatorClass();
	if(MoveToIndicatorClass == nullptr)
	{
		MoveToIndicatorClass = GetMoveToIndicatorClass();
	}
	
	if(!IsValid(MoveToIndicator))
	{
		FRotator Rotation = FRotator();
		MoveToIndicator = GetWorld()->SpawnActor<ASI_MoveToIndicator>(MoveToIndicatorClass, InHitLocation, Rotation);
		MoveToIndicator->SetActiveMeshToDefault();
	}
	else
	{
		MoveToIndicator->SetActorHiddenInGame(false);
		MoveToIndicator->SetActorLocation(InHitLocation);
	}
	
	return MoveToIndicator;
}

void USI_GameplayAbility_Gizbo_AdaptableAction::HideMoveToIndicator()
{
	if(MoveToIndicator)
	{
		MoveToIndicator->SetActorHiddenInGame(true);
		MoveToIndicator->SetActiveMeshToDefault();
	}
}

void USI_GameplayAbility_Gizbo_AdaptableAction::HighlightInteractables(const AActor* InActor)
{
	for(TActorIterator<ASI_InteractableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASI_InteractableActor* HitInteractableActor = *ActorItr;
		if(FVector::Distance(HitInteractableActor->GetActorLocation(), InActor->GetActorLocation()) < AdaptableActionMaximumRadius)
		{
			HitInteractableActor->HighlightMesh->SetVisibility(true);	
		}
		else
		{
			HitInteractableActor->HighlightMesh->SetVisibility(false);
		}
	}
}

void USI_GameplayAbility_Gizbo_AdaptableAction::CancelInteractableHighlight()
{
	for(TActorIterator<ASI_InteractableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(ASI_InteractableActor* HitInteractableActor = *ActorItr)
		{
			HitInteractableActor->HighlightMesh->SetVisibility(false);
		}
	}
}

