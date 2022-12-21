// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_DialogueManager.generated.h"

class UDialogueSession;
class UDialogueSessionNode;
class UAoS_Case;
class UAoS_Part;
class UAoS_CharacterData;

UCLASS()
class AOS_PROTOTYPE_API UAoS_DialogueManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

public:

	// assumes that active characters using non-default dialogue have an associated AoS_CharacterData
	// loaded into the CharacterManager's ActiveCharactersData
	void StartDialogue(FText CharacterName);

	void ExitDialogue(UDialogueSessionNode* NewSaveNode, int32 NewAngerLevel);


	// --- Functions to respond to button presses --- //

	void OnNextPressed();
	void OnPreviousPressed();
	void OnPressPressed();
	void OnTextOptionSelected(FText RelatedText);
	void OnItemOptionSelected(UObject* RelatedItem = nullptr);
	void OnInterrogationPressed();

	void SetupBindings();

	// --- Functions to determine which buttons should be available in the UI --- //

	bool HasNextOption();
	bool HasPreviousOption();
	bool HasPressOption();
	bool HasTextOptions();
	bool HasItemOptions();
	bool CanEnterInterrogation();

	// Finds the relevant dialogue based on Case and Part
	// To be called by CharacterManager when it is updating all of the character data
	UDialogueSession* FindDialogue(UAoS_Case* Case, UAoS_Part* Part);

private:

	void StartDefaultDialogue(FText CharacterName);

	UAoS_CharacterData* CurrentCharacterData;
	UDialogueSession* CurrentDialogue;

};
