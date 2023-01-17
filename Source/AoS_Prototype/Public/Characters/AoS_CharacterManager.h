// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_CharacterManager.generated.h"

class UAoS_Part;
class UAoS_CharacterData;

UCLASS()
class AOS_PROTOTYPE_API UAoS_CharacterManager : public UAoS_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// returns nullptr if character's name is not found in the list
	UAoS_CharacterData* GetActiveCharacterData(FText CharacterName);
	bool GetIsActiveCharacter(UAoS_CharacterData* InCharacterData);

protected:

	virtual void OnGameInstanceInit() override;

private: 

	// Assumption: this is always kept up to date by calling functions in this class to update it
	// We will create a binding with an event in the case manager
	TArray<UAoS_CharacterData*> ActiveCharactersData;
	
	// Called when a new part of a case is activated in order to update ActiveCharactersData
	UFUNCTION()
	void OnPartActivated(UAoS_Part* ActivatedPart);
	
	// Called when a part is completed to update ActiveCharactersData
	UFUNCTION()
	void OnPartCompleted(UAoS_Part* CompletedPart);
};
