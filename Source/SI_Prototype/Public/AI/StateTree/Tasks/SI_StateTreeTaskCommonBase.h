// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "SI_StateTreeTaskCommonBase.generated.h"

USTRUCT()
struct FStateTreeTaskCommonBase_InstanceData
{
	GENERATED_BODY()
};

USTRUCT(Meta=(Hidden))
struct SI_PROTOTYPE_API FSI_StateTreeTaskCommonBase : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FSI_StateTreeTaskCommonBase() = default;
	
	using FInstanceDataType = FStateTreeTaskCommonBase_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

};