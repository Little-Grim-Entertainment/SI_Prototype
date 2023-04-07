// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_NativeGameplayTagLibrary.h"
#include "AoS_GameInstanceSubsystem.generated.h"

enum class EPlayerMode : uint8;

class UAoS_GameInstance;
class AAoS_GameMode;
class UAoS_GameplayTagManager;

using namespace AoS_NativeGameplayTagLibrary;

UCLASS()
class AOS_PROTOTYPE_API UAoS_GameInstanceSubsystem : public UGameInstanceSubsystem
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
	virtual void OnGameInstanceInit();
	UFUNCTION()
	virtual void OnInitGame();
	UFUNCTION()
	virtual void OnPlayerStart();	
	UFUNCTION()
	virtual void OnGameModeBeginPlay();
	UFUNCTION()
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag);
	UFUNCTION()
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag);
};
