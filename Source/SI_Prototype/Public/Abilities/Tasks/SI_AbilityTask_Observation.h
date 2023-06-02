// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_AbilityTask.h"
#include "SI_AbilityTask_Observation.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask_Observation : public USI_AbilityTask
{
	GENERATED_BODY()

public:
	USI_AbilityTask_Observation (const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks")
	static USI_AbilityTask_Observation* ObservationTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	UGameplayAbility* OwningAbility;
	APlayerController* PlayerController;
	void StartLineTrace();
};
