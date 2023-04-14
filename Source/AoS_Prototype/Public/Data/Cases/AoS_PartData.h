// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_PartData.generated.h"

class UAoS_CaseManager;
class UAoS_CharacterData;
class UAoS_ObjectiveData;



UCLASS(BlueprintType)
class AOS_PROTOTYPE_API UAoS_PartData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UAoS_PartData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartDetails")
	FText PartName;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	TArray<UAoS_ObjectiveData*> Objectives;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	bool bCompleteObjectivesInOrder;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	TArray<UAoS_CharacterData*> ActiveCharacters;
	
	UFUNCTION(BlueprintPure)
	bool GetPartIsComplete() const {return bIsComplete;}
	UFUNCTION(BlueprintPure)
	bool GetPartIsActive() const {return bIsActive;}
	UFUNCTION(BlueprintPure)
	TArray<UAoS_ObjectiveData*> GetActiveObjectives() const;
	UFUNCTION(BlueprintPure)
	TArray<UAoS_ObjectiveData*> GetAllObjectives() const {return Objectives;}
	
	void ResetPart();
	void SetPartComplete(bool bPartCompleted);
	void SetPartIsActive(bool bPartIsActive, UAoS_CaseManager* CaseManagerRef);
	void ActivateObjectives(UAoS_CaseManager* CaseManagerRef);
	void DeactivateObjectives();
	
private:
	
	bool bIsActive;
	bool bIsComplete;
	
};
