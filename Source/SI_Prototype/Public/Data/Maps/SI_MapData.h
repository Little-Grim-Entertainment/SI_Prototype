// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SI_Types.h"
#include "GameplayTagContainer.h"
#include "SI_MapData.generated.h"

class USI_MusicManager;
class USI_CinematicDataAsset;
class USI_VideoDataAsset;
class USI_UserWidget;

UCLASS()
class SI_PROTOTYPE_API USI_MapData : public UDataAsset
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
	FSI_MusicSettings BackgroundMusicSettings;
};
