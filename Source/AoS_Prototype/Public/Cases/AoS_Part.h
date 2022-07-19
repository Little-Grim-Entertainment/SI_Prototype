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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartDetails")
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
	bool GetPartIsActive() const {return bIsActive;}
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Objective*> GetActiveObjectives() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_Objective*> GetAllObjectives() const {return Objectives;}

	void ResetPart();
	void SetPartComplete(bool bPartCompleted);
	void SetPartIsActive(bool bPartIsActive);
	void ActivateObjectives();
	void DeactivateObjectives();
	
private:
	
	bool bIsActive;
	bool bIsComplete;
	
};
