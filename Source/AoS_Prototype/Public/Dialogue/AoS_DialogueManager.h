// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_DialogueManager.generated.h"

UCLASS()
class AOS_PROTOTYPE_API UAoS_DialogueManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

public:

	// assumes that active characters using non-default dialogue have an associated AoS_CharacterData
	// loaded into the CharacterManager's ActiveCharactersData
	void StartDialogue(FText CharacterName);

	void OnNextPressed();
	void OnPreviousPressed();
	void OnBackButtonPressed();

	void OnInterrogationPressed();

private:

	void StartDefaultDialogue(FText CharacterName);

};
