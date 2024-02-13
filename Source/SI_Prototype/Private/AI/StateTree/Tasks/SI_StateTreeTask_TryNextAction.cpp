// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTask_TryNextAction.h"

#include "LG_DebugMacros.h"
#include "StateTreeLinker.h"
#include "StateTreeExecutionContext.h"
#include "Characters/SI_NPC.h"
#include "Controllers/SI_NPCController.h"
#include "GameplayTags/SI_GameplayTagManager.h"
#include "SI_Prototype/SI_Prototype.h"

void UStateTreeTryNextActionTask_InstanceData::OnTreeStart(FStateTreeExecutionContext& Context)
{
	GameplayTagManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GameplayTagManager>();
}

EStateTreeRunStatus FSI_StateTreeTask_TryNextAction::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask_NextAction::EnterState")

	UInstanceDataType* InstanceData = Context.GetInstanceDataPtr<UInstanceDataType>(*this);
	InstanceData->OnTreeStart(Context);
	
	ASI_NPCController* NPCController = InstanceData->NPCController;
	if(!IsValid(NPCController))
	{
		LG_LOG(LogLG_StateTree, Error, "NPCController is invalid cannot change behavior")
		return EStateTreeRunStatus::Failed;
	}
	
	FSI_NPCMemory* NPCMemory = NPCController->NPCMemory;
	if(!NPCMemory)
	{
		LG_LOG(LogLG_StateTree, Error, "NPCMemory is invalid cannot change behavior")
		return EStateTreeRunStatus::Failed;
	}
	
	if(NPCMemory->GetNextActionTag() == SITag_None)
	{
		return EStateTreeRunStatus::Succeeded;
	}

	USI_GameplayTagManager* SITagManager = InstanceData->GameplayTagManager;
	if(!SITagManager)
	{
		LG_LOG(LogLG_StateTree, Error, "Tag Manager is invalid cannot change behavior")
		return EStateTreeRunStatus::Failed;
	}
	
	SITagManager->AddNewGameplayTag_Internal(NPCMemory->GetNextActionTag(), NPCMemory->GetAbilityCaller(),NPCMemory->GetAbilityInstigator());
	
	return EStateTreeRunStatus::Succeeded;
}

void FSI_StateTreeTask_TryNextAction::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask__NextAction::ExitState")

	UInstanceDataType* InstanceData = Context.GetInstanceDataPtr<UInstanceDataType>(*this);
	
	ASI_NPCController* NPCController = InstanceData->NPCController;
	if(!IsValid(NPCController))
	{
		LG_LOG(LogLG_StateTree, Error, "NPCController is invalid cannot change behavior")
		return;
	}
	
	FSI_NPCMemory* NPCMemory = NPCController->NPCMemory;
	if(!NPCMemory)
	{
		LG_LOG(LogLG_StateTree, Error, "NPCMemory is invalid cannot change behavior")
		return;
	}
	USI_GameplayTagManager* SITagManager =  NPCController->GetSITagManager();

	//todo find method to get caller target in here cleanly
	SITagManager->AddNewGameplayTag_Internal(NPCMemory->GetNextActionTag(), NPCMemory->GetAbilityCaller(), NPCMemory->GetAbilityInstigator());
	NPCMemory->SetNextActionTag(SITag_None);

	ASI_NPC* NPC = Cast<ASI_NPC>(InstanceData->NPCController->GetPawn());
	if(!IsValid(NPC)) {LG_LOG(LogLG_StateTree, Error, "NPC is invalid cannot change behavior") return;}

	NPC->SetCurrentBehavior(SITag_Behavior_Waiting);
}

