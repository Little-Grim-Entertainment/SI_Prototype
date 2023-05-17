// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SI_ObjectiveData.generated.h"

class USI_MapData;
class USI_CinematicDataAsset;
class USI_VideoDataAsset;

USTRUCT(BlueprintType)
struct FSI_LevelMediaAssignment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(EditCondition="!bHasCinematics"))
	bool bHasVideos;
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bHasVideos"))
	bool bHasCinematics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	FGameplayTag AssociatedLevelTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasVideos", EditConditionHides))
	USI_VideoDataAsset* IntroVideo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasVideos", EditConditionHides))
	USI_VideoDataAsset* OutroVideo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasCinematics", EditConditionHides))
	USI_CinematicDataAsset* IntroCinematic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasCinematics", EditConditionHides))
	USI_CinematicDataAsset*  OutroCinematic;
};

UCLASS(BlueprintType)
class SI_PROTOTYPE_API USI_ObjectiveData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	USI_ObjectiveData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ObjectiveDetails")
	FText ObjectiveDescription;
	UPROPERTY(EditAnywhere, Category = "Media")
	TArray<FSI_LevelMediaAssignment> LevelMediaAssignments;

	bool HasLevelMediaAssignments();
};
