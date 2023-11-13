// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTask_UpdateMoveTo.h"

#include "AIController.h"
#include "LG_DebugMacros.h"
#include "StateTreeExecutionContext.h"
#include "Controllers/SI_NPCController.h"
#include "Navigation/PathFollowingComponent.h"
#include "StateTreeLinker.h"

EStateTreeRunStatus FSI_StateTreeTask_UpdateMoveTo::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	if(InstanceData.MoveToLocation != FVector::ZeroVector)
	{
		return EStateTreeRunStatus::Failed;
	}
    
	ASI_NPCController& Controller = Context.GetExternalData(ControllerHandle);
	Controller.MoveToLocation(Controller.NPCMemory->GetMoveToLocation());
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSI_StateTreeTask_UpdateMoveTo::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	const ASI_NPCController& Controller = Context.GetExternalData(ControllerHandle);
	bool Moving = Controller.GetMoveStatus() == EPathFollowingStatus::Moving;
	return Moving ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;
}

void FSI_StateTreeTask_UpdateMoveTo::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FSI_StateTreeTaskCommonBase::ExitState(Context, Transition);
}

bool FSI_StateTreeTask_UpdateMoveTo::Link(FStateTreeLinker& Linker)
{
	Linker.LinkExternalData(ControllerHandle);
	return true;
}
