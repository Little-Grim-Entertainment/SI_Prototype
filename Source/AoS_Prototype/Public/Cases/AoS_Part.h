// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Part.generated.h"

class AAoS_Character;
class UAoS_Objective;

UCLASS(BlueprintType)
class AOS_PROTOTYPE_API UAoS_Part : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UAoS_Part();

	UPROPERTY(EditAnywhere, Category = "PartDetails")
	FText PartName;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	TArray<UAoS_Objective*> Objectives;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	bool bCompleteObjectivesInOrder;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	TArray<TSubclassOf<AAoS_Character>> ActiveCharacters;
	
	UFUNCTION(BlueprintPure)
	bool GetPartIsComplete() const {return bIsComplete;}
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Objective*> GetActiveObjectives() const {return ActiveObjectives;}
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Objective*> GetAllObjectives() const {return Objectives;}

	void SetPartComplete(bool bPartCompleted);
	void SetPartIsActive(bool bPartIsActive);
	void ActivateObjectives();
	void DeactivateObjectives();
	
private:

	UPROPERTY()
	TArray<UAoS_Objective*> ActiveObjectives;

	bool bIsActive;
	bool bIsComplete;
	
};
