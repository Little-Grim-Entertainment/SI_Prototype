// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeTaskCommonBase.h"
#include "SI_StateTreeTask_Idle.generated.h"

UCLASS()
class UStateTreeIdleTask_InstanceData : public UObject
{
	GENERATED_BODY()

	UStateTreeIdleTask_InstanceData() = default;

public:
	void OnTreeStart(FStateTreeExecutionContext& Context);
	UFUNCTION()
	void UpdateBehaviorBool(FGameplayTag& InBehaviorTag);
	
	UPROPERTY()
	bool bBehaviorTagUpdated = false;
};

USTRUCT(meta = (DisplayName = "SI Idle Task"))
struct SI_PROTOTYPE_API FSI_StateTreeTask_Idle : public FSI_StateTreeTaskCommonBase
{
	GENERATED_BODY()

	FSI_StateTreeTask_Idle() = default;
	
	using UInstanceDataType = UStateTreeIdleTask_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return UInstanceDataType::StaticClass(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};