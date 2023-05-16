// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "SI_PlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	UPROPERTY()
	class ASI_Nick* PlayerCharacter;
	
public:

	UFUNCTION(BlueprintPure)
	FTransform GetFollowCamTransform();
	UFUNCTION(BlueprintPure)
	ASI_Nick* GetPlayerCharacter() {return PlayerCharacter;}

	UFUNCTION(BlueprintCallable)
	void SetPlayerCharacter(ASI_Nick* CharacterToSet);
};
