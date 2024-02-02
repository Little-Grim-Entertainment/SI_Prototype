// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_CharacterTypes.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_DialogueManager.generated.h"

class USI_InterrogationWidget;
class ASI_NPC;
class UDialogueSessionNode;
class USI_CaseData;
class USI_PartData;
class USI_CharacterData;
class ASI_DialogueCamera;

DECLARE_MULTICAST_DELEGATE(FOnInputDelayEnd);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInterrogationStateUpdated, const ESI_InterrogationState&);

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
	void OnPresentPressed();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ExitPressOrResponse();

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FSI_PrimaryDialogue GetCurrentPrimaryDialogue() const;
	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FSI_CorrectedDialogue GetCurrentCorrectedDialogue() const;
	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FSI_DefaultResponse GetCurrentDefaultResponse() const;

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	ASI_Character* GetActiveSpeaker();

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	bool ActiveInputDelay() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartInputDelayTimer(const float& InDelayTime);

	void SetupBindings();

	void SetActiveInputDelay(const bool& bInActiveInputDelay);

	void SetActiveInterrogationWidget(USI_InterrogationWidget* InInterrogationWidget);
	void InitializeInterrogationWidget();

	void SetInterrogationState(const ESI_InterrogationState& InInterrogationState);

	FOnInterrogationStateUpdated& OnInterrogationStateUpdated();

	FOnInputDelayEnd& OnInputDelayEnd();
	const ESI_InterrogationState& GetInterrogationState() const;

private:

	UPROPERTY()
	TSoftObjectPtr<USI_InterrogationWidget> ActiveInterrogationWidget;

	UPROPERTY()
	TSoftObjectPtr<ASI_Character> ActiveSpeaker;

	UPROPERTY()
	TSoftObjectPtr<ASI_NPC> ActiveNPC;
	
	UPROPERTY()
	TSoftObjectPtr<ASI_DialogueCamera> DialogueCamera;

	FOnInputDelayEnd OnInputDelayEndDelegate;
	FOnInterrogationStateUpdated OnInterrogationStateUpdatedDelegate;
	
	FSI_DialogueState* ActiveDialogueState;
	int32 CurrentDialogueIndex;

	// Only used during Interrogation
	int32 CurrentStatementIndex;
	int32 CurrentSecondaryDialogueIndex;

	ESI_InterrogationState InterrogationState;
	
	bool bCanPress;
	bool bInterrogationWidgetLoaded;
	bool bActiveInputDelay;

	void SetNickLocation();
	void UpdateActiveSpeaker();
	void SpawnDialogueCamera();

	UFUNCTION()
	void OnInterrogationIntroAnimationComplete();
	
	UFUNCTION()
	void OnInputDelayEnd_Internal();

	FLGConversationDialogue* GetCurrentDialogueByType(const int32 InCurrentIndex, const FGameplayTag& InTypeTag);
	
	void GetCurrentPressArray(const FSI_PrimaryDialogue* InCurrentPrimaryDialogue, TArray<FSI_PressDialogue*>& OutPressArray) const;
	void GetCurrentResponseArray(const FSI_PrimaryDialogue* InCurrentPrimaryDialogue, TArray<FSI_ResponseDialogue*>& OutResponseArray) const;
	void DisplayDefaultResponse();
	void UpdateInterrogationDialogue(const FLGConversationDialogue* InCurrentDialogue);
	UDataTable* GetCurrentDialogueTableByType(const int32 InCurrentIndex, const FGameplayTag& InTypeTag) const;
};