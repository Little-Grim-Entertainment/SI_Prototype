// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SI_MapList.generated.h"

class USI_MapData;

UCLASS()
class SI_PROTOTYPE_API USI_MapList : public UDataAsset
{
	GENERATED_BODY()

public:

	USI_MapList();

	UPROPERTY(EditAnywhere, Category = "PersistentLevel")
	USI_MapData* PersistentLevel;
	UPROPERTY(EditAnywhere, Category = "Menus")
    TArray<USI_MapData*> MenuMaps;
	UPROPERTY(EditAnywhere, Category = "NovaLuxDistrict")
	TArray<USI_MapData*> NovaLuxDistrictInteriorMaps;
	UPROPERTY(EditAnywhere, Category = "NovaLuxDistrict")
	TArray<USI_MapData*> NovaLuxDistrictExteriorMaps;
	UPROPERTY(EditAnywhere, Category = "TestMaps")
	TArray<USI_MapData*> TestMaps;

	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<USI_MapData*> GetAllMaps();
};
