// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Characters/SI_CharacterTypes.h"
#include "SI_GameState.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_GameState : public AGameState
{
	GENERATED_BODY()
	
protected:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
