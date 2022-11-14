// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_CinematicsManager.generated.h"


class ULevelSequence;
class ULevelSequencePlayer;

UCLASS()
class AOS_PROTOTYPE_API UAoS_CinematicsManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void PlayCinematic(ULevelSequence* LevelSequenceToPlay, bool bAutoPlay = false, int32 Loop = 0, float PlayRate = 1.0f, float StartOffset = 0.0f, bool bRandomStartTime = false, bool bRestoreState = false, bool bDisableMovementInput = false, bool bDisableLookInput = false, bool bHidePlayer = false, bool bHideHud = false, bool bDisableCameraCuts = false, bool bPauseAtEnd = false);

private:

	UPROPERTY()
	ULevelSequencePlayer* CurrentCinematic;

	EPlayerMode PreviousPlayerMode;
	
	UFUNCTION()
	void OnCinematicEnd();
		
};
