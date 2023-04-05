// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AoS_Objective.generated.h"

class UAoS_MapData;
class UAoS_CinematicDataAsset;
class UAoS_VideoDataAsset;

USTRUCT(BlueprintType)
struct FLevelMediaAssignment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(EditCondition="!bHasCinematics"))
	bool bHasVideos;
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bHasVideos"))
	bool bHasCinematics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	FGameplayTag AssociatedLevelTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasVideos", EditConditionHides))
	UAoS_VideoDataAsset* IntroVideo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasVideos", EditConditionHides))
	UAoS_VideoDataAsset* OutroVideo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasCinematics", EditConditionHides))
	UAoS_CinematicDataAsset* IntroCinematic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos", meta=(EditCondition="bHasCinematics", EditConditionHides))
	UAoS_CinematicDataAsset*  OutroCinematic;
};

UCLASS(BlueprintType)
class AOS_PROTOTYPE_API UAoS_Objective : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UAoS_Objective();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ObjectiveDetails")
	FText ObjectiveDescription;
	UPROPERTY(EditAnywhere, Category = "Media")
	TArray<FLevelMediaAssignment> LevelMediaAssignments;
	
	UFUNCTION(BlueprintPure)
	bool GetObjectiveComplete() const {return bIsComplete;}
	UFUNCTION(BlueprintPure)
	bool GetObjectiveIsActive() const {return bIsActive;}
	
	void ResetObjective();
	void SetObjectiveComplete(bool bObjectiveCompleted);
	void SetObjectiveIsActive(bool bObjectiveIsActive);

	void SetMediaLevelAssignments();
	void ClearMediaLevelAssignments();
	void ResetMediaLevelAssignments();

private:

	bool bIsActive;
	bool bIsComplete;
	
};
