// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UAoS_CaseList.generated.h"

class UAoS_CaseData;

UCLASS()
class AOS_PROTOTYPE_API UUAoS_CaseList : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "Menus")
	TArray<UAoS_CaseData*> StoryCases;
	UPROPERTY(EditAnywhere, Category = "NovaLuxDistrict")
	TArray<UAoS_CaseData*> NovaLuxDistrictCases;
	UPROPERTY(EditAnywhere, Category = "TestMaps")
	TArray<UAoS_CaseData*> TestCases;

	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<UAoS_CaseData*> GetAllCases();
};
