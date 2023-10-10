// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeEvaluatorBase.h"
#include "SI_StateTreeEvaluator_GizboDefault.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_StateTreeEvaluator_GizboDefault : public USI_StateTreeEvaluatorBase
{
	GENERATED_BODY()

	virtual void TreeStart(FStateTreeExecutionContext& Context) override;
};
