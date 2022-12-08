// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/AoS_InteractableActor.h"
#include "AoS_LevelTransition.generated.h"

class UAoS_CinematicDataAsset;
class UAoS_VideoDataAsset;
class UAoS_MapData;

UCLASS()
class AOS_PROTOTYPE_API AAoS_LevelTransition : public AAoS_InteractableActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	FString PlayerStartTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	UAoS_MapData* MapToLoad;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	UAoS_VideoDataAsset* OutroVideo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	UAoS_CinematicDataAsset* OutroCinematic;
	
protected:

	virtual void OnBeginOverlap(AAoS_Nick* InNickActor) override;
	virtual void OnEndOverlap(AAoS_Nick* InNickActor) override;
	virtual void OnInteract_Implementation(AActor* Caller) override;
	
};
