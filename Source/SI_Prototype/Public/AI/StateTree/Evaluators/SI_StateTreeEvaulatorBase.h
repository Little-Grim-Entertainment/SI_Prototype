// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"
#include "SI_StateTreeEvaulatorBase.generated.h"

USTRUCT()
struct FSI_StateTreeEvaluatorBase_InstanceData
{
	GENERATED_BODY()
};

USTRUCT(Meta=(Hidden))
struct SI_PROTOTYPE_API FSI_StateTreeEvaulatorBase : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()

	FSI_StateTreeEvaulatorBase() = default;
	
	using FInstanceDataType = FSI_StateTreeEvaluatorBase_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
};