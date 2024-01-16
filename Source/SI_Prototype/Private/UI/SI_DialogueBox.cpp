// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_DialogueBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Dialogue/SI_DialogueManager.h"

void USI_DialogueBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (!BTN_Next || !BTN_Previous){return;}

	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (!IsValid(DialogueManager)){return;}

	BTN_Next->SetVisibility(ESlateVisibility::Hidden);
	BTN_Previous->SetVisibility(ESlateVisibility::Hidden);

	if (DialogueManager->HasNextOption())
	{
		BTN_Next->SetVisibility(ESlateVisibility::Visible);
		BTN_Next->OnClicked.AddDynamic(this, &ThisClass::OnNextClicked);
		BTN_Next->OnHovered.AddDynamic(this, &ThisClass::OnNextHovered);
		BTN_Next->OnUnhovered.AddDynamic(this, &ThisClass::OnNextUnhovered);
	}
	if (DialogueManager->HasPreviousOption())
	{
		BTN_Previous->SetVisibility(ESlateVisibility::Visible);
		BTN_Previous->OnClicked.AddDynamic(this, &ThisClass::OnPreviousClicked);
		BTN_Previous->OnHovered.AddDynamic(this, &ThisClass::OnPreviousHovered);
		BTN_Previous->OnUnhovered.AddDynamic(this, &ThisClass::OnPreviousUnhovered);
	}

	//OnNextClickedDelegate.AddDynamic(DialogueManager, &USI_DialogueManager::OnNextPressed);
	//OnPreviousClickedDelegate.AddDynamic(DialogueManager, &USI_DialogueManager::OnPreviousPressed);
}

void USI_DialogueBox::NativeDestruct()
{
	Super::NativeDestruct();
	
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (!IsValid(DialogueManager)){return;}
	
	//OnNextClickedDelegate.RemoveDynamic(DialogueManager, &USI_DialogueManager::OnNextPressed);
	//OnPreviousClickedDelegate.RemoveDynamic(DialogueManager, &USI_DialogueManager::OnPreviousPressed);
}

FText USI_DialogueBox::GetCurrentSpeaker() const
{
	return CurrentPrimaryDialogue.GetSpeakerNameFromTag();
}

FText USI_DialogueBox::GetCurrentDialogue() const
{
	return CurrentPrimaryDialogue.Dialogue;
}

void USI_DialogueBox::RefreshDialogueBox()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (!IsValid(DialogueManager)){return;}

	CurrentPrimaryDialogue = DialogueManager->GetCurrentPrimaryDialogue();
	
	TXT_CharacterName->SetText(CurrentPrimaryDialogue.GetSpeakerNameFromTag());
	TXT_CharacterDialogue->SetText(CurrentPrimaryDialogue.Dialogue);
	
	ShowNextButton(DialogueManager);
	ShowPreviousButton(DialogueManager);
}

FOnNextClickedDelegate& USI_DialogueBox::GetOnNextClickedDelegate()
{
	return OnNextClickedDelegate;
}

FOnNextHoveredDelegate& USI_DialogueBox::GetOnNextHoveredDelegate()
{
	return OnNextHoveredDelegate;
}

FOnNextUnhoveredDelegate& USI_DialogueBox::GetOnNextUnhoveredDelegate()
{
	return OnNextUnhoveredDelegate;
}

FOnPreviousClickedDelegate& USI_DialogueBox::GetOnPreviousClickedDelegate()
{
	return OnPreviousClickedDelegate;
}

FOnPreviousHoveredDelegate& USI_DialogueBox::GetOnPreviousHoveredDelegate()
{
	return OnPreviousHoveredDelegate;
}

FOnPreviousUnhoveredDelegate& USI_DialogueBox::GetOnPreviousUnhoveredDelegate()
{
	return OnPreviousUnhoveredDelegate;
}

void USI_DialogueBox::OnNextClicked()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (!IsValid(DialogueManager)) {return;}

	DialogueManager->OnNextDialoguePressed();
	RefreshDialogueBox();
		
	OnNextClickedDelegate.Broadcast();
}

void USI_DialogueBox::OnNextHovered()
{
	OnNextHoveredDelegate.Broadcast();
}

void USI_DialogueBox::OnNextUnhovered()
{
	OnNextUnhoveredDelegate.Broadcast();
}

void USI_DialogueBox::OnPreviousClicked()
{
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (!IsValid(DialogueManager)) {return;}

	DialogueManager->OnPreviousStatementPressed();
	RefreshDialogueBox();
		
	OnPreviousClickedDelegate.Broadcast();
}

void USI_DialogueBox::OnPreviousHovered()
{
	OnPreviousHoveredDelegate.Broadcast();
}

void USI_DialogueBox::OnPreviousUnhovered()
{
	OnPreviousUnhoveredDelegate.Broadcast();
}

void USI_DialogueBox::ShowNextButton(USI_DialogueManager* InDialogueManager)
{
	if (InDialogueManager->HasNextOption())
	{
		BTN_Next->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BTN_Next->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USI_DialogueBox::ShowPreviousButton(USI_DialogueManager* InDialogueManager)
{
	if (InDialogueManager->HasPressOption())
	{
		BTN_Previous->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BTN_Previous->SetVisibility(ESlateVisibility::Hidden);
	}
}

