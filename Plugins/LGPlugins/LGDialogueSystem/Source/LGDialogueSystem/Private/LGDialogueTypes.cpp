// Fill out your copyright notice in the Description page of Project Settings.


#include "LGDialogueTypes.h"

DEFINE_LOG_CATEGORY(LogLGDialogue);

FArrayProperty* FLGDialogueArray::GetArrayProperty()
{
	return nullptr;
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
