// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_GizboController.h"

#include "Characters/AoS_Nick.h"
#include "Characters/AoS_NPC.h"
#include "AoS_Prototype/AoS_Prototype.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AAoS_GizboController::AAoS_GizboController() : AAoS_NPCController_Interactable()
{
	
}

void AAoS_GizboController::BeginPlay()
{
	Super::BeginPlay();
}

void AAoS_GizboController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AAoS_GizboController::UpdateBehaviorTree()
{
	Super::UpdateBehaviorTree();
}

void AAoS_GizboController::ConfigurePerception()
{
	//TODO: Play around with / discuss values with Jeff, Manuel etc.
	if (SightConfig)
	{
		SightConfig->SightRadius = 5000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 1000.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		//SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	}

	if (HearingConfig)
	{
		HearingConfig->HearingRange = 5000.0f;
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

void AAoS_GizboController::SetSeenTarget(AActor* Actor)
{
	Super::SetSeenTarget(Actor);
}

void AAoS_GizboController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor && Stimulus.IsValid() && Stimulus.IsActive())
	{
		if (auto* Nick = Cast<AAoS_Nick>(Actor))
		{
			switch (Stimulus.Type)
			{
				case 0: //Sight
					{
						//TODO: Amend accordingly
						if (bCanFollow)
						{
							SetSeenTarget(Actor);
						}
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
		}

		UpdateBehaviorTree();
	}
}

void AAoS_GizboController::ToggleFollow()
{
	bCanFollow = !bCanFollow;
	
	if (!bCanFollow && PossessedNPC->IsPerformingMainAction())
	{
		// Stop Gizbo from following Nick
		PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_Nothing);
		SetLostTarget();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Gizbo: Follow Action Disabled")));
		UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_GizboController::ToggleFollow Follow Action Disabled"), *GetNameSafe(GetPawn()));
	}
	else
	{
		// Allow Gizbo to follow Nick
		PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_PerformingMainAction);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Gizbo: Follow Action Enabled")));
		UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_GizboController::ToggleFollow Follow Action Enabled"), *GetNameSafe(GetPawn()));
	}

	UpdateBehaviorTree();
}