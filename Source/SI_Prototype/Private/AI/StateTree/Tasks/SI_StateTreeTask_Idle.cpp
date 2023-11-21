// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTask_Idle.h"

#include "LG_DebugMacros.h"
#include "StateTreeLinker.h"
#include "StateTreeExecutionContext.h"
#include "SI_Prototype/SI_Prototype.h"

EStateTreeRunStatus FSI_StateTreeTask_Idle::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask_Idle::EnterState")

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSI_StateTreeTask_Idle::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	//Do Something here
	return EStateTreeRunStatus::Succeeded;
}

void FSI_StateTreeTask_Idle::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask_Idle::ExitState") 
}

