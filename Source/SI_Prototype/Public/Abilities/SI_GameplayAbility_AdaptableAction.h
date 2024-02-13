// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "Interfaces/SI_AIInterface.h"
#include "SI_GameplayAbility_AdaptableAction.generated.h"

class ASI_Gizbo;
class USI_AbilityTask_WaitCancelConfirmHoldTagAdded;
class ASI_Nick;
class ASI_PlayerController;
class ASI_PlayerCameraManager;
class ASI_MoveToIndicator;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_AdaptableAction : public USI_GameplayAbility, public ISI_AIInterface
{
	GENERATED_BODY()

public:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	TSubclassOf<ASI_MoveToIndicator> GetMoveToIndicatorClass() const { return MoveToIndicatorClass;}

protected:

	/** Initiates an adaptable action based on the provided actor's location.
	* This function begins an adaptable action by calculating a trace from the camera's location towards a specific distance. It checks for potential obstructions and responds accordingly:
	* - If there is an obstruction, it creates or updates a 'MoveToIndicator' to guide the action towards the obstacle.
	* - If the 'MoveToIndicator' is not valid, it spawns a new one at the location of the obstruction.
	* - Additionally, it starts a timer to continuously update the indicator's position to guide the action effectively.
	* @param InActor The actor used as a reference for initiating the adaptable action.
	*/
	void StartAdaptableAction(const AActor* InActor);
	void StartUpdateIndicatorPositionTimer();
	void CancelUpdateIndicatorPositionTimer();
	void UpdateMoveToIndicatorPosition();
	ASI_MoveToIndicator* SpawnMoveToIndicator(const FVector InHitLocation);
	void DestroyMoveToIndicator();

	/** Highlights interactable actors within a specified radius of the given actor.
	* This function iterates through all ASI_InteractableActor instances in the current world and checks their distance from the provided actor.
	* If an actor is within the specified radius (AdaptableActionMaximumRadius), its highlight mesh is set to be visible; otherwise, it's hidden.
	* @param InActor The actors location used as the center point for the radius calculation.
	* This function is used to visually indicate interactable objects that are within the interaction range of the given actor.
	*/
	void HighlightInteractables(const AActor* InActor);

	/** Cancels the highlighting of interactable actors.
	* This function iterates through all ASI_InteractableActor instances in the current world and hides their highlight meshes, effectively canceling their visual highlighting.
	*/
	void CancelInteractableHighlight();

	/** Called when the Cancel tag has been received and ends the ability.
	*/
	UFUNCTION()
	void CancelTagReceived();

	/** Called when the confirm tag has been received.
	* It first checks if the current object implements the 'ISI_AIInterface' interface. If not, it logs an error and exits.
	* If the interface is implemented, it calls 'OnUpdateTargetLocation' via the interface, updates gameplay tags, and ends the ability.
	*/
	UFUNCTION()
	void ConfirmTagReceived();

	/** Called after HoldConfirm tag is received.
	* It first checks if the current object implements the 'ISI_AIInterface' interface. If the interface is not implemented, it logs an error and exits.
	* If the interface is implemented, it executes 'OnUpdateTargetLocation' via the interface, and then ends the ability.
	*/
	UFUNCTION()
	void HoldConfirmTagReceived();

	UPROPERTY()
	USI_AbilityTask_WaitCancelConfirmHoldTagAdded* WaitCancelConfirmHoldTagAddedTask;
	
	UPROPERTY()
	TObjectPtr<ASI_Nick> Nick;
	UPROPERTY()
	TObjectPtr<ASI_Gizbo> Gizbo;
	UPROPERTY()
	TObjectPtr<ASI_PlayerController> PC;
	UPROPERTY(EditAnywhere, Category = "Ability")
	TObjectPtr<ASI_MoveToIndicator> MoveToIndicator;
	UPROPERTY(EditAnywhere, Category = "Ability")
	TSubclassOf<ASI_MoveToIndicator> MoveToIndicatorClass;
	UPROPERTY(EditAnywhere, Category = "Ability")
	float AdaptableActionMaximumRadius = 2000.0f;
	UPROPERTY()
	TObjectPtr<ASI_PlayerCameraManager> SICameraManger;
	UPROPERTY()
	TObjectPtr<AActor> OverlappedActor = nullptr;

private:
	float UpdateIndicatorDelay = 0.001f;
	FTimerHandle IndicatorPositionTimerHandle;
	bool bIsActive;
	bool bHitActorIsMovable;
	bool bHitActorIsPickupable
	;
};