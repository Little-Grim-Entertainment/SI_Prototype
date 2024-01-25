// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Interrogation/SI_InterrogationDialogueBubble.h"

#include "Components/Border.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Dialogue/SI_DialogueManager.h"
#include "UI/SI_InputOption.h"
#include "UI/Interrogation/SI_InterrogationWidget.h"

USI_InterrogationWidget* USI_InterrogationDialogueBubble::GetInterrogationWidget()
{
	return InterrogationWidget;
}

USI_InputOption* USI_InterrogationDialogueBubble::GetPressInputOptionWidget()
{
	return PressInputOption;
}

USI_InputOption* USI_InterrogationDialogueBubble::GetPresentInputOptionWidget()
{
	return PresentInputOption;
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

void USI_InterrogationDialogueBubble::ShowPressInputOption(const bool& bInShouldShow)
{
	if(!IsValid(PressInputOption)) {return;}

	if(bInShouldShow && PressInputOption->GetVisibility() != ESlateVisibility::SelfHitTestInvisible)
	{
		PressInputOption->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else if (!bInShouldShow && PressInputOption->GetVisibility() != ESlateVisibility::Hidden)
	{
		PressInputOption->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USI_InterrogationDialogueBubble::ShowPresentInputOption(const bool& bInShouldShow)
{
	if(!IsValid(PresentInputOption)) {return;}
	
	if(bInShouldShow && PresentInputOption->GetVisibility() != ESlateVisibility::SelfHitTestInvisible)
	{
		PresentInputOption->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else if (!bInShouldShow && PresentInputOption->GetVisibility() != ESlateVisibility::Hidden)
	{
		PresentInputOption->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USI_InterrogationDialogueBubble::HideAllInputOptions()
{
	if(!IsValid(PresentInputOption) || !IsValid(PressInputOption)) {return;}

	ShowPresentInputOption(false);
	ShowPressInputOption(false);
}

void USI_InterrogationDialogueBubble::OnInterrogationStateUpdated(const ESI_InterrogationState& InInterrogationState)
{
	if(!bShowInputOptions) {return;}
	switch (InInterrogationState)
	{
		case IS_Conversation:
		{
			ShowPresentInputOption(false);
			ShowPressInputOption(true);	
			break;
		}
		case IS_Pressing:
		{
			ShowPresentInputOption(true);
			ShowPressInputOption(false);	
			break;
		}
		default:
		{
			HideAllInputOptions();
			break;
		}
	}
}

const FSI_InputOptionSettings& USI_InterrogationDialogueBubble::RequestInputOptionSettings(const USI_InputOption* InInputOptionWidget) const
{
	if(InInputOptionWidget == PressInputOption)
	{
		return PressInputOptionSettings;
	}
	if (InInputOptionWidget == PresentInputOption)
	{
		return PresentInputOptionSettings;
	}

	static FSI_InputOptionSettings DefaultInputOptionSettings;
	return DefaultInputOptionSettings;
}

void USI_InterrogationDialogueBubble::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(!bShowInputOptions)
	{
		HideAllInputOptions();
		return;
	}	

	if(!IsValid(PressInputOption) || !IsValid(PresentInputOption)) {return;}

	UOverlaySlot* PressOverlaySlot = Cast<UOverlaySlot>(PressInputOption->Slot);
	UOverlaySlot* PresentOverlaySlot = Cast<UOverlaySlot>(PresentInputOption->Slot);

	if(!IsValid(PressOverlaySlot) || !IsValid(PresentOverlaySlot)) {return;}

	PressOverlaySlot->SetPadding(PressInputOptionSettings.InputOptionPadding);
	PresentOverlaySlot->SetPadding(PresentInputOptionSettings.InputOptionPadding);	
}

void USI_InterrogationDialogueBubble::NativeConstruct()
{
	Super::NativeConstruct();

	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if(!IsValid(DialogueManager)) {return;}

	DialogueManager->OnInterrogationStateUpdated().AddUObject(this, &ThisClass::OnInterrogationStateUpdated);
}

void USI_InterrogationDialogueBubble::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName MemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr) ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;

	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(USI_InterrogationDialogueBubble, PressInputOptionSettings))
	{
		if(!IsValid(PressInputOption)) {return;}

		PressInputOption->SetInputOptionSettings(PressInputOptionSettings);
	}
	else if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(USI_InterrogationDialogueBubble, PresentInputOptionSettings))
	{
		if(!IsValid(PresentInputOption)) {return;}

		PresentInputOption->SetInputOptionSettings(PresentInputOptionSettings);
	}
}

void USI_InterrogationDialogueBubble::PlayBubbleAnimation_Implementation()
{
}
