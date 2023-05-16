// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Actors/SI_InteractableActor.h"
#include "SI_LevelTransition.generated.h"

class UBillboardComponent;
class USI_CinematicDataAsset;
class USI_VideoDataAsset;
class USI_MapData;

UCLASS()
class SI_PROTOTYPE_API ASI_LevelTransition : public ASI_InteractableActor
{
	GENERATED_BODY()

	/** Normal editor sprite. */
	UPROPERTY()
	UBillboardComponent* MapSprite;
	
public:

	ASI_LevelTransition();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels", meta =(Categories = "Map.Title"))
	FGameplayTag MapToLoadTag;
	
protected:

	virtual void OnBeginOverlap(ASI_Nick* InNickActor) override;
	virtual void OnEndOverlap(ASI_Nick* InNickActor) override;
	virtual void OnInteract_Implementation(AActor* Caller) override;
};
