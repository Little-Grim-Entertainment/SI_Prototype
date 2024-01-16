// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InterrogationWidget.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Dialogue/SI_DialogueManager.h"
#include "UI/SI_InterrogationDialogueBubble.h"

void USI_InterrogationWidget::SetNickDialogue(const FText& InDialogue)
{
	if(!IsValid(NickDialogueBubble)) {return;}
	
	NickDialogueBubble->SetCharacterDialogue(InDialogue);
	if(NickDialogueBubble->GetVisibility() == ESlateVisibility::Hidden)
	{
		NPCDialogueBubble->SetVisibility(ESlateVisibility::Hidden);
		NickDialogueBubble->SetVisibility(ESlateVisibility::Visible);
		VisibleDialogueBubble = NickDialogueBubble;
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
		VisibleDialogueBubble = NPCDialogueBubble;
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

	if(!IsValid(DialogueBubbles) || !IsValid(NickDialogueBubble) || !IsValid(NPCDialogueBubble)) {return;}

	DialogueBubbles->SetVisibility(ESlateVisibility::Hidden);
	
	NickDialogueBubble->SetInterrogationWidget(this);
	NickDialogueBubble->SetVisibility(ESlateVisibility::Hidden);
	NPCDialogueBubble->SetInterrogationWidget(this);
	NPCDialogueBubble->SetVisibility(ESlateVisibility::Hidden);

	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(!IsValid(DialogueManager)) {return;}

	DialogueManager->SetActiveInterrogationWidget(this);
	OnIntroAnimationCompleteDelegate.AddDynamic(this, &ThisClass::OnIntroAnimationComplete_Internal);
}

void USI_InterrogationWidget::OnIntroAnimationComplete_Internal()
{
	if(!IsValid(DialogueBubbles)) {return;}

	DialogueBubbles->SetVisibility(ESlateVisibility::Visible);
	if(!IsValid(VisibleDialogueBubble)) {return;}

	VisibleDialogueBubble->SetVisibility(ESlateVisibility::Visible);
	VisibleDialogueBubble->PlayBubbleAnimation();
}
