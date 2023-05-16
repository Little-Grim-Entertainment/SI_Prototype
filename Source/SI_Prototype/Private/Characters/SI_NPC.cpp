// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC.h"
#include "SI_Prototype/SI_Prototype.h"
#include "BehaviorTree/BehaviorTree.h"

ASI_NPC::ASI_NPC()
{
	NothingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Do Nothing Behavior Tree"));
	WanderingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Wandering Behavior Tree"));
	PatrollingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Patrolling Behavior Tree"));
	MovingToTargetTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Moving To Target Behavior Tree"));
	MainTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Main Action Behavior Tree"));
}

UBehaviorTree* ASI_NPC::GetNothingTree() const
{
	if (IsValid(NothingTree)) { return NothingTree; }
	
	UE_LOG(LogSIAI, Warning, TEXT("%s : SI_NPC::GetNothingTree NothingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetWanderingTree() const
{
	if (IsValid(WanderingTree)) { return WanderingTree; }
		
	UE_LOG(LogSIAI, Warning, TEXT("%s : SI_NPC::GetWanderingTree WanderingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetPatrollingTree() const
{
	if (IsValid(PatrollingTree)) { return PatrollingTree; }
		
	UE_LOG(LogSIAI, Warning, TEXT("%s : SI_NPC::GetPatrollingTree PatrollingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetMovingToTargetTree() const
{
	if (IsValid(MovingToTargetTree)) { return MovingToTargetTree; }
		
	UE_LOG(LogSIAI, Warning, TEXT("%s : SI_NPC::GetMovingToTargetTree MovingToTargetTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetMainTree() const
{
	if (IsValid(MainTree)) { return MainTree; }
		
	UE_LOG(LogSIAI, Warning, TEXT("%s : SI_NPC::GetMainTree MainTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

ECurrentBehavior ASI_NPC::GetCurrentBehavior() const
{
	return CurrentBehavior;
}

void ASI_NPC::SetCurrentBehavior(const ECurrentBehavior NewBehavior)
{
	if (CurrentBehavior != NewBehavior)
	{
		//TODO: Might need to refer to the following article, for converting enum values into strings: https://biq.medium.com/type-safe-string-conversions-of-enums-in-unreal-engine-651806fce40
		UE_LOG(LogSIAI, Display, TEXT("%s : SI_NPC::SetCurrentBehavior Changing CurrentBehavior from %s to %s"),
			*GetNameSafe(this), *UEnum::GetDisplayValueAsText(CurrentBehavior).ToString(), *UEnum::GetDisplayValueAsText(NewBehavior).ToString());
		CurrentBehavior = NewBehavior;
	}
}

bool ASI_NPC::IsDoingNothing() const
{
	return CurrentBehavior == ECurrentBehavior::CB_Nothing;
}

bool ASI_NPC::IsWandering() const
{
	return CurrentBehavior == ECurrentBehavior::CB_Wandering;
}

bool ASI_NPC::IsPatrolling() const
{
	return CurrentBehavior == ECurrentBehavior::CB_Patrolling;
}

bool ASI_NPC::IsMovingToTarget() const
{
	return CurrentBehavior == ECurrentBehavior::CB_MovingToTarget;
}

bool ASI_NPC::IsPerformingMainAction() const
{
	return CurrentBehavior == ECurrentBehavior::CB_PerformingMainAction;
}