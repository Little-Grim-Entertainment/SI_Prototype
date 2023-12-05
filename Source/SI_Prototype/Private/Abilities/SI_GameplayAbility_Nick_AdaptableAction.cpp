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
#include "Characters/SI_GizboManager.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "Interfaces/SI_MovableInterface.h"
#include "Characters/SI_Gizbo.h"
#include "Controllers/SI_NPCController.h"

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
	if(!IsValid(GizboManager)) {LG_LOG(LogLG_Ability, Error, "GizboManager is invalid") return;}
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
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}

void USI_GameplayAbility_Nick_AdaptableAction::ConfirmTagReceived()
{	
	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);

	ASI_NPCController* AIController = Cast<ASI_NPCController>(Gizbo->GetController());
	if(!IsValid(AIController)) {LG_LOG(LogLG_Ability, Error, "AIController is not valid"); return; }

	FVector NewMoveToLocation = MoveToIndicator->GetActorLocation();
	AIController->GetNPCMemory()->SetMoveToLocation(NewMoveToLocation);
	
	PC->GetSITagManager()->AddNewGameplayTag(SITag_Ability_AI_MoveTo, Payload);
	
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}

void USI_GameplayAbility_Nick_AdaptableAction::HoldConfirmTagReceived()
{
	FSITagPayload* Payload = new FSITagPayload(Nick, Gizbo);

	ASI_NPCController* AIController = Cast<ASI_NPCController>(Gizbo->GetController());
	if(!IsValid(AIController)) {LG_LOG(LogLG_Ability, Error, "AIController is not valid"); return; }	
	FSI_NPCMemory* NPCMemory = AIController->GetNPCMemory();
	if(*NPCMemory == FSI_NPCMemory()) {LG_LOG(LogLG_Ability, Error, "NPCMemory is Empty"); return; }

	FVector NewMoveToLocation = MoveToIndicator->GetActorLocation();
	NPCMemory->SetMoveToLocation(NewMoveToLocation);
	
	PC->GetSITagManager()->AddNewGameplayTag(SITag_Ability_AI_MoveTo, Payload);
	
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}