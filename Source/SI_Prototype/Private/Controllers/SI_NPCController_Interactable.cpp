// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SI_NPCController_Interactable.h"
#include "BehaviorTree/BehaviorTree.h"


void ASI_NPCController_Interactable::StartDialogue()
{
	if (DialogueTree)
	{
		RunBehaviorTree(DialogueTree);
	}
}

void ASI_NPCController_Interactable::EndDialogue()
{
	if (DialogueTree)
	{
		BrainComponent->StopLogic("Conversation Ended");
	}
}
