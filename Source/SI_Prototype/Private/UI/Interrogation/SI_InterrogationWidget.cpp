// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Interrogation/SI_InterrogationWidget.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Dialogue/SI_DialogueManager.h"
#include "UI/Interrogation/SI_InterrogationDialogueBubble.h"

void USI_InterrogationWidget::SetNickDialogue(const FText& InDialogue)
{
	if(!IsValid(NickDialogueBubble)) {return;}
	
	NickDialogueBubble->SetCharacterDialogue(InDialogue);
	if(NickDialogueBubble->GetVisibility() == ESlateVisibility::Hidden)
	{
		NPCDialogueBubble->SetVisibility(ESlateVisibility::Hidden);
		NickDialogueBubble->SetVisibility(ESlateVisibility::Visible);
		
		if(VisibleDialogueBubble == NickDialogueBubble){return;}
		SetVisibleDialogueBubble(NickDialogueBubble);
	}
}

void USI_InterrogationWidget::SetNPCDialogue(const FText& InDialogue)
{
	if(!IsValid(NPCDialogueBubble)) {return;}
	
	NPCDialogueBubble->SetCharacterDialogue(InDialogue);
	if(NPCDialogueBubble->GetVisibility() == ESlateVisibility::Hidden)
	{
		NickDialogueBubble->SetVisibility(ESlateVisibility::Hidden);
		NPCDialogueBubble->SetVisibility(ESlateVisibility::Visible);

		if(VisibleDialogueBubble == NPCDialogueBubble) {return;}
		SetVisibleDialogueBubble(NPCDialogueBubble);
	}
}

void USI_InterrogationWidget::SetNPCImage(UTexture2D* InNPCImage)
{
	if(!IsValid(InNPCImage) || !IsValid(IMG_NPCImage)){return;}

	IMG_NPCImage->SetBrushFromTexture(InNPCImage);
}

FOnIntroAnimationComplete& USI_InterrogationWidget::OnIntroAnimationComplete()
{
	return OnIntroAnimationCompleteDelegate;
}

void USI_InterrogationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!IsValid(NickDialogueBubble) || !IsValid(NPCDialogueBubble)) {return;}
		
	NickDialogueBubble->SetInterrogationWidget(this);
	NickDialogueBubble->SetVisibility(ESlateVisibility::Hidden);
	NPCDialogueBubble->SetInterrogationWidget(this);
	NPCDialogueBubble->SetVisibility(ESlateVisibility::Hidden);

	DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(!IsValid(DialogueManager.Get())) {return;}

	DialogueManager->SetActiveInterrogationWidget(this);
	DialogueManager->SetActiveInputDelay(true);
	OnIntroAnimationCompleteDelegate.AddDynamic(this, &ThisClass::OnIntroAnimationComplete_Internal);
}

void USI_InterrogationWidget::OnIntroAnimationComplete_Internal()
{
	if(!IsValid(VisibleDialogueBubble)) {return;}
	
	VisibleDialogueBubble->SetVisibility(ESlateVisibility::Visible);
	VisibleDialogueBubble->PlayBubbleAnimation();

	if(!IsValid(DialogueManager.Get())) {return;}
	DialogueManager->SetActiveInputDelay(false);
}

void USI_InterrogationWidget::SetVisibleDialogueBubble(USI_InterrogationDialogueBubble* InVisibleDialogueBubble)
{
	if(!IsValid(InVisibleDialogueBubble)) {return;}

	VisibleDialogueBubble = InVisibleDialogueBubble;
}
