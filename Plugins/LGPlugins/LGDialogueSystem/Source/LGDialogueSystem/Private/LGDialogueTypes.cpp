// Fill out your copyright notice in the Description page of Project Settings.


#include "LGDialogueTypes.h"

DEFINE_LOG_CATEGORY(LogLGDialogue);

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
}
