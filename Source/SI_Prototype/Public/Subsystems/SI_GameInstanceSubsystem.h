// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTag/SI_GameplayTagTypes.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "..\Levels\SI_MapGameplayTagLibrary.h"
#include "SI_GameInstanceSubsystem.generated.h"


//enum class EPlayerMode : uint8;
class USI_GameInstance;
class ASI_GameMode;
class USI_GameplayTagManager;
class USI_GizboManager;

using namespace SI_NativeGameplayTagLibrary;
using namespace SI_MapGameplayTagLibrary;

UCLASS()
class SI_PROTOTYPE_API USI_GameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	USI_GameInstance* GameInstance;
	UPROPERTY()
	USI_GameplayTagManager* SITagManager;
	UPROPERTY()
	USI_GizboManager* GizboManager;


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

	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload = nullptr);
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload = nullptr);

private:

	FGameplayTag PreviouslyAddedTag;
	FGameplayTag PreviouslyRemovedTag;
};
