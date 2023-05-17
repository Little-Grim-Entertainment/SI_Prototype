// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_InteractionWidget.h"

#include "UI/SI_UIManager.h"

void USI_InteractionWidget::ShowWidget_Implementation()
{
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if (IsValid(UIManager))
	{
		UIManager->AddActiveInteractionWidget(this);
	}
}

void USI_InteractionWidget::HideWidget_Implementation()
{

}

void USI_InteractionWidget::RefreshWidget_Implementation()
{
}
