// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SI_GameplayTagTypes.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "SI_WorldSubsystem.generated.h"

enum class EPlayerMode : uint8;

class USI_GameInstance;
class USI_GameplayTagManager;

using namespace SI_NativeGameplayTagLibrary;

UCLASS()
class SI_PROTOTYPE_API USI_WorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	USI_GameInstance* GameInstance;
	UPROPERTY()
	USI_GameplayTagManager* SITagManager;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	virtual void InitializeDelegates();
	UFUNCTION()
	virtual void InitializeDelegateMaps();

	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload = nullptr);
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload = nullptr);
};
