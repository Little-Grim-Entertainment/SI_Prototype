// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_OptionWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USI_OptionWidget::ShowWidget_Implementation()
{
	Super::ShowWidget_Implementation();
}

void USI_OptionWidget::HideWidget_Implementation()
{
	Super::HideWidget_Implementation();
}

void USI_OptionWidget::RefreshWidget_Implementation()
{
	Super::RefreshWidget_Implementation();
	
}

void USI_OptionWidget::SetOptionImage(UTexture2D* InImage)
{
	IMG_Icon->SetBrushFromTexture(InImage);
}

void USI_OptionWidget::SetOptionPrompt(FText InPrompt)
{
	TXT_Prompt->Text = InPrompt;
}

void USI_OptionWidget::SetOptionBinding(FText InBinding)
{
	TXT_Binding->Text = InBinding;
}
