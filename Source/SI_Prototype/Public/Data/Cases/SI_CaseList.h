// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SI_CaseList.generated.h"

class USI_CaseData;

UCLASS()
class SI_PROTOTYPE_API USI_CaseList : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "Menus")
	TArray<USI_CaseData*> StoryCases;
	UPROPERTY(EditAnywhere, Category = "NovaLuxDistrict")
	TArray<USI_CaseData*> NovaLuxDistrictCases;
	UPROPERTY(EditAnywhere, Category = "TestMaps")
	TArray<USI_CaseData*> TestCases;

	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<USI_CaseData*> GetAllCases();
};
