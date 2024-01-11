// Fill out your copyright notice in the Description page of Project Settings.


#include "LGDialogueTypes.h"
#include "LGBlueprintFunctionLibrary.h"

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

FText FLGConversationDialogue::GetSpeakerNameFromTag() const
{
	if(!SpeakerTag.IsValid()) {return FText();}
	
	FString SpeakerNameString = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(SpeakerTag);

	int32 SecondUpperIndex = 0;
	
	for(int32 CharIndex = 0; CharIndex < SpeakerNameString.Len(); CharIndex++)
	{
		const TCHAR CurrentChar = SpeakerNameString[CharIndex];
		if(TChar<TCHAR>::IsUpper(CurrentChar) && CharIndex > 0)
		{
			SecondUpperIndex = CharIndex;
			break;
		}
	}

	SpeakerNameString.InsertAt(SecondUpperIndex, ' ');

	return FText::FromString(SpeakerNameString);
}

FLGDialogueData::FLGDialogueData() : DialogueDataID(FGuid::NewGuid())
{
	
}

FLGCharacterDialogue::FLGCharacterDialogue()
{
}
