// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AoS_GameMode.generated.h"

class UAoS_LevelManager;
class UAoS_HUD;

UCLASS()
class AOS_PROTOTYPE_API AAoS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AAoS_GameMode();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UAoS_LevelManager* LevelManager;
	
};
