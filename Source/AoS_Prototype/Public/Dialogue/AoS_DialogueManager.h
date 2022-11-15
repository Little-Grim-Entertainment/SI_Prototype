// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_DialogueManager.generated.h"

class UDlgDialogue;
class UDlgContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginDialogue, UDlgContext*, DialogueContext);

UCLASS()
class AOS_PROTOTYPE_API UAoS_DialogueManager : public UAoS_WorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION()
	FOnBeginDialogue& GetOnBeginDialogue();

	// assumes that active characters using non-default dialogue have an associated AoS_CharacterData
	// loaded into the CharacterManager's ActiveCharactersData
	void StartDialogue(FText CharacterName);

	void OnNextPressed();
	void OnPreviousPressed();
	void OnBackButtonPressed();

	void OnInterrogationPressed();

private:

	UPROPERTY()
	FOnBeginDialogue OnBeginDialogueDelegate;

	UPROPERTY()
	UDlgContext* ActiveDialogueContext;
	
	void StartDefaultDialogue(FText CharacterName);

};
