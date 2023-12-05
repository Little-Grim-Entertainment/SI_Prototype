// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LGProjectDialogueData.h"
#include "Data/LGDialogueDataAsset.h"

void ULGProjectDialogueData::UpdateAllDialogue()
{
	for (FLGCharacterDialogue& CurrentCharacterDialogue : CharacterDialogue)
	{
		for(ULGDialogueDataAsset* CurrentDialogueData : CurrentCharacterDialogue.DialogueData)
		{
			if(!IsValid(CurrentDialogueData)){continue;}
			CurrentDialogueData->UpdateDialogue_Internal();
		}
	}
}
