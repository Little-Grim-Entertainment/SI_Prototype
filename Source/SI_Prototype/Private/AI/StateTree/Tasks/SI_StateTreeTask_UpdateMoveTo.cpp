// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/StateTree/Tasks/SI_StateTreeTask_UpdateMoveTo.h"

#include "AIController.h"
#include "LG_DebugMacros.h"
#include "StateTreeLinker.h"
#include "StateTreeExecutionContext.h"
#include "Characters/SI_NPC.h"
#include "Controllers/SI_NPCController.h"
#include "Navigation/PathFollowingComponent.h"
#include "SI_Prototype/SI_Prototype.h"

FStateTreeUpdateMoveToTask_InstanceData::FStateTreeUpdateMoveToTask_InstanceData()
	: MoveToLocation(FVector::ZeroVector)
	, Nick(nullptr)
	, NPCController(nullptr)
{
	LG_LOG(LogLG_StateTree, VeryVerbose, "FStateTreeUpdateMoveToTask_InstanceData::Constructed")
}

EStateTreeRunStatus FSI_StateTreeTask_UpdateMoveTo::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, VeryVerbose, "FSI_StateTreeTask_UpdateMoveTo::EnterState")
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if(InstanceData.MoveToLocation == FVector::ZeroVector)
	{
		TObjectPtr<ASI_NPC> NPC = Cast<ASI_NPC>(Context.GetOwner());
		if(!IsValid(NPC))
		{
			LG_LOG(LogLG_StateTree, Error, "NPC is invalid cannot change behavior")
			return EStateTreeRunStatus::Failed;
		}
		
		LG_LOG(LogLG_StateTree, Warning, "MoveToLocation isnt set task failed")
		
		NPC->SetCurrentBehavior(SITag_Behavior_Waiting);
		
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.NPCController->MoveToLocation(InstanceData.MoveToLocation);
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSI_StateTreeTask_UpdateMoveTo::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	InstanceData.NPCController->UpdateMovementSpeed(InstanceData.MoveToLocation);
	
	bool Moving = InstanceData.NPCController->GetMoveStatus() == EPathFollowingStatus::Moving;
	return Moving ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;
}

void FSI_StateTreeTask_UpdateMoveTo::ExitState(FStateTreeExecutionContext& Context,	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	ASI_NPC* NPC = Cast<ASI_NPC>(InstanceData.NPCController->GetPawn());
	if(!IsValid(NPC)) {LG_LOG(LogLG_StateTree, Error, "NPC is invalid cannot change behavior") return;}

	NPC->SetCurrentBehavior(SITag_Behavior_TryNextAction);
	
	LG_LOG(LogLG_StateTree, VeryVerbose, "FSI_StateTreeTask_UpdateMoveTo::ExitState") 
}

