// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AoS_MediaDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_MediaDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media")
	FGameplayTag MediaTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media")
	bool bCanRepeat = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media")
	bool bIsOpeningMedia = false;
};
