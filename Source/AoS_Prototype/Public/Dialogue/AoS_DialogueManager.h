// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AoS_DialogueManager.generated.h"

class UAoS_GameInstance;
class UDlgDialogue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginDialogue, UDlgDialogue*, DlgDialogue);

UCLASS()
class AOS_PROTOTYPE_API UAoS_DialogueManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION()
	FOnBeginDialogue& GetOnBeginDialogue();

protected:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:

	UPROPERTY()
	UAoS_GameInstance* GameInstance;
	UPROPERTY()
	FOnBeginDialogue OnBeginDialogueDelegate;
};
