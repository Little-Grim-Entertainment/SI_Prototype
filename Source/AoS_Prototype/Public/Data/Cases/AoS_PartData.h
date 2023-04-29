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
	TArray<UAoS_ObjectiveData*> GetAllObjectives() const {return Objectives;}
};
