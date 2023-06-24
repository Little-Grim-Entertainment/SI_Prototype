// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_GameplayAbility.h"
#include "SI_GameplayAbility_Gizbo_AdaptableAction.generated.h"


class ASI_PlayerCameraManager;
class ASI_MoveToIndicator;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbility_Gizbo_AdaptableAction : public USI_GameplayAbility
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
	void UpdateMoveToIndicatorPosition() const;
	ASI_MoveToIndicator* SpawnMoveToIndicator(FVector InHitLocation);
	void HideMoveToIndicator();
	void HighlightInteractables(const AActor* InActor);
	void CancelInteractableHighlight();

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

};
