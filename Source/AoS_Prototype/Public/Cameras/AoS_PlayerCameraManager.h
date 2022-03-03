// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "AoS_PlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API AAoS_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	UPROPERTY()
	class AAoS_Nick* PlayerCharacter;
	
public:

	UFUNCTION(BlueprintPure)
	FTransform GetFollowCamTransform();
	UFUNCTION(BlueprintPure)
	AAoS_Nick* GetPlayerCharacter() {return PlayerCharacter;}

	UFUNCTION(BlueprintCallable)
	void SetPlayerCharacter(AAoS_Nick* CharacterToSet);
};
