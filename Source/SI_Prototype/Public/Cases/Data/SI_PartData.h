// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SI_PartData.generated.h"

class USI_CaseManager;
class USI_CharacterData;
class USI_ObjectiveData;



UCLASS(BlueprintType)
class SI_PROTOTYPE_API USI_PartData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	USI_PartData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartDetails")
	FText PartName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PartDetails")
	FText PartNumber;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	TArray<USI_ObjectiveData*> Objectives;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	bool bCompleteObjectivesInOrder;
	UPROPERTY(EditAnywhere, Category = "PartDetails")
	TArray<USI_CharacterData*> ActiveCharacters;

	UFUNCTION(BlueprintPure)
	TArray<USI_ObjectiveData*> GetAllObjectives() const {return Objectives;}
};
