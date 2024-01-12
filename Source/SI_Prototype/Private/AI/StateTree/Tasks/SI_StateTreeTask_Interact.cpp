#include "AI/StateTree/Tasks/SI_StateTreeTask_Interact.h"

EStateTreeRunStatus FStateTreeInteractTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStateTreeInteractTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	bool CheckSomething = true;
	
	return CheckSomething ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;
}

void FStateTreeInteractTask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	
}
