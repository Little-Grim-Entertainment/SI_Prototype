// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_DialogueBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Dialogue/AoS_DialogueManager.h"
#include "Dialogue/DialogueSession.h"

void UAoS_DialogueBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (!BTN_Next || !BTN_Previous){return;}

	UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
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

	//OnNextClickedDelegate.AddDynamic(DialogueManager, &UAoS_DialogueManager::OnNextPressed);
	//OnPreviousClickedDelegate.AddDynamic(DialogueManager, &UAoS_DialogueManager::OnPreviousPressed);
}

void UAoS_DialogueBox::NativeDestruct()
{
	Super::NativeDestruct();
	
	UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
	if (!IsValid(DialogueManager)){return;}
	
	//OnNextClickedDelegate.RemoveDynamic(DialogueManager, &UAoS_DialogueManager::OnNextPressed);
	//OnPreviousClickedDelegate.RemoveDynamic(DialogueManager, &UAoS_DialogueManager::OnPreviousPressed);
}

void UAoS_DialogueBox::SetCharacterName(FText InCharacterName)
{
	if (!IsValid(TXT_CharacterName)){return;}

	TXT_CharacterName->SetText(InCharacterName);
	CurrentSpeaker = InCharacterName;
}

void UAoS_DialogueBox::SetCharacterDialogue(FText InCharacterDialogue)
{
	if (!IsValid(TXT_CharacterDialogue)){return;}
	
	TXT_CharacterDialogue->SetText(InCharacterDialogue);
	CurrentDialogue = InCharacterDialogue;
}


void UAoS_DialogueBox::RefreshDialogueBox()
{
	UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
	if (!IsValid(DialogueManager)){return;}

	SetCharacterDialogue(DialogueManager->GetCurrentDialogue()->GetText());
	SetCharacterName(DialogueManager->GetCurrentDialogue()->GetName());
	ShowNextButton(DialogueManager);
	ShowPreviousButton(DialogueManager);
}

FText UAoS_DialogueBox::GetCurrentSpeaker() const
{
	return CurrentSpeaker;
}

FText UAoS_DialogueBox::GetCurrentDialogue() const
{
	return CurrentDialogue;
}

FOnNextClickedDelegate& UAoS_DialogueBox::GetOnNextClickedDelegate()
{
	return OnNextClickedDelegate;
}

FOnNextHoveredDelegate& UAoS_DialogueBox::GetOnNextHoveredDelegate()
{
	return OnNextHoveredDelegate;
}

FOnNextUnhoveredDelegate& UAoS_DialogueBox::GetOnNextUnhoveredDelegate()
{
	return OnNextUnhoveredDelegate;
}

FOnPreviousClickedDelegate& UAoS_DialogueBox::GetOnPreviousClickedDelegate()
{
	return OnPreviousClickedDelegate;
}

FOnPreviousHoveredDelegate& UAoS_DialogueBox::GetOnPreviousHoveredDelegate()
{
	return OnPreviousHoveredDelegate;
}

FOnPreviousUnhoveredDelegate& UAoS_DialogueBox::GetOnPreviousUnhoveredDelegate()
{
	return OnPreviousUnhoveredDelegate;
}

void UAoS_DialogueBox::OnNextClicked()
{
	UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
	if (!IsValid(DialogueManager)) {return;}

	DialogueManager->OnNextPressed();
	RefreshDialogueBox();
		
	OnNextClickedDelegate.Broadcast();
}

void UAoS_DialogueBox::OnNextHovered()
{
	OnNextHoveredDelegate.Broadcast();
}

void UAoS_DialogueBox::OnNextUnhovered()
{
	OnNextUnhoveredDelegate.Broadcast();
}

void UAoS_DialogueBox::OnPreviousClicked()
{
	UAoS_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<UAoS_DialogueManager>();
	if (!IsValid(DialogueManager)) {return;}

	DialogueManager->OnPreviousPressed();
	RefreshDialogueBox();
		
	OnPreviousClickedDelegate.Broadcast();
}

void UAoS_DialogueBox::OnPreviousHovered()
{
	OnPreviousHoveredDelegate.Broadcast();
}

void UAoS_DialogueBox::OnPreviousUnhovered()
{
	OnPreviousUnhoveredDelegate.Broadcast();
}

void UAoS_DialogueBox::ShowNextButton(UAoS_DialogueManager* InDialogueManager)
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

void UAoS_DialogueBox::ShowPreviousButton(UAoS_DialogueManager* InDialogueManager)
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

