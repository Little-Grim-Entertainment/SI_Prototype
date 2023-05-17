// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_DialogueManager.generated.h"

class UDialogueSession;
class UDialogueSessionNode;
class USI_CaseData;
class USI_PartData;
class USI_CharacterData;

UCLASS()
class SI_PROTOTYPE_API USI_DialogueManager : public USI_WorldSubsystem
{
	GENERATED_BODY()

public:

	// assumes that active characters using non-default dialogue have an associated SI_CharacterData
	// loaded into the CharacterManager's ActiveCharactersData
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue(USI_CharacterData* InCharacterData);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ExitDialogue(UDialogueSessionNode* NewSaveNode, int32 NewAngerLevel);


	// --- Functions to respond to button presses --- //
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnNextPressed();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnPreviousPressed();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnPressPressed();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnTextOptionSelected(FText RelatedText);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnItemOptionSelected(UObject* RelatedItem = nullptr);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnInterrogationPressed();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	UDialogueSession* GetCurrentDialogue();

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
	UDialogueSession* FindDialogue(USI_CaseData* Case, USI_PartData* Part);

private:

	void StartDefaultDialogue(USI_CharacterData* InCharacterData);

	USI_CharacterData* CurrentCharacterData;
	UDialogueSession* CurrentDialogue;

};
