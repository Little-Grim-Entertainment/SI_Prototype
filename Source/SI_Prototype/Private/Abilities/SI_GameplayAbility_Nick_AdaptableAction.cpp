// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Nick_AdaptableAction.h"

#include "Actors/SI_MoveToIndicator.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "Characters/SI_Nick.h"
#include "Controllers/SI_PlayerController.h"
#include "EngineUtils.h" // ActorIterator
#include "SI_GameplayTagManager.h"
#include "Abilities/Tasks/SI_AbilityTask_WaitCancelConfirmHoldTagAdded.h"
#include "Actors/SI_MovableActor.h"
#include "Characters/SI_Gizbo.h"
#include "Characters/SI_GizboManager.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "Interfaces/SI_MovableInterface.h"

void USI_GameplayAbility_Nick_AdaptableAction::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Nick = Cast<ASI_Nick>(ActorInfo->OwnerActor);
	if(!IsValid(Nick)) return;
	PC = Cast<ASI_PlayerController>(Nick->GetController());
	if(!IsValid(PC)) return;
	SICameraManger = Cast<ASI_PlayerCameraManager>(PC->PlayerCameraManager);
	if(!IsValid(SICameraManger)) return;

	USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>();
	if(!IsValid(GizboManager)) {LG_LOG(LogSI_Ability, Error, "GizboManager is invalid") return;}
	Gizbo = GizboManager->GetGizbo();

	WaitCancelConfirmHoldTagAddedTask = USI_AbilityTask_WaitCancelConfirmHoldTagAdded::WaitCancelConfirmGameplayTagAdd(this, SITag_Ability_Cancel, SITag_Ability_Confirm, SITag_Ability_HoldConfirm, nullptr, true);
	WaitCancelConfirmHoldTagAddedTask->CancelTagAdded.AddDynamic(this, &ThisClass::CancelTagReceived);
	WaitCancelConfirmHoldTagAddedTask->ConfirmTagAdded.AddDynamic(this, &ThisClass::ConfirmTagReceived);
	WaitCancelConfirmHoldTagAddedTask->HoldConfirmTagAdded.AddDynamic(this, &ThisClass::HoldConfirmTagReceived);
	WaitCancelConfirmHoldTagAddedTask->ReadyForActivation();
	
	HighlightInteractables(Nick);
	StartAdaptableAction(Nick);
}

void USI_GameplayAbility_Nick_AdaptableAction::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	CancelInteractableHighlight();
	DestroyMoveToIndicator();
	CancelUpdateIndicatorPositionTimer();
	if(IsValid(PC))
	{
		PC->GetSITagManager()->RemoveTag(SITag_UI_HUD_QuickAction_Movable);
	}
	if(IsValid(WaitCancelConfirmHoldTagAddedTask))
	{
		WaitCancelConfirmHoldTagAddedTask->EndTask();
	}
	LG_PRINT(5.f, Green ,"EndAbility");
}

void USI_GameplayAbility_Nick_AdaptableAction::StartAdaptableAction(const AActor* InActor)
{	
	FVector TraceStart = SICameraManger->GetCameraLocation();
	FVector TraceEnd =  TraceStart + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(SICameraManger);
	QueryParams.AddIgnoredActor(InActor);
	
	FHitResult OutHit;
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECC_WorldDynamic, QueryParams);

	if(bBlockingHit)
	{
		if(!IsValid(MoveToIndicator))
		{
			MoveToIndicator = SpawnMoveToIndicator(OutHit.Location);
		}

		StartUpdateIndicatorPositionTimer();
	}	
}

void USI_GameplayAbility_Nick_AdaptableAction::StartUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().SetTimer(IndicatorPositionTimerHandle, this, &ThisClass::UpdateMoveToIndicatorPosition, UpdateIndicatorDelay, true);
}

void USI_GameplayAbility_Nick_AdaptableAction::CancelUpdateIndicatorPositionTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(IndicatorPositionTimerHandle);
}

