// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Objective.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class AOS_PROTOTYPE_API UAoS_Objective : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UAoS_Objective();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ObjectiveDetails")
	FText ObjectiveDescription;
	
	UFUNCTION(BlueprintPure)
	bool GetObjectiveComplete() const {return bIsComplete;}
	UFUNCTION(BlueprintPure)
	bool GetObjectiveIsActive() const {return bIsActive;}

	void ResetObjective();
	void SetObjectiveComplete(bool bObjectiveCompleted);
	void SetObjectiveIsActive(bool bObjectiveIsActive);

private:

	bool bIsActive;
	bool bIsComplete;
	
};
