// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_DialogueBox.h"
#include "DlgContext.h"
#include "Components/TextBlock.h"

void UAoS_DialogueBox::SetCharacterName(FText InCharacterName)
{
	if (!IsValid(TXT_CharacterName)){return;}

	TXT_CharacterName->SetText(InCharacterName);
	CurrentSpeaker = InCharacterName;
}

void UAoS_DialogueBox::SetCharacterDialogue(FText InCharacterDialogue)
{
	if (!IsValid(TXT_CharacterDialogue)){return;}
	
	TXT_CharacterName->SetText(InCharacterDialogue);
	CurrentDialogue = InCharacterDialogue;
}

void UAoS_DialogueBox::UpdateDialogueBox(UDlgContext* DlgContext)
{
	if (!IsValid(DlgContext)){return;}
	
	if (GetCurrentSpeaker().ToString() != DlgContext->GetActiveNodeParticipantDisplayName().ToString())
	{
		SetCharacterName(DlgContext->GetActiveNodeParticipantDisplayName());
	}
	if (GetCurrentDialogue().ToString() != DlgContext->GetActiveNodeText().ToString())
	{
		SetCharacterDialogue(DlgContext->GetActiveNodeText());
	}
}

FText UAoS_DialogueBox::GetCurrentSpeaker() const
{
	return CurrentSpeaker;
}

FText UAoS_DialogueBox::GetCurrentDialogue() const
{
	return CurrentDialogue;
}
