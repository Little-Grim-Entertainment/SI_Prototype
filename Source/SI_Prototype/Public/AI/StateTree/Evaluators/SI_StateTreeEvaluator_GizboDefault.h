// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeNPCEvaluatorBase.h"
#include "SI_StateTreeEvaluator_GizboDefault.generated.h"

USTRUCT(BlueprintType)
struct FSI_StateTreeEvaluator_GizboDefault_InstanceData
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType, meta = (DisplayName = "SIStateTreeEvaluator_GizboDefault"))
struct SI_PROTOTYPE_API FSI_StateTreeEvaluator_GizboDefault : public FSI_StateTreeNPCEvaluatorBase
{
	GENERATED_BODY()

	FSI_StateTreeEvaluator_GizboDefault() = default;
	
	using FInstanceDataType = FSI_StateTreeEvaluator_GizboDefault_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
};


