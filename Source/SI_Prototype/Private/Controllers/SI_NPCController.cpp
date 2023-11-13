// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SI_NPCController.h"

#include "SI_NativeGameplayTagLibrary.h"
#include "Characters/SI_NPC.h"
#include "Perception/AIPerceptionComponent.h"
#include "SI_Prototype/SI_Prototype.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AI/SI_StateTreeComponentBase.h"

using namespace SI_NativeGameplayTagLibrary;

ASI_NPCController::ASI_NPCController()
{
	//StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"));
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	NPCMemory = new FSI_NPCMemory();
}

void ASI_NPCController::BeginPlay()
{
	Super::BeginPlay();
	
	ConfigurePerception();
	
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ASI_NPCController::OnTargetPerceptionUpdated);
	}
}

void ASI_NPCController::OnPossess(APawn* InPawn)
{
	PossessedNPC = Cast<ASI_NPC>(InPawn);
	if (!IsValid(PossessedNPC))
	{
		UE_LOG(LogSI_AI, Error, TEXT("%s SI_NPCController::OnPossess PossessedNPC is not valid"), *GetNameSafe(InPawn));
		return;
	}
	
	if (!IsValid(PerceptionComp))
	{
		UE_LOG(LogSI_AI, Error, TEXT("%s : SI_NPCController::OnPossess PerceptionComp is not valid"), *GetNameSafe(InPawn));
		return;
	}

	if (!IsValid(SightConfig))
	{
		UE_LOG(LogSI_AI, Error, TEXT("%s : SI_NPCController::OnPossess SightConfig is not valid"), *GetNameSafe(InPawn));
		return;
	}

	if (!IsValid(HearingConfig))
	{
		UE_LOG(LogSI_AI, Error, TEXT("%s : SI_NPCController::OnPossess HearingConfig is not valid"), *GetNameSafe(InPawn));
		return;
	}
	
	if (!IsValid(GetWorld()))
	{
		UE_LOG(LogSI_AI, Error, TEXT("%s : SI_NPCController::OnPossess World is not valid"), *GetNameSafe(InPawn));
		return;
	}
	
	// Only possess once all checks have passed.
	Super::OnPossess(InPawn);

	PossessedNPC->SetCurrentBehavior(SITag_Behavior_Default);
	PerceptionComp->Activate(true);
	//TODO: Ask NPC to set blackboard values etc.
	SetActorTickEnabled(true);
}

void ASI_NPCController::ConfigurePerception()
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

void ASI_NPCController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
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
	}
}