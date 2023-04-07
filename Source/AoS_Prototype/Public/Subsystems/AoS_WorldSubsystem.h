// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AoS_NativeGameplayTagLibrary.h"
#include "AoS_WorldSubsystem.generated.h"

enum class EPlayerMode : uint8;

class UAoS_GameInstance;
class UAoS_GameplayTagManager;

using namespace AoS_NativeGameplayTagLibrary;

UCLASS()
class AOS_PROTOTYPE_API UAoS_WorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	UAoS_GameplayTagManager* AoSTagManager;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	virtual void InitializeDelegates();
	UFUNCTION()
	virtual void InitializeDelegateMaps();
	UFUNCTION()
	virtual void OnGameModeBeginPlay();
	UFUNCTION()
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag);
	UFUNCTION()
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag);
		
};
