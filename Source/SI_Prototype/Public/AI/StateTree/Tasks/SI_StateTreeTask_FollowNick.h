// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeTaskCommonBase.h"
#include "SI_StateTreeTask_FollowNick.generated.h"

class ASI_NPCController;
class ASI_Nick;
class USI_GameplayTagManager;

USTRUCT()
struct FStateTreeFollowNickTask_InstanceData
{
	GENERATED_BODY()

	FStateTreeFollowNickTask_InstanceData();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<ASI_Nick> Nick;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<ASI_NPCController> NPCController; 
};

USTRUCT(meta = (DisplayName = "SI Follow Nick Task"))
struct SI_PROTOTYPE_API FStateTreeFollowNickTask : public FSI_StateTreeTaskCommonBase
{
	GENERATED_BODY()

	FStateTreeFollowNickTask() = default;
	
	using FInstanceDataType = FStateTreeFollowNickTask_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};