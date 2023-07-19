// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_QuickActionWidget.h"

#include "EnhancedInputSubsystems.h"
#include "SI_Types.h"
#include "Components/TextBlock.h"
#include "UI/SI_OptionWidget.h"

void USI_QuickActionWidget::RefreshQuickActionWidget()
{
	// GET current IMC?
	
}

void USI_QuickActionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EILPS = GetOwningPlayer()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
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

void USI_QuickActionWidget::UpdateActionByTag(USI_OptionWidget* InOptionWidget, FGameplayTag InOptionTag, UInputAction* InInputAction)
{
	TArray<FKey> MappedKey = EILPS->QueryKeysMappedToAction(InInputAction);
	
	FSI_QuckActionOptions* Row;
	FName TagName = InOptionTag.GetTagName();
	Row = OptionListDataTable->FindRow<FSI_QuckActionOptions>(TagName, TEXT(""));

	if(Row != NULL)
	{
		InOptionWidget->SetVisibility(ESlateVisibility::Visible);
		InOptionWidget->SetOptionImage(Row->QuickActionImage);
		InOptionWidget->TXT_Prompt->SetText(Row->QuickActionPrompt);
		InOptionWidget->TXT_Binding->SetText(MappedKey[0].GetDisplayName());
	}
	
	InOptionWidget->SetVisibility(ESlateVisibility::Collapsed);
	InOptionWidget->TXT_Prompt->SetText(FText::FromString(""));
	InOptionWidget->TXT_Binding->SetText(FText::FromString(""));

}