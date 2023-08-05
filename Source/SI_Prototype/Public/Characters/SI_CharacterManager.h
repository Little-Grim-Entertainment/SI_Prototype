// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_CharacterManager.generated.h"

class USI_PartData;
class USI_CharacterData;

DECLARE_LOG_CATEGORY_EXTERN(LogSI_CharacterManager, Log, All);

UCLASS()
class SI_PROTOTYPE_API USI_CharacterManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// returns nullptr if character's name is not found in the list
	USI_CharacterData* GetActiveCharacterData(FText CharacterName);
	bool GetIsActiveCharacter(USI_CharacterData* InCharacterData);

protected:

	virtual void OnGameInstanceInit() override;

private: 

	// Assumption: this is always kept up to date by calling functions in this class to update it
	// We will create a binding with an event in the case manager
	TArray<USI_CharacterData*> ActiveCharactersData;
	
	// Called when a new part of a case is activated in order to update ActiveCharactersData
	UFUNCTION()
	void OnPartActivated(USI_PartData* ActivatedPart);
	
	// Called when a part is completed to update ActiveCharactersData
	UFUNCTION()
	void OnPartCompleted(USI_PartData* CompletedPart);
};
