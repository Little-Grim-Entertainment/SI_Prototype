// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AoS_NPCController.generated.h"

class AAoS_NPC;
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

/**
 * Base NPC Controller for AoS Prototype
 */
UCLASS()
class AOS_PROTOTYPE_API AAoS_NPCController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAoS_NPCController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	//TODO: Should also define what to do OnUnPossess
	virtual void UpdateBehaviorTree();
	virtual void ConfigurePerception();
	virtual void SetSeenTarget(AActor* Actor);
	//TODO: Will need to add support for AI Perception Teams, if we want NPCs to belong to specific factions, and have interactions between each other.

	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAIPerceptionComponent> PerceptionComp = nullptr;
	TObjectPtr<UAISenseConfig_Sight> SightConfig = nullptr;
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<AAoS_NPC> PossessedNPC = nullptr;

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	FName BlackboardTargetKey = "Target";

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	FName BlackboardCanSeeTargetKey = "CanSeeTarget";
};
