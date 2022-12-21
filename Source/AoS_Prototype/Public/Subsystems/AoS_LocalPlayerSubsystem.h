// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "AoS_LocalPlayerSubsystem.generated.h"

enum class EPlayerMode : uint8;

class UAoS_GameInstance;

UCLASS()
class AOS_PROTOTYPE_API UAoS_LocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;	
	
	UFUNCTION()
	virtual void OnGameModeBeginPlay();
	UFUNCTION()
	virtual void OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode);
};
