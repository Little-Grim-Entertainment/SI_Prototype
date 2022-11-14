// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AoS_DialogueManager.generated.h"

class UAoS_GameInstance;
class UDlgDialogue;
class UDlgContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginDialogue, UDlgDialogue*, DlgDialogue);

UCLASS()
class AOS_PROTOTYPE_API UAoS_DialogueManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION()
	FOnBeginDialogue& GetOnBeginDialogue();

	// assumes that active characters using non-default dialogue have an associated AoS_CharacterData
	// loaded into the CharacterManager's ActiveCharactersData
	void StartDialogue(FText CharacterName);

protected:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	FOnBeginDialogue OnBeginDialogueDelegate;

	UPROPERTY()
	UDlgContext* ActiveDialogueContext;

	void StartDefaultDialogue(FText CharacterName);

};
