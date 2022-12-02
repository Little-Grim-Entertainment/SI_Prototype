// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_InteractionWidget.h"

#include "UI/AoS_UIManager.h"

void UAoS_InteractionWidget::ShowWidget_Implementation()
{
	UAoS_UIManager* UIManager = GetGameInstance()->GetSubsystem<UAoS_UIManager>();
	if (IsValid(UIManager))
	{
		UIManager->AddActiveInteractionWidget(this);
	}
}

void UAoS_InteractionWidget::HideWidget_Implementation()
{
	UAoS_UIManager* UIManager = GetGameInstance()->GetSubsystem<UAoS_UIManager>();
	if (IsValid(UIManager))
	{
		UIManager->RemoveActiveInteractionWidget(this);
	}
}

void UAoS_InteractionWidget::RefreshWidget_Implementation()
{
}
