// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_NPCController_Interactable.h"
#include "BehaviorTree/BehaviorTree.h"


void AAoS_NPCController_Interactable::StartDialogue()
{
	if (DialogueTree)
	{
		RunBehaviorTree(DialogueTree);
	}
}

void AAoS_NPCController_Interactable::EndDialogue()
{
	if (DialogueTree)
	{
		BrainComponent->StopLogic("Conversation Ended");
	}
}
