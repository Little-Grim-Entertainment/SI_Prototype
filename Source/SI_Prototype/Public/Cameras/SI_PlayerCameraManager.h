// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Camera/PlayerCameraManager.h"
#include "SI_PlayerCameraManager.generated.h"

class USI_LevelManager;
class USI_GameInstance;
class USI_GameplayTagManager;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	UPROPERTY()
	USI_GameInstance* GameInstance;
	UPROPERTY()
	USI_GameplayTagManager* SITagManager;

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag);
	UFUNCTION()
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag);
};
