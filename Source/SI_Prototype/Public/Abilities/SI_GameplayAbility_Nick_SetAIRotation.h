// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "Interfaces/SI_AIInterface.h"
#include "SI_GameplayAbility_Nick_SetAIRotation.generated.h"

class ASI_PlayerController;
class ASI_Nick;
class ASI_MoveToIndicator;
class ASI_Gizbo;
class ASI_RotationIndicator;
class USI_AbilityTask_WaitCancelConfirmHoldTagAdded;

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_Nick_SetAIRotation : public USI_GameplayAbility, public ISI_AIInterface
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	TSubclassOf<ASI_RotationIndicator> GetRotationIndicatorClass() const { return RotationIndicatorClass;}

protected:
	UFUNCTION()
	void CancelTagReceived();
	UFUNCTION()
	void ConfirmTagReceived();
	
	UPROPERTY()
	USI_AbilityTask_WaitCancelConfirmHoldTagAdded* WaitCancelConfirmHoldTagAddedTask;
	
	UPROPERTY()
	ASI_Nick* Nick;
	UPROPERTY()
	ASI_Gizbo* Gizbo;
	UPROPERTY()
	ASI_PlayerController* PC;
	
	UPROPERTY()
	ASI_MoveToIndicator* MoveToIndicator;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_RotationIndicator> RotationIndicatorClass;
	
};
