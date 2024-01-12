// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTask_Idle.h"

#include "LG_DebugMacros.h"
#include "StateTreeLinker.h"
#include "StateTreeExecutionContext.h"
#include "Characters/SI_NPC.h"
#include "SI_Prototype/SI_Prototype.h"

void UStateTreeIdleTask_InstanceData::OnTreeStart(FStateTreeExecutionContext& Context)
{
	LG_LOG(LogLG_StateTree, Log, "UStateTreeIdleTask_InstanceData::OnTreeStart")
	ASI_NPC* NPC = Cast<ASI_NPC>(Context.GetOwner());
	
	NPC->OnBehaviorTagUpdated.AddUObject(this, &UStateTreeIdleTask_InstanceData::UpdateBehaviorBool);
}

void UStateTreeIdleTask_InstanceData::UpdateBehaviorBool(FGameplayTag& InBehaviorTag)
{
	if(InBehaviorTag != SITag_Behavior_Waiting || InBehaviorTag != SITag_Behavior_Default)
	{
		bBehaviorTagUpdated = true;
	}
}

EStateTreeRunStatus FSI_StateTreeTask_Idle::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask_Idle::EnterState")
	
	UInstanceDataType* InstanceData = Context.GetInstanceDataPtr<UInstanceDataType>(*this);
	InstanceData->bBehaviorTagUpdated = false;
	InstanceData->OnTreeStart(Context);

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FSI_StateTreeTask_Idle::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	UInstanceDataType* InstanceData = Context.GetInstanceDataPtr<UInstanceDataType>(*this);

	if(InstanceData->bBehaviorTagUpdated)
	{
		return EStateTreeRunStatus::Succeeded;
	}

	return EStateTreeRunStatus::Running;
}

void FSI_StateTreeTask_Idle::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, Log, "FSI_StateTreeTask_Idle::ExitState") 
}

