// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SI_NPCController.h"

#include "LG_DebugMacros.h"
#include "SI_Prototype/SI_Prototype.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Characters/SI_NPC.h"
#include "Characters/SI_Nick.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

using namespace SI_NativeGameplayTagLibrary;

ASI_NPCController::ASI_NPCController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
}



void ASI_NPCController::BeginPlay()
{
	Super::BeginPlay();
	
	ConfigurePerception();
	BuildMemory();
	NPCMovementHelper = new FSI_NPCMovementHelper();
	
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
		LG_LOG(LogLG_AI, Error, "%s PossessedNPC is not valid", *GetNameSafe(InPawn));
		return;
	}
	
	if (!IsValid(PerceptionComp))
	{
		LG_LOG(LogLG_AI, Error, "%s PerceptionComp is not valid", *GetNameSafe(InPawn));
		return;
	}

	if (!IsValid(SightConfig))
	{
		LG_LOG(LogLG_AI, Error, "%s SightConfig is not valid", *GetNameSafe(InPawn));
		return;
	}

	if (!IsValid(HearingConfig))
	{
		LG_LOG(LogLG_AI, Error, "%s HearingConfig is not valid", *GetNameSafe(InPawn));
		return;
	}
	
	if (!IsValid(GetWorld()))
	{
		LG_LOG(LogLG_AI, Error, "%s  World is not valid", *GetNameSafe(InPawn));
		return;
	}
	
	// Only possess once all checks have passed.
	Super::OnPossess(InPawn);

	PossessedNPC->SetCurrentBehavior(SITag_Behavior_Default);
	PerceptionComp->Activate(true);
	
	SetActorTickEnabled(true);
}

void ASI_NPCController::ConfigurePerception()
{
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

void ASI_NPCController::BuildMemory()
{
	ASI_Nick* Nick = Cast<ASI_Nick>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!IsValid(Nick)) {LG_LOG(LogLG_Ability, Error, "Nick is invalid unable to build NPCMemory") return;}

	NPCMemory = new FSI_NPCMemory();
	NPCMemory->SetNick(Nick);
}

void ASI_NPCController::UpdateMovementSpeed(const FVector& InMoveToLocation, float InTargetSpeed)
{
	if (PossessedNPC)
	{
		const float CurrentDistanceToTarget = FVector::Dist(InMoveToLocation, GetPawn()->GetActorLocation());
		NPCMovementHelper->CalculateMovementSpeed(CurrentDistanceToTarget, InTargetSpeed);
		
		UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(PossessedNPC->GetMovementComponent());
		MovementComponent->MaxWalkSpeed = NPCMovementHelper->CalculateMovementSpeed(CurrentDistanceToTarget, InTargetSpeed);
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
