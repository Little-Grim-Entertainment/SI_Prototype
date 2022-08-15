// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_MapList.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_MapList : public UDataAsset
{
	GENERATED_BODY()

public:

	UAoS_MapList();
	
	UPROPERTY(EditAnywhere, Category = "Levels")
	TArray<TSoftObjectPtr<UWorld>> Maps;
	
};
