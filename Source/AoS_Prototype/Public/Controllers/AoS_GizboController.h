// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/AoS_NPCController_Interactable.h"
#include "AoS_GizboController.generated.h"

/**
 * AI Controller specifically for Gizbo, dervied from base NPC Controllers, for AoS Prototype
 */
UCLASS()
class AOS_PROTOTYPE_API AAoS_GizboController : public AAoS_NPCController_Interactable
{
	GENERATED_BODY()
	
public:
	AAoS_GizboController();

	void ToggleFollow();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	//TODO: Should also define what to do OnUnPossess
	virtual void UpdateBehaviorTree() override;
	virtual void ConfigurePerception() override;
	virtual void SetSeenTarget(AActor* Actor) override;
	//TODO: Will need to add support for AI Perception Teams, if we want NPCs to belong to specific factions, and have interactions between each other.
	
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
	
	/*
	 * TODO: Check the Google Drive file (AoS: Gizbo Commands) for the latest information on what is required
	 * https://docs.google.com/document/d/1XdFo3CqsEQOG0aSNXEq8UJg4rayv5C0FNY6DQo2j7_I
	 * 
	 * 'Move To' implementation ideas:
	 * Once a location has been selected, check whether the 'Move To' target is valid, and can be traversed to (i.e. FHitResult from ray trace - Controller->GetHitResultUnderCursorByChannel)
	 * If true, then Gizbo should find an appropriate path, and move towards the location (Controller->MoveToLocation)
	 * If the player tells Gizbo to wait, then the current target should be deleted, and Gizbo should cease performing any action
	 */
	
private:
	bool bCanFollow = true;
};
