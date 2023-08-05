// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SI_GameplayTagTypes.h"
#include "..\SI_NativeGameplayTagLibrary.h"
#include "..\Levels\SI_MapGameplayTagLibrary.h"
#include "SI_GameInstanceSubsystem.generated.h"

enum class EPlayerMode : uint8;

class USI_GameInstance;
class ASI_GameMode;
class USI_GameplayTagManager;

using namespace SI_NativeGameplayTagLibrary;
using namespace SI_MapGameplayTagLibrary;

DECLARE_LOG_CATEGORY_EXTERN(LogSI_GameInstanceSubsystem, Log, All);

UCLASS()
class SI_PROTOTYPE_API USI_GameInstanceSubsystem : public UGameInstanceSubsystem
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
	UFUNCTION()
	virtual void OnGameInstanceInit();
	UFUNCTION()
	virtual void OnGameModeBeginPlay();
	UFUNCTION()
	virtual void OnPlayerStart();
	UFUNCTION()
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag);
	UFUNCTION()
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag);

private:

	FGameplayTag PreviouslyAddedTag;
	FGameplayTag PreviouslyRemovedTag;
};
