// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_MapList.generated.h"

class UAoS_MapData;

UCLASS()
class AOS_PROTOTYPE_API UAoS_MapList : public UDataAsset
{
	GENERATED_BODY()

public:

	UAoS_MapList();
	
	UPROPERTY(EditAnywhere, Category = "Menus")
    TArray<UAoS_MapData*> MenuMaps;
	UPROPERTY(EditAnywhere, Category = "GlassDistrict")
	TArray<UAoS_MapData*> GlassDistrictInteriorMaps;
	UPROPERTY(EditAnywhere, Category = "GlassDistrict")
	TArray<UAoS_MapData*> GlassDistrictExteriorMaps;
	
	UPROPERTY(EditAnywhere, Category = "TestMaps")
	TArray<UAoS_MapData*> TestMaps;

	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<UAoS_MapData*> GetAllMaps();
};
