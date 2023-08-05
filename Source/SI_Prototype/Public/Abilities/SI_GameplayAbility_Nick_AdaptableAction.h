// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "SI_GameplayAbility_Nick_AdaptableAction.generated.h"

class ASI_Nick;
class ASI_PlayerController;
class USI_GameplayAbility_Interact_Pickup;
class USI_GameplayAbility_Interact_Drop;
class USI_GameplayAbility_Interact_Push;
class USI_GameplayAbility_Interact_Pull;
class ASI_PlayerCameraManager;
class ASI_MoveToIndicator;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_Nick_AdaptableAction : public USI_GameplayAbility
{
	GENERATED_BODY()

public:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	TSubclassOf<ASI_MoveToIndicator> GetMoveToIndicatorClass() const { return MoveToIndicatorClass;}

protected:
	void StartAdaptableAction(const AActor* InActor);
	void StartUpdateIndicatorPositionTimer();
	void CancelUpdateIndicatorPositionTimer();
	void UpdateMoveToIndicatorPosition();
	ASI_MoveToIndicator* SpawnMoveToIndicator(const FVector InHitLocation);
	void DestroyMoveToIndicator();
	void HighlightInteractables(const AActor* InActor);
	void CancelInteractableHighlight();

	UPROPERTY()
	USI_GameplayAbility_Interact_Pull* PullAbility;
	UPROPERTY()
	USI_GameplayAbility_Interact_Push* PushAbility;
	UPROPERTY()
	USI_GameplayAbility_Interact_Drop* DropAbility;
	UPROPERTY()
	USI_GameplayAbility_Interact_Pickup* PickupAbility;

	UPROPERTY()
	ASI_Nick* Nick;
	UPROPERTY()
	ASI_PlayerController* PC;
	UPROPERTY()
	ASI_MoveToIndicator* MoveToIndicator;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_MoveToIndicator> MoveToIndicatorClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AdaptableActionMaximumRadius = 2000.0f;
	UPROPERTY()
	ASI_PlayerCameraManager* SICameraManger;
	float UpdateIndicatorDelay = 0.001f;
	FTimerHandle IndicatorPositionTimerHandle;
	bool bIsActive;
	bool bHitActorIsMovable;
};
