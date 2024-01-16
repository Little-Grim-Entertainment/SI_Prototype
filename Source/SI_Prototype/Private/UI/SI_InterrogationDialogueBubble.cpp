// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InterrogationDialogueBubble.h"

#include "Components/Border.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "UI/SI_InterrogationWidget.h"


USI_InterrogationWidget* USI_InterrogationDialogueBubble::GetInterrogationWidget()
{
	return InterrogationWidget;
}

void USI_InterrogationDialogueBubble::SetCharacterDialogue(const FText& InDialogue)
{
	if(!IsValid(TXT_CharacterDialogue)) {return;}
	
	TXT_CharacterDialogue->SetText(InDialogue);
}

void USI_InterrogationDialogueBubble::SetInterrogationWidget(USI_InterrogationWidget* InInterrogationWidget)
{
	InterrogationWidget = InInterrogationWidget;
}

void USI_InterrogationDialogueBubble::PlayBubbleAnimation_Implementation()
{
}
