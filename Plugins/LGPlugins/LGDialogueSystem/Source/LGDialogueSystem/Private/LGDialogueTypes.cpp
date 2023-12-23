// Fill out your copyright notice in the Description page of Project Settings.


#include "LGDialogueTypes.h"
#include "Data/LGDialogueDataAsset.h"

DEFINE_LOG_CATEGORY(LogLGDialogue);


FLGDialogueArray::FLGDialogueArray() : DialogueArrayID(FGuid::NewGuid())
{
}

void FLGDialogueArray::SetDataTable(UDataTable* InDataTable)
{
}

UScriptStruct* FLGDialogueArray::GetStructContainer()
{
	return nullptr;
}

void FLGDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
}

bool FLGDialogueArray::operator==(const FLGDialogueArray& OtherDialogue) const
{
	return OtherDialogue.DialogueStructTypeTag == DialogueStructTypeTag;
}

bool FLGDialogueArray::operator!=(const FLGDialogueArray& OtherDialogue) const
{
	return OtherDialogue.DialogueStructTypeTag != DialogueStructTypeTag;
}

FLGDialogue::FLGDialogue() : DialogueID(FGuid::NewGuid())
{
}

bool FLGDialogue::operator==(const FLGDialogue& OtherDialogue) const
{
	return OtherDialogue.DialogueID == DialogueID;
}

bool FLGDialogue::operator!=(const FLGDialogue& OtherDialogue) const
{
	return OtherDialogue.DialogueID != DialogueID;
}

FLGCharacterDialogue::FLGCharacterDialogue()
{
	if(IsValid(CharacterDialogueData))
	{
		CharacterTag = CharacterDialogueData->GetCharacterTag();
	}
}
