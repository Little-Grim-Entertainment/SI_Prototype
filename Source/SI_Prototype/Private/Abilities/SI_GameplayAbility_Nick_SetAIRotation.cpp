// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Nick_SetAIRotation.h"

#include "Actors/SI_MoveToIndicator.h"
#include "SI_GameplayTagManager.h"
#include "Abilities/Tasks/SI_AbilityTask_WaitCancelConfirmHoldTagAdded.h"
#include "Characters/SI_Gizbo.h"
#include "Characters/SI_GizboManager.h"
#include "Characters/SI_Nick.h"
#include "Controllers/SI_PlayerController.h"

void USI_GameplayAbility_Nick_SetAIRotation::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	LG_PRINT(5.f, Green ,"ActivateAbility");
	
	Nick = Cast<ASI_Nick>(ActorInfo->OwnerActor);
	if(!IsValid(Nick)) return;
	PC = Cast<ASI_PlayerController>(Nick->GetController());
	if(!IsValid(PC)) return;

	WaitCancelConfirmHoldTagAddedTask = USI_AbilityTask_WaitCancelConfirmHoldTagAdded::WaitCancelConfirmGameplayTagAdd(this, SITag_Ability_Cancel, SITag_Ability_Confirm, SITag_Ability_HoldConfirm, nullptr, true);
	WaitCancelConfirmHoldTagAddedTask->CancelTagAdded.AddDynamic(this, &ThisClass::CancelTagReceived);
	WaitCancelConfirmHoldTagAddedTask->ConfirmTagAdded.AddDynamic(this, &ThisClass::ConfirmTagReceived);
	WaitCancelConfirmHoldTagAddedTask->ReadyForActivation();
	
	Nick->Controller->SetIgnoreMoveInput(true);
	
	USI_GameplayTagManager* SITagManager =  GetWorld()->GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
	if(!IsValid(SITagManager)) {LG_LOG(LogSI_Ability, Error, "SITagManager is not valid"); return; }
	
	SITagManager->AddNewGameplayTag(SITag_Ability_AI_MoveTo);	
}

void USI_GameplayAbility_Nick_SetAIRotation::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Nick->Controller->SetIgnoreMoveInput(false);
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}

void USI_GameplayAbility_Nick_SetAIRotation::CancelTagReceived()
{
	LG_PRINT(5.f, Green ,"CancelTagReceived");
	
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}

void USI_GameplayAbility_Nick_SetAIRotation::ConfirmTagReceived()
{
	LG_PRINT(5.f, Green ,"ConfirmTagReceived");
	
	const ISI_AIInterface* AIAbility = Cast<ISI_AIInterface>(this);
	if(!AIAbility) {LG_LOG(LogSI_Ability, Error, "AIAbility is not valid"); return; }

	AIAbility->Execute_OnUpdateTargetRotation(this, MoveToIndicator->GetActorRotation());
	
	EndAbility(ActiveSpecHandle, GetCurrentActorInfo(), CurrentActivationInfo, true, true);
}