// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AoS_CinematicsManager.generated.h"


class UAoS_GameInstance;
class ULevelSequence;
class ULevelSequencePlayer;

enum class EPlayerMode : uint8;

UCLASS()
class AOS_PROTOTYPE_API UAoS_CinematicsManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void PlayCinematic(ULevelSequence* LevelSequenceToPlay, bool bAutoPlay = false, int32 Loop = 0, float PlayRate = 1.0f, float StartOffset = 0.0f, bool bRandomStartTime = false, bool bRestoreState = false, bool bDisableMovementInput = false, bool bDisableLookInput = false, bool bHidePlayer = false, bool bHideHud = false, bool bDisableCameraCuts = false, bool bPauseAtEnd = false);

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
private:

	UPROPERTY()
	ULevelSequencePlayer* CurrentCinematic;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;

	EPlayerMode PreviousPlayerMode;
	
	UFUNCTION()
	void OnCinematicEnd();
		
};
