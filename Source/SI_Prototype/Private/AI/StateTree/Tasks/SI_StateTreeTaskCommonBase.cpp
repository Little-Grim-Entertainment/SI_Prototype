// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTaskCommonBase.h"

DEFINE_LOG_CATEGORY(LogSI_StateTreeTask)


EStateTreeRunStatus FSI_StateTreeTaskCommonBase::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	return EStateTreeRunStatus::Running;
}
