// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_CharacterTypes.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_DialogueManager.generated.h"

class ASI_NPC;
class UDialogueSessionNode;
class USI_CaseData;
class USI_PartData;
class USI_CharacterData;
class ASI_DialogueCamera;

UCLASS()
class SI_PROTOTYPE_API USI_DialogueManager : public USI_WorldSubsystem
{
	GENERATED_BODY()

public:

	// assumes that active characters using non-default dialogue have an associated SI_CharacterData
	// loaded into the CharacterManager's ActiveCharactersData
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue(ASI_NPC* InNPC);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ExitDialogue();


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

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FSI_PrimaryDialogue GetCurrentPrimaryDialogue() const;

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	ASI_Character* GetActiveSpeaker();

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

private:

	UPROPERTY()
	TSoftObjectPtr<ASI_Character> ActiveSpeaker;

	UPROPERTY()
	TSoftObjectPtr<ASI_NPC> ActiveNPC;
	
	UPROPERTY()
	TSoftObjectPtr<ASI_DialogueCamera> DialogueCamera;
	
	FSI_DialogueState* ActiveDialogueState;
	int32 CurrentDialogueIndex;

	void SetNickLocation();
	void UpdateActiveSpeaker();
	void SpawnDialogueCamera();
};
