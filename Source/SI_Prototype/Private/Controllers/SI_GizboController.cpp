// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SI_GizboController.h"

#include "Characters/SI_Nick.h"
#include "Characters/SI_NPC.h"
#include "SI_Prototype/SI_Prototype.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

ASI_GizboController::ASI_GizboController() : ASI_NPCController_Interactable()
{
	
}

void ASI_GizboController::BeginPlay()
{
	Super::BeginPlay();

	ConfigurePerception();
}

void ASI_GizboController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ASI_GizboController::ConfigurePerception()
{
	//TODO: Play around with / discuss values with Jeff, Manuel etc.
	if (SightConfig)
	{
		SightConfig->SightRadius = 2000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		//SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	}

	if (HearingConfig)
	{
		HearingConfig->HearingRange = 2000.0f;
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

void ASI_GizboController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor && Stimulus.IsValid() && Stimulus.IsActive())
	{
		//TODO: ASK JEFF about using a getter function from the manager instead here. would require adding manager pointer to header etc. 
		if ((Nick = Cast<ASI_Nick>(Actor)) != nullptr)
		{
			switch (Stimulus.Type)
			{
				case 0: //Sight
					{
						//TODO: Amend accordingly
						if (bCanFollow)
						{
						
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
		else
		{
			switch (Stimulus.Type)
			{
				case 0: //Sight
					{
						//TODO: Amend accordingly
						if (bCanMoveTo)
						{
							
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
	}
}


