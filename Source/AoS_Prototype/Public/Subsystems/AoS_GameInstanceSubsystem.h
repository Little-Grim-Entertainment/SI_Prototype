// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_GameInstanceSubsystem.generated.h"

enum class EPlayerMode : uint8;

class UAoS_GameInstance;

UCLASS()
class AOS_PROTOTYPE_API UAoS_GameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION()
	virtual void OnGameInstanceInit();
	UFUNCTION()
	virtual void OnGameModeBeginPlay();
	UFUNCTION()
	virtual void OnPlayerModeChanged(EPlayerMode NewPlayerMode);
};
