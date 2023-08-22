// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/SI_AbilityTask.h"
#include "SI_AbilityTask_HighlightInteractables.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask_HighlightInteractables : public USI_AbilityTask
{
	GENERATED_BODY()

	USI_AbilityTask_HighlightInteractables(const FObjectInitializer& ObjectInitializer);
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks")
	static USI_AbilityTask_HighlightInteractables* HighlightInteractablesTask(UGameplayAbility* OwningAbility);

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	void HighlightInteractables();
	void StartHighlightInteractablesTimer();
	void CancelHighlightInteractablesTimer();
	void CancelInteractableHighlight();
	

private:
	UPROPERTY()
	UGameplayAbility* OwningAbility;
	FTimerHandle HighlightInteractablesTimerHandle;
	float HighlightInteractablesDelay = 0.25f;
};
