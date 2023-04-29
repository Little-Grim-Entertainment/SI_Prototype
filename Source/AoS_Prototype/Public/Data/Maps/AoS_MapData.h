// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Types.h"
#include "GameplayTagContainer.h"
#include "AoS_MapData.generated.h"

class UAoS_MusicManager;
class UAoS_CinematicDataAsset;
class UAoS_VideoDataAsset;
class UAoS_UserWidget;

UCLASS()
class AOS_PROTOTYPE_API UAoS_MapData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	FString MapName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails", meta=(Categories = "Map"))
	FGameplayTag MapTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails", meta=(Categories = "Map.Type"))
	FGameplayTag MapType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	TSoftObjectPtr<UWorld> Map;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	FAoS_MusicSettings BackgroundMusicSettings;
};
