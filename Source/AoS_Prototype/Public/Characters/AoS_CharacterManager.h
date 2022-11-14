// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AoS_CharacterManager.generated.h"

class UAoS_CharacterData;

UCLASS()
class AOS_PROTOTYPE_API UAoS_CharacterManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// returns nullptr if character's name is not found in the list
	UAoS_CharacterData* GetActiveCharacterData(FText CharacterName);

private: 

	// Assumption: this is always kept up to date by calling functions in this class to update it
	// We will create a binding with an event in the case manager
	TArray<UAoS_CharacterData*> ActiveCharactersData;

	// Called when a new part of a case is activated in order to update ActiveCharactersData
	void OnNewPartActive();
	// Called when a part is completed to update ActiveCharactersData
	void OnPartCompleted();
	
};
