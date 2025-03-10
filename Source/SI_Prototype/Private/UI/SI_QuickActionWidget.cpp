// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_QuickActionWidget.h"

#include "EnhancedInputSubsystems.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Abilities/SI_AbilityGameplayTagLibrary.h"
#include "SI_Types.h"
#include "Components/TextBlock.h"
#include "UI/SI_OptionWidget.h"

using namespace SI_NativeGameplayTagLibrary;
using namespace SI_AbilityGameplayTagLibrary;

void USI_QuickActionWidget::RefreshQuickActionWidget(const FGameplayTag& InUITag)
{
	if (InUITag == SITag_UI_HUD_QuickAction_GadgetsOne)
	{
		UpdateQuickActionUp(SITag_Ability_Nick_Interact_Drop);
		UpdateQuickActionDown(SITag_Ability_Nick_Interact_Pickup);
		UpdateQuickActionLeft(SITag_Ability_Nick_Gadget_UsePrimary);
		UpdateQuickActionRight(SITag_Ability_Nick_Gadget_UseSecondary);
	}
	else if (InUITag == SITag_UI_HUD_QuickAction_Movable)
	{
		UpdateQuickActionUp(SITag_Ability_Adaptable_AI_Interact_Drop);
		UpdateQuickActionDown(SITag_Ability_Adaptable_AI_Interact_Pickup);
		UpdateQuickActionLeft(SITag_Ability_Adaptable_AI_Interact_Pull);
		UpdateQuickActionRight(SITag_Ability_Adaptable_AI_Interact_Push);
	}
	else if (InUITag == SITag_UI_HUD_QuickAction_Gizbo)
	{
		UpdateQuickActionUp(SITag_Ability_AI_Follow);
		UpdateQuickActionDown(SITag_Ability_AI_Wait);
		UpdateQuickActionLeft(SITag_Ability_AI_Gadget_UsePrimary);
		UpdateQuickActionRight(SITag_Ability_AI_Gadget_UseSecondary);
	}
}

void USI_QuickActionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EnhancedInputLPS = GetOwningPlayer()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	UpdateQuickActionUp(QuickActionUpTag);
	UpdateQuickActionDown(QuickActionDownTag);
	UpdateQuickActionLeft(QuickActionLeftTag);
	UpdateQuickActionRight(QuickActionRightTag);	
}

void USI_QuickActionWidget::UpdateQuickActionUp(FGameplayTag InOptionTag)
{
	UpdateActionByTag(QuickActionOption_Up, InOptionTag, QuickActionUpInputAction);
}

void USI_QuickActionWidget::UpdateQuickActionDown(FGameplayTag InOptionTag)
{
	UpdateActionByTag(QuickActionOption_Down, InOptionTag, QuickActionDownInputAction);
}

void USI_QuickActionWidget::UpdateQuickActionLeft(FGameplayTag InOptionTag)
{
	UpdateActionByTag(QuickActionOption_Left, InOptionTag, QuickActionLeftInputAction);
}

void USI_QuickActionWidget::UpdateQuickActionRight(FGameplayTag InOptionTag)
{
	UpdateActionByTag(QuickActionOption_Right, InOptionTag, QuickActionRightInputAction);
}

FGameplayTag USI_QuickActionWidget::GetQuickActionAbilityTag(const FGameplayTag InQuickActionTag) const
{
	FGameplayTag QuickActionTag;
	if(InQuickActionTag == SITag_Input_Action_MultiOption_Down)
	{
		if(IsValid(QuickActionOption_Down))
		{
			QuickActionTag = QuickActionOption_Down->GetOptionTag();
		}
	}
	else if(InQuickActionTag == SITag_Input_Action_MultiOption_Left)
	{
		if(IsValid(QuickActionOption_Left))
		{
			QuickActionTag = QuickActionOption_Left->GetOptionTag();
		}
	}
	else if(InQuickActionTag == SITag_Input_Action_MultiOption_Right)
	{
		if(IsValid(QuickActionOption_Right))
		{
			QuickActionTag = QuickActionOption_Right->GetOptionTag();
		}
	}
	else if(InQuickActionTag == SITag_Input_Action_MultiOption_Up)
	{
		if(IsValid(QuickActionOption_Up))	
		{
			QuickActionTag = QuickActionOption_Up->GetOptionTag();
		}
	}
	
	return QuickActionTag;
}

void USI_QuickActionWidget::UpdateActionByTag(USI_OptionWidget* InOptionWidget, FGameplayTag InOptionTag, UInputAction* InInputAction)
{
	TArray<FKey> MappedKey = EnhancedInputLPS->QueryKeysMappedToAction(InInputAction);
	
	FSI_QuckActionOptions* Row;
	FName TagName = InOptionTag.GetTagName();
	Row = OptionListDataTable->FindRow<FSI_QuckActionOptions>(TagName, TEXT(""));

	if(Row != NULL)
	{
		InOptionWidget->OptionTag = Row->QuickActionTag;
		InOptionWidget->SetVisibility(ESlateVisibility::Visible);
		InOptionWidget->SetOptionImage(Row->QuickActionImage);
		InOptionWidget->TXT_Prompt->SetText(Row->QuickActionPrompt);
	}
	else
	{
		InOptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		InOptionWidget->TXT_Prompt->SetText(FText::FromString(""));
		InOptionWidget->TXT_Binding->SetText(FText::FromString(""));
	}

	if(!MappedKey.IsEmpty())
	{
		InOptionWidget->TXT_Binding->SetText(MappedKey[0].GetDisplayName());
	}
	else
	{			
		InOptionWidget->TXT_Binding->SetText(FText::FromString(""));
	}
}