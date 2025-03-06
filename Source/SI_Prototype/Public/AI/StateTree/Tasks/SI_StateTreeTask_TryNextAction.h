// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeTaskCommonBase.h"
#include "SI_StateTreeTask_TryNextAction.generated.h"

class ASI_NPCController;
class USI_GameplayTagManager;

UCLASS()
class UStateTreeTryNextActionTask_InstanceData : public UObject
{
	GENERATED_BODY()

	UStateTreeTryNextActionTask_InstanceData() = default;

public:
	
	void OnTreeStart(FStateTreeExecutionContext& Context);
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<ASI_NPCController> NPCController;
	UPROPERTY()
	TObjectPtr<USI_GameplayTagManager> GameplayTagManager = nullptr;
};

USTRUCT(meta = (DisplayName = "SI Next Action Task"))
struct SI_PROTOTYPE_API FSI_StateTreeTask_TryNextAction : public FSI_StateTreeTaskCommonBase
{
	GENERATED_BODY()

	FSI_StateTreeTask_TryNextAction() = default;
	
	using UInstanceDataType = UStateTreeTryNextActionTask_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return UInstanceDataType::StaticClass(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};