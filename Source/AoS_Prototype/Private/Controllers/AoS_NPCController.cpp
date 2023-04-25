// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_NPCController.h"
#include "Characters/AoS_NPC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "AoS_Prototype/AoS_Prototype.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AAoS_NPCController::AAoS_NPCController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	ConfigurePerception();
}

void AAoS_NPCController::BeginPlay()
{
	Super::BeginPlay();

	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAoS_NPCController::OnTargetPerceptionUpdated);
	}
}

void AAoS_NPCController::OnPossess(APawn* InPawn)
{
	PossessedNPC = Cast<AAoS_NPC>(InPawn);
	if (!IsValid(PossessedNPC))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s AoS_NPCController::OnPossess PossessedNPC is not valid"), *GetNameSafe(InPawn));
		return;
	}
	
	UBehaviorTree* MainTree = PossessedNPC->GetMainTree();

	if (!IsValid(MainTree))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s : AoS_NPCController::OnPossess MainTree is not valid"), *GetNameSafe(InPawn));
		return;
	}

#if WITH_EDITORONLY_DATA
	if (!IsValid(MainTree->BTGraph))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s : AoS_NPCController::OnPossess MainTree->BTGraph is not valid"), *GetNameSafe(InPawn));
		return;
	}
#endif

	if (!IsValid(PerceptionComp))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s : AoS_NPCController::OnPossess PerceptionComp is not valid"), *GetNameSafe(InPawn));
		return;
	}

	if (!IsValid(SightConfig))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s : AoS_NPCController::OnPossess SightConfig is not valid"), *GetNameSafe(InPawn));
		return;
	}

	if (!IsValid(HearingConfig))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s : AoS_NPCController::OnPossess HearingConfig is not valid"), *GetNameSafe(InPawn));
		return;
	}
	
	if (!IsValid(GetWorld()))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s : AoS_NPCController::OnPossess World is not valid"), *GetNameSafe(InPawn));
		return;
	}
	
	// Only possess once all checks have passed.
	Super::OnPossess(InPawn);

	PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_PerformingMainAction);
	PerceptionComp->Activate(true);
	RunBehaviorTree(MainTree);
	//TODO: Ask NPC to set blackboard values etc.
	SetActorTickEnabled(true);
}

void AAoS_NPCController::UpdateBehaviorTree()
{
	if (!IsValid(PossessedNPC))
	{
		UE_LOG(LogAoSAI, VeryVerbose, TEXT("%s : AoS_NPCController::UpdateBehaviorTree PossessedNPC reference is not valid"), *GetNameSafe(GetPawn()));
		return;
	}

	UBehaviorTree* SelectedTree = PossessedNPC->GetNothingTree();

	if (PossessedNPC->IsWandering()) { SelectedTree = PossessedNPC->GetWanderingTree(); }

	//TODO: Should also check for a patrol path
	if (PossessedNPC->IsPatrolling()) { SelectedTree = PossessedNPC->GetPatrollingTree(); }

	if (PossessedNPC->IsMovingToTarget()) { SelectedTree = PossessedNPC->GetMovingToTargetTree(); }

	//TODO: Should also check for a current target
	if (PossessedNPC->IsPerformingMainAction()) { SelectedTree = PossessedNPC->GetMainTree(); }

	if (!IsValid(SelectedTree) || !IsValid(SelectedTree->BlackboardAsset))
	{
		UE_LOG(LogAoSAI, Error, TEXT("%s : AoS_NPCController::UpdateBehaviorTree SelectedTree is not valid"), *GetNameSafe(GetPawn()));
		return;
	}

	UE_LOG(LogAoSAI, VeryVerbose, TEXT("%s : AoS_NPCController::UpdateBehaviorTree Running Behavior Tree : %s"), *GetNameSafe(GetPawn()), *SelectedTree->GetName());

	// Handles BehaviorTreeComponent and BlackboardComponent internally
	RunBehaviorTree(SelectedTree);
}

//TODO: Get the Actor's perception, check its info, and for sight (index 0), check whether it was successfully sensed
// Split functions into acquiring / losing a target, and sensing / or losing sense of a given target
void AAoS_NPCController::SetSeenTarget(AActor* Actor)
{
	if (Blackboard && Actor)
	{
		Blackboard->SetValueAsObject(BlackboardTargetKey, Actor);
		Blackboard->SetValueAsBool(BlackboardCanSeeTargetKey, true);
	}
}

void AAoS_NPCController::SetLostTarget()
{
	if (Blackboard)
	{
		Blackboard->SetValueAsObject(BlackboardTargetKey, nullptr);
		Blackboard->SetValueAsBool(BlackboardCanSeeTargetKey, false);
	}
}

void AAoS_NPCController::ConfigurePerception()
{
	//TODO: Play around with / discuss values with Jeff, Manuel etc.
	if (SightConfig)
	{
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 200.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	}

	if (HearingConfig)
	{
		HearingConfig->HearingRange = 1000.0f;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	}

	if (PerceptionComp && SightConfig && HearingConfig)
	{
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->ConfigureSense(*HearingConfig);
		PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AAoS_NPCController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor && Stimulus.IsValid() && Stimulus.IsActive())
	{
		switch (Stimulus.Type)
		{
			case 0: //Sight
				{
					//TODO: Implement
					break;
				}
			case 1: //Hearing
				{
					//TODO: Implement
					break;
				}
			default:
				{
					//TODO: Implement
					break;
				}
		}

		UpdateBehaviorTree();
	}
}