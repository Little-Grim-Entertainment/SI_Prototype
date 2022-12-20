// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_NPC.h"
#include "AoS_Prototype/AoS_Prototype.h"
#include "BehaviorTree/BehaviorTree.h"

AAoS_NPC::AAoS_NPC()
{
	NothingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Do Nothing Behavior Tree"));
	WanderingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Wandering Behavior Tree"));
	PatrollingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Patrolling Behavior Tree"));
	MovingToTargetTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Moving To Target Behavior Tree"));
	MainTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Main Action Behavior Tree"));
}

UBehaviorTree* AAoS_NPC::GetNothingTree() const
{
	if (IsValid(NothingTree)) { return NothingTree; }
	
	UE_LOG(LogAoSAI, Warning, TEXT("%s : AoS_NPC::GetNothingTree NothingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* AAoS_NPC::GetWanderingTree() const
{
	if (IsValid(WanderingTree)) { return WanderingTree; }
		
	UE_LOG(LogAoSAI, Warning, TEXT("%s : AoS_NPC::GetWanderingTree WanderingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* AAoS_NPC::GetPatrollingTree() const
{
	if (IsValid(PatrollingTree)) { return PatrollingTree; }
		
	UE_LOG(LogAoSAI, Warning, TEXT("%s : AoS_NPC::GetPatrollingTree PatrollingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* AAoS_NPC::GetMovingToTargetTree() const
{
	if (IsValid(MovingToTargetTree)) { return MovingToTargetTree; }
		
	UE_LOG(LogAoSAI, Warning, TEXT("%s : AoS_NPC::GetMovingToTargetTree MovingToTargetTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* AAoS_NPC::GetMainTree() const
{
	if (IsValid(MainTree)) { return MainTree; }
		
	UE_LOG(LogAoSAI, Warning, TEXT("%s : AoS_NPC::GetMainTree MainTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

ECurrentBehavior AAoS_NPC::GetCurrentBehavior() const
{
	return CurrentBehavior;
}

void AAoS_NPC::SetCurrentBehavior(const ECurrentBehavior NewBehavior)
{
	if (CurrentBehavior != NewBehavior)
	{
		//TODO: Might need to refer to the following article, for converting enum values into strings: https://biq.medium.com/type-safe-string-conversions-of-enums-in-unreal-engine-651806fce40
		UE_LOG(LogAoSAI, Display, TEXT("%s : AoS_NPC::SetCurrentBehavior Changing CurrentBehavior from %s to %s"),
			*GetNameSafe(this), *UEnum::GetDisplayValueAsText(CurrentBehavior).ToString(), *UEnum::GetDisplayValueAsText(NewBehavior).ToString());
		CurrentBehavior = NewBehavior;
	}
}

bool AAoS_NPC::IsDoingNothing() const
{
	return CurrentBehavior == ECurrentBehavior::CB_Nothing;
}

bool AAoS_NPC::IsWandering() const
{
	return CurrentBehavior == ECurrentBehavior::CB_Wandering;
}

bool AAoS_NPC::IsPatrolling() const
{
	return CurrentBehavior == ECurrentBehavior::CB_Patrolling;
}

bool AAoS_NPC::IsMovingToTarget() const
{
	return CurrentBehavior == ECurrentBehavior::CB_MovingToTarget;
}

bool AAoS_NPC::IsPerformingMainAction() const
{
	return CurrentBehavior == ECurrentBehavior::CB_PerformingMainAction;
}