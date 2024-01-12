// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTask_FollowNick.h"

#include "AIController.h"
#include "LG_DebugMacros.h"
#include "StateTreeLinker.h"
#include "StateTreeExecutionContext.h"
#include "Characters/SI_Nick.h"
#include "Characters/SI_NPC.h"
#include "Controllers/SI_NPCController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "SI_Prototype/SI_Prototype.h"

FStateTreeFollowNickTask_InstanceData::FStateTreeFollowNickTask_InstanceData()
	: Nick(nullptr)
	, NPCController(nullptr)
{
	LG_LOG(LogLG_StateTree, VeryVerbose, "FStateTreeUpdateMoveToTask_InstanceData::Constructed")
}

EStateTreeRunStatus FStateTreeFollowNickTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	LG_LOG(LogLG_StateTree, VeryVerbose, "FSI_StateTreeTask_UpdateMoveTo::EnterState")
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if(InstanceData.Nick == nullptr)
	{
		TObjectPtr<ASI_NPC> NPC = Cast<ASI_NPC>(Context.GetOwner());
		if(!IsValid(NPC))
		{
			LG_LOG(LogLG_StateTree, Error, "NPC is invalid cannot change behavior")
			return EStateTreeRunStatus::Failed;
		}
		
		LG_LOG(LogLG_StateTree, Warning, "Nick is null, set task failed")
		
		NPC->SetCurrentBehavior(SITag_Behavior_Waiting);
		
		return EStateTreeRunStatus::Failed;
	}
	
	InstanceData.NPCController->MoveToActor(InstanceData.Nick);
	
	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStateTreeFollowNickTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	ASI_Nick* NickPtr = InstanceData.Nick.Get();
	FVector NickCurrentLocation = NickPtr->GetActorLocation();
	UCharacterMovementComponent* NickMovementComponent =  Cast<UCharacterMovementComponent>(NickPtr->GetMovementComponent());
	float NickCurrentSpeed = NickMovementComponent->GetMaxSpeed();
	
	InstanceData.NPCController->UpdateMovementSpeed(NickCurrentLocation, NickCurrentSpeed);
	
	bool Moving = InstanceData.NPCController->GetMoveStatus() == EPathFollowingStatus::Moving;
	return Moving ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;
}

void FStateTreeFollowNickTask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{	
	LG_LOG(LogLG_StateTree, VeryVerbose, "FSI_StateTreeTask_UpdateMoveTo::ExitState") 
}