void USI_GameplayAbility_Nick_AdaptableAction::UpdateMoveToIndicatorPosition()
{
	if(!MoveToIndicator) return;
	
	FHitResult HitResult;
	FVector Start = SICameraManger->GetCameraLocation();
	FVector End = SICameraManger->GetCameraLocation() + SICameraManger->GetActorForwardVector() * AdaptableActionMaximumRadius;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel2);

	if (HitResult.GetActor())
	{
		FVector HitLocation = HitResult.ImpactPoint;
		
		if (HitResult.GetActor()->Implements<USI_MovableInterface>())
		{
			// Update HUD
			if(!bHitActorIsMovable)
			{
				PC->GetSITagManager()->AddNewGameplayTag(SITag_UI_HUD_QuickAction_Movable);
				bHitActorIsMovable = true;
			}
		}
		else
		{
			if(bHitActorIsMovable)
			{
				PC->GetSITagManager()->RemoveTag(SITag_UI_HUD_QuickAction_Movable);
			}
			bHitActorIsMovable = false;
		}
		
		MoveToIndicator->SetActorLocation(HitLocation);
		MoveToIndicator->SetActorRotation(Nick->GetActorRotation());
	}
}

ASI_MoveToIndicator* USI_GameplayAbility_Nick_AdaptableAction::SpawnMoveToIndicator(const FVector InHitLocation)
{
	MoveToIndicatorClass = GetMoveToIndicatorClass();
	if(MoveToIndicatorClass == nullptr)
	{
		MoveToIndicatorClass = GetMoveToIndicatorClass();
	}
	
	if(!IsValid(MoveToIndicator))
	{
		FRotator Rotation = FRotator(0,0,0);
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

void USI_GameplayAbility_Nick_AdaptableAction::DestroyMoveToIndicator()
{
	if(MoveToIndicator)
	{
		MoveToIndicator->Destroy();
	}
}

void USI_GameplayAbility_Nick_AdaptableAction::HighlightInteractables(const AActor* InActor)
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

void USI_GameplayAbility_Nick_AdaptableAction::CancelInteractableHighlight()
{
	for(TActorIterator<ASI_InteractableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(ASI_InteractableActor* HitInteractableActor = *ActorItr)
		{
			HitInteractableActor->HighlightMesh->SetVisibility(false);
		}
	}
}

void USI_GameplayAbility_Nick_AdaptableAction::CancelTagReceived()
{
	LG_PRINT(5.f, Green ,"CancelTagReceived");
	
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}

void USI_GameplayAbility_Nick_AdaptableAction::ConfirmTagReceived()
{
	LG_PRINT(5.f, Green ,"ConfirmTagReceived");
	
	/* //TODO: [Pace] ... Implement when StateTree bug is resolved
	const ISI_AIInterface* AIAbility = Cast<ISI_AIInterface>(this);
	if(!AIAbility) {LG_LOG(LogSI_Ability, Error, "AIAbility is not valid"); return; }

	//AIAbility->Execute_OnUpdateTarget(this, MoveToIndicator->GetActorLocation()); */
	//TODO: [Pace] ...remove this line when StateTree c++ corrected
	Gizbo->MoveToLocation = MoveToIndicator->GetActorLocation();
	
	PC->GetSITagManager()->AddNewGameplayTag(SITag_Ability_Gizbo_MoveTo);
	
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}

void USI_GameplayAbility_Nick_AdaptableAction::HoldConfirmTagReceived()
{
	LG_PRINT(5.f, Green ,"HoldConfirmTagReceived");
	
	FGameplayEventData Payload;
	Payload.OptionalObject = MoveToIndicator;
	Payload.EventTag = SITag_Ability_Nick_AdaptableAction_CommandRotation;
	Nick->GetSIAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
//	PC->GetSITagManager()->AddNewGameplayTag(SITag_Ability_Nick_AdaptableAction_CommandRotation);
	
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}


