// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Nick_CommandRotation.h"

#include "Actors/SI_MoveToIndicator.h"
#include "SI_GameplayTagManager.h"
#include "Characters/SI_Gizbo.h"
#include "Characters/SI_GizboManager.h"

void USI_GameplayAbility_Nick_CommandRotation::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	USI_GizboManager* GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>();
	if(!IsValid(GizboManager)) {LG_LOG(LogSI_Ability, Error, "GizboManager is invalid") return;}
	Gizbo = GizboManager->GetGizbo();

	LG_PRINT(5.f, Green ,"ActivateAbility");
	
	/* TODO: [Pace] Implement when StateTree bug is resolved
	const ISI_AIInterface* AIAbility = Cast<ISI_AIInterface>(this);
	if(!AIAbility) {LG_LOG(LogSI_Ability, Error, "AIAbility is not valid"); return; }

	AIAbility->Execute_OnUpdateTarget(this, MoveToIndicator->GetActorLocation());
	TODO: [Pace] remove these lines when StateTree c++ corrected */
	MoveToIndicator = Cast<ASI_MoveToIndicator>(TriggerEventData->OptionalObject);
	if(!IsValid(MoveToIndicator)) {LG_LOG(LogSI_Ability, Error, "MoveToIndicator is not valid"); return; }
	
	Gizbo->MoveToLocation = MoveToIndicator->GetActorLocation();	
	Gizbo->bDirectedRotation = true;
	Gizbo->MoveToRotation.Yaw = MoveToIndicator->GetActorRotation().Yaw;
	
	USI_GameplayTagManager* SITagManager =  GetWorld()->GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
	if(!IsValid(SITagManager)) {LG_LOG(LogSI_Ability, Error, "SITagManager is not valid"); return; }
	SITagManager->AddNewGameplayTag(SITag_Ability_Gizbo_MoveTo);
	
}

void USI_GameplayAbility_Nick_CommandRotation::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}