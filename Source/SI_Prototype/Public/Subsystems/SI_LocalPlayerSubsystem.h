// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "..\SI_NativeGameplayTagLibrary.h"
#include "SI_GameplayTagTypes.h"
#include "SI_LocalPlayerSubsystem.generated.h"

enum class EPlayerMode : uint8;
class USI_PlayerManager;
class USI_AbilityManager;
class USI_GameInstance;
class USI_GameplayTagManager;

using namespace SI_NativeGameplayTagLibrary;

UCLASS()
class SI_PROTOTYPE_API USI_LocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	USI_GameInstance* GameInstance;
	UPROPERTY()
	USI_GameplayTagManager* SITagManager;
	UPROPERTY()
	USI_PlayerManager* PlayerManager;
	UPROPERTY()
	USI_AbilityManager* AbilityManager;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;	

	UFUNCTION()
	virtual void InitializeDelegates();
	UFUNCTION()
	virtual void InitializeDelegateMaps();

	UFUNCTION()
	virtual void OnPlayerStart();
	UFUNCTION()
	virtual void OnGameModeBeginPlay();
	
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload = nullptr);
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload = nullptr);
};
