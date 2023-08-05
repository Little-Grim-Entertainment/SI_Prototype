// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_NPC.h"
#include "SI_Prototype/SI_Prototype.h"
#include "BehaviorTree/BehaviorTree.h"
#include "SI_NativeGameplayTagLibrary.h"

using namespace SI_NativeGameplayTagLibrary;

ASI_NPC::ASI_NPC()
{
	NothingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Do Nothing Behavior Tree"));
	WanderingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Wandering Behavior Tree"));
	PatrollingTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Patrolling Behavior Tree"));
	MovingToTargetTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Moving To Target Behavior Tree"));
	DefaultTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("Main Action Behavior Tree"));
}

UBehaviorTree* ASI_NPC::GetNothingTree() const
{
	if (IsValid(NothingTree)) { return NothingTree; }
	
	UE_LOG(LogSI_AI, Warning, TEXT("%s : SI_NPC::GetNothingTree NothingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetWanderingTree() const
{
	if (IsValid(WanderingTree)) { return WanderingTree; }
		
	UE_LOG(LogSI_AI, Warning, TEXT("%s : SI_NPC::GetWanderingTree WanderingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetPatrollingTree() const
{
	if (IsValid(PatrollingTree)) { return PatrollingTree; }
		
	UE_LOG(LogSI_AI, Warning, TEXT("%s : SI_NPC::GetPatrollingTree PatrollingTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetMovingToTargetTree() const
{
	if (IsValid(MovingToTargetTree)) { return MovingToTargetTree; }
		
	UE_LOG(LogSI_AI, Warning, TEXT("%s : SI_NPC::GetMovingToTargetTree MovingToTargetTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

UBehaviorTree* ASI_NPC::GetMainTree() const
{
	if (IsValid(DefaultTree)) { return DefaultTree; }
		
	UE_LOG(LogSI_AI, Warning, TEXT("%s : SI_NPC::GetMainTree MainTree is not valid"), *GetNameSafe(this));
	return nullptr;
}

FGameplayTag& ASI_NPC::GetCurrentBehaviorTag()
{
	return CurrentBehaviorTag;
}

void ASI_NPC::SetCurrentBehavior(const FGameplayTag NewBehaviorTag)
{
	if (CurrentBehaviorTag != NewBehaviorTag)
	{
		CurrentBehaviorTag = NewBehaviorTag;
	}
}

bool ASI_NPC::IsDoingNothing() const
{
	return CurrentBehaviorTag == SITag_Behavior_None;
}

bool ASI_NPC::IsWandering() const
{
	return CurrentBehaviorTag == SITag_Behavior_Wandering;
}

bool ASI_NPC::IsPatrolling() const
{
	return CurrentBehaviorTag == SITag_Behavior_Patrolling;
}

bool ASI_NPC::IsMovingToTarget() const
{
	return CurrentBehaviorTag == SITag_Behavior_MoveTo;
}

bool ASI_NPC::IsPerformingMainAction() const
{
	return CurrentBehaviorTag == SITag_Behavior_Default;
}