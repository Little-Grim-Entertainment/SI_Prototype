// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeEvaulatorBase.h"
#include "SI_AITypes.h"
#include "StateTreeExecutionTypes.h"
#include "SI_StateTreeNPCEvaluatorBase.generated.h"

class ASI_NPC;
class ASI_NPCController;
class ASI_Nick;

//-----------------------------------------------------
// USI_StateTreeNPCEvaluatorBase_InstanceData
//-----------------------------------------------------
UCLASS()
class USI_StateTreeNPCEvaluatorBase_InstanceData : public UObject
{
	GENERATED_BODY()

public:
	USI_StateTreeNPCEvaluatorBase_InstanceData() = default;
	
	void OnTreeStart(FStateTreeExecutionContext& Context);
	UFUNCTION()
	void SetMoveToLocation(FVector& InMoveToLocation);
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<ASI_NPC> NPC;
	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<ASI_NPCController> NPCController;
	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<ASI_Nick> Nick;
	UPROPERTY(EditAnywhere, Category = "Output")
	FVector MoveToLocation;
};

//-----------------------------------------------------
// FSI_StateTreeNPCEvaluatorBase
//-----------------------------------------------------
USTRUCT(meta = (DisplayName = "SIStateTreeNPCEvaluatorBase"))
struct SI_PROTOTYPE_API FSI_StateTreeNPCEvaluatorBase : public FSI_StateTreeEvaulatorBase
{
	GENERATED_BODY()

	FSI_StateTreeNPCEvaluatorBase() = default;
	
	using UInstanceDataType = USI_StateTreeNPCEvaluatorBase_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return UInstanceDataType::StaticClass(); }
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void TreeStop(FStateTreeExecutionContext& Context) const override;
};
