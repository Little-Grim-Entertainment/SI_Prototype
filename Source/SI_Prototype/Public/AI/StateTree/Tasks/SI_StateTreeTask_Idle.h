// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeTaskCommonBase.h"
#include "SI_StateTreeTask_Idle.generated.h"



USTRUCT()
struct FStateTreeIdleTask_InstanceData
{
	GENERATED_BODY()

	FStateTreeIdleTask_InstanceData() = default;
	
};

USTRUCT(meta = (DisplayName = "SIIdleTask"))
struct SI_PROTOTYPE_API FSI_StateTreeTask_Idle : public FSI_StateTreeTaskCommonBase
{
	GENERATED_BODY()

	FSI_StateTreeTask_Idle() = default;
	
	using FInstanceDataType = FStateTreeIdleTask_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};