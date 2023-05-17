// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/SI_NPCController_Interactable.h"
#include "SI_GizboController.generated.h"

class ASI_Nick;
class ASI_MoveToIndicator;
/**
 * AI Controller specifically for Gizbo, dervied from base NPC Controllers, for SI Prototype
 */
UCLASS()
class SI_PROTOTYPE_API ASI_GizboController : public ASI_NPCController_Interactable
{
	GENERATED_BODY()
	
public:
	ASI_GizboController();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ToggleFollow();
	UFUNCTION(BlueprintCallable, Category = "AI") //TODO: Possibly remove these specifiers later if not needed
	void ToggleMoveTo();
	UFUNCTION(BlueprintCallable, Category = "AI")
	void ToggleWait();
	TSubclassOf<ASI_MoveToIndicator> GetMoveToIndicatorClass() const;
	void ReachedMoveToIndicator();
	
	UPROPERTY()
	ASI_Nick* Nick;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_MoveToIndicator> MoveToIndicatorClass;

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
	 * TODO: Check the Google Drive file (SI: Gizbo Commands) for the latest information on what is required
	 * https://docs.google.com/document/d/1XdFo3CqsEQOG0aSNXEq8UJg4rayv5C0FNY6DQo2j7_I
	 * 
	 * 'Move To' implementation ideas:
	 * Once a location has been selected, check whether the 'Move To' target is valid, and can be traversed to (i.e. FHitResult from ray trace - Controller->GetHitResultUnderCursorByChannel)
	 * If true, then Gizbo should find an appropriate path, and move towards the location (Controller->MoveToLocation)
	 * If the player tells Gizbo to wait, then the current target should be deleted, and Gizbo should cease performing any action
	 */
	
private:
	bool bCanFollow = true;
	bool bCanMoveTo = false;
};
