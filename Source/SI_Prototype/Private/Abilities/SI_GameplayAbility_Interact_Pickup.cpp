// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Interact_Pickup.h"

#include "SI_AITypes.h"
#include "Characters/SI_NPC.h"
#include "Controllers/SI_NPCController.h"

void USI_GameplayAbility_Interact_Pickup::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogLG_Ability,"Ability Activated");

	ASI_NPC* NPC = Cast<ASI_NPC>(ActorInfo->OwnerActor);
	if(!IsValid(NPC)) {LG_LOG(LogLG_Ability, Error, "Actor is not valid"); return;}
	ASI_NPCController* AIController = Cast<ASI_NPCController>(NPC->GetController());
	if(!IsValid(AIController)) {LG_LOG(LogLG_Ability, Error, "AIController is not valid"); return; }
	FSI_NPCMemory* NPCMemory = AIController->GetNPCMemory();
	if(*NPCMemory == FSI_NPCMemory()) {LG_LOG(LogLG_Ability, Error, "NPCMemory is Empty"); return; }
	
	TObjectPtr<AActor> TargetPickup = NPCMemory->GetTargetObject();
	if(!IsValid(TargetPickup)) {LG_LOG(LogLG_Ability, Error, "TargetPickup is not valid"); return; }
	
	USkeletalMeshComponent* NPCMesh = NPC->GetMesh();
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	TargetPickup->SetActorEnableCollision(false);
	TargetPickup->AttachToComponent(NPCMesh, AttachRules, "Socket_Chest");
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void USI_GameplayAbility_Interact_Pickup::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
