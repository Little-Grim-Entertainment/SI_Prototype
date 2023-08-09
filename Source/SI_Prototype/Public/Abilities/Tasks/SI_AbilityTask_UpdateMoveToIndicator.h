// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_AbilityTask.h"
#include "SI_AbilityTask_UpdateMoveToIndicator.generated.h"

class ASI_PlayerCameraManager;
class ASI_Nick;
class ASI_PlayerController;
class ASI_MoveToIndicator;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask_UpdateMoveToIndicator : public USI_AbilityTask
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	
protected:

	ASI_MoveToIndicator* SpawnMoveToIndicator(FVector InHitLocation);
	TSubclassOf<ASI_MoveToIndicator> GetMoveToIndicatorClass() const { return MoveToIndicatorClass;}
	void DestroyMoveToIndicator();
	void StartAdaptableAction(const AActor* InActor);
	void StartUpdateIndicatorPositionTimer();
	void CancelUpdateIndicatorPositionTimer();
	void UpdateMoveToIndicatorPosition();
	
	UPROPERTY()
	ASI_MoveToIndicator* MoveToIndicator;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASI_MoveToIndicator> MoveToIndicatorClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AdaptableActionMaximumRadius = 2000.0f;
	UPROPERTY()
	ASI_PlayerCameraManager* SICameraManger;
	UPROPERTY()
	ASI_Nick* Nick;
	UPROPERTY()
	ASI_PlayerController* PC;
	
	bool bIsActive;
	bool bHitActorIsMovable;
	float UpdateIndicatorDelay = 0.001f;
	FTimerHandle IndicatorPositionTimerHandle;
};
