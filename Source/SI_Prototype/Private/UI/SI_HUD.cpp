// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_HUD.h"
#include "UI/SI_DialogueBox.h"
#include "Data/Cases/SI_CaseManager.h"
#include "UI/SI_QuickActionWidget.h"

USI_HUD::USI_HUD()
{
	bBindingsSetup = false;
	if (IsValid(CaseAcceptedWidget))
	{
		CaseAcceptedWidget->SetRenderOpacity(0.0f);
	}
}

USI_DialogueBox* USI_HUD::GetDialogueBox() const
{
	return DialogueBox;
}

USI_UserWidget* USI_HUD::GetReticle() const
{
	return Reticle;
}

void USI_HUD::UpdateQuickActionWidget(const FGameplayTag& InUITag)
{
	if (!IsValid(QuickActionWidget))
	{
		CreateWidget(QuickActionWidget);
	}
	
	QuickActionWidget->RefreshQuickActionWidget(InUITag);
}

FGameplayTag USI_HUD::GetQuickActionAbilityTag(const FGameplayTag& InQuickActionTag) const
{
	return QuickActionWidget->GetQuickActionAbilityTag(InQuickActionTag);
}

void USI_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	CaseManagerRef = GetGameInstance()->GetSubsystem<USI_CaseManager>();

	if (CaseManagerRef && !bBindingsSetup)
	{
		SetupBindings();
	}

	if (!IsValid(QuickActionWidget))
	{
		CreateWidget(QuickActionWidget);
	}
	QuickActionWidget->RefreshQuickActionWidget(SITag_UI_HUD_QuickAction);
}

void USI_HUD::SetupBindings()
{
	CaseManagerRef->OnObjectiveComplete().AddDynamic(this, &USI_HUD::OnObjectiveComplete);
	bBindingsSetup = true;
}

void USI_HUD::OnObjectiveComplete_Implementation(USI_ObjectiveData* CompletedObjective)
{
	
}