// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_GameplayTagTypes.h"
#include "AoS_GameInstanceSubsystem.generated.h"

enum class EPlayerMode : uint8;

class UAoS_GameInstance;
class AAoS_GameMode;
class UAoS_GameplayTagManager;

UCLASS()
class AOS_PROTOTYPE_API UAoS_GameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	UAoS_GameplayTagManager* AoS_GameplayTagManager;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION()
	virtual void OnGameInstanceInit();
	UFUNCTION()
	virtual void OnInitGame();
	UFUNCTION()
	virtual void OnPlayerStart();	
	UFUNCTION()
	virtual void OnGameModeBeginPlay();
	UFUNCTION()
	virtual void OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode);
	UFUNCTION()
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag);
	UFUNCTION()
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag);
};
