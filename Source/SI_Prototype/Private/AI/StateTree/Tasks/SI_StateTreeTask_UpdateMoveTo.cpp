// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTask_UpdateMoveTo.h"

#include "AIController.h"
#include "LG_DebugMacros.h"
#include "StateTreeLinker.h"
#include "StateTreeExecutionContext.h"
#include "Controllers/SI_NPCController.h"
#include "Navigation/PathFollowingComponent.h"
#include "SI_Prototype/SI_Prototype.h"

EStateTreeRunStatus FSI_StateTreeTask_UpdateMoveTo::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask_UpdateMoveTo::EnterState")
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if(InstanceData.MoveToLocation != FVector::ZeroVector)
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.NPCController->MoveToLocation(InstanceData.MoveToLocation);
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSI_StateTreeTask_UpdateMoveTo::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	LG_LOG(LogLG_StateTree, Log, "MoveToLocation: %s", *InstanceData.MoveToLocation.ToString())
	
	bool Moving = InstanceData.NPCController->GetMoveStatus() == EPathFollowingStatus::Moving;
	return Moving ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;
}

void FSI_StateTreeTask_UpdateMoveTo::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{

	
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask_UpdateMoveTo::ExitState") 
	FSI_StateTreeTaskCommonBase::ExitState(Context, Transition);
}

