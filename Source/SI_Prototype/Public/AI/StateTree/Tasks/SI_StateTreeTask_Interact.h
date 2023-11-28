#pragma once

#include "CoreMinimal.h"
#include "SI_StateTreeTaskCommonBase.h"
#include "SI_StateTreeTask_Interact.generated.h"

USTRUCT()
struct FStateTreeInteractTask_InstanceData
{
	GENERATED_BODY()

	FStateTreeInteractTask_InstanceData();
	
};

USTRUCT(meta = (DisplayName = "SI Interact Task"))
struct SI_PROTOTYPE_API FStateTreeInteractTask : public FSI_StateTreeTaskCommonBase
{
	GENERATED_BODY()

	FStateTreeInteractTask() = default;
	
	using FInstanceDataType = FStateTreeInteractTask_InstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};