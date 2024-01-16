// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_CharacterTypes.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_DialogueManager.generated.h"

class USI_InterrogationWidget;
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
	void OnNextDialoguePressed();

	// Interrogation
	UFUNCTION(BlueprintCallable, Category = "Dialogue | Interrogation")
	void OnRequestInterrogation();
	UFUNCTION(BlueprintCallable, Category = "Dialogue | Interrogation")
	void OnRequestQuitInterrogation();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnNextStatementPressed();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnPreviousStatementPressed();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnPressPressed();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ExitPressOrResponse();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnTextOptionSelected(FText RelatedText);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnItemOptionSelected(UObject* RelatedItem = nullptr);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnInterrogationPressed();

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FSI_PrimaryDialogue GetCurrentPrimaryDialogue() const;
	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FSI_CorrectedDialogue GetCurrentCorrectedDialogue() const;
	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FSI_DefaultResponse GetCurrentDefaultResponse() const;

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	ASI_Character* GetActiveSpeaker();

	void SetupBindings();

	void SetActiveInterrogationWidget(USI_InterrogationWidget* InInterrogationWidget);
	void InitializeInterrogationWidget();


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
	TSoftObjectPtr<USI_InterrogationWidget> ActiveInterrogationWidget;

	UPROPERTY()
	TSoftObjectPtr<ASI_Character> ActiveSpeaker;

	UPROPERTY()
	TSoftObjectPtr<ASI_NPC> ActiveNPC;
	
	UPROPERTY()
	TSoftObjectPtr<ASI_DialogueCamera> DialogueCamera;
	
	FSI_DialogueState* ActiveDialogueState;
	int32 CurrentDialogueIndex;

	// Only used during Interrogation
	int32 CurrentStatementIndex;
	int32 CurrentSecondaryDialogueIndex;
	
	bool bCanPress;
	bool bIsPressing;
	bool bIsResponding;
	bool bInterrogationWidgetLoaded;

	void SetNickLocation();
	void UpdateActiveSpeaker();
	void SpawnDialogueCamera();

	UFUNCTION()
	void OnInterrogationIntroAnimationComplete();

	FLGConversationDialogue* GetCurrentDialogueByType(const int32 InCurrentIndex, const FGameplayTag& InTypeTag);
	
	void GetCurrentPressArray(const FSI_PrimaryDialogue* InCurrentPrimaryDialogue, TArray<FSI_PressDialogue*>& OutPressArray) const;
	void GetCurrentResponseArray(const FSI_PrimaryDialogue* InCurrentPrimaryDialogue, TArray<FSI_ResponseDialogue*>& OutResponseArray) const;
	void DisplayDefaultResponse();
	void UpdateInterrogationDialogue(const FLGConversationDialogue* InCurrentDialogue);
	UDataTable* GetCurrentDialogueTableByType(const int32 InCurrentIndex, const FGameplayTag& InTypeTag) const;
};
