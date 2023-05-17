// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/SI_NPCController.h"
#include "SI_NPCController_Interactable.generated.h"

UCLASS()
class SI_PROTOTYPE_API ASI_NPCController_Interactable : public ASI_NPCController
{
	GENERATED_BODY()

	UPROPERTY()
	class UBehaviorTree* DialogueTree;

public:

	UFUNCTION()
	void StartDialogue();
	UFUNCTION()
	void EndDialogue();
	
	UFUNCTION()
	void SetDialogueTree(UBehaviorTree* DialogueTreeToSet) {DialogueTree = DialogueTreeToSet;}
	
	UFUNCTION(BlueprintPure)
	UBehaviorTree* GetDialogueTree() {return DialogueTree;}
	
};
