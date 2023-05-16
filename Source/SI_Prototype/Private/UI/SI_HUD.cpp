// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_HUD.h"
#include "UI/SI_DialogueBox.h"
#include "Data/Cases/SI_CaseManager.h"

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

void USI_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	CaseManagerRef = GetGameInstance()->GetSubsystem<USI_CaseManager>();

	if (CaseManagerRef && !bBindingsSetup)
	{
		SetupBindings();
	}
}

void USI_HUD::SetupBindings()
{
	CaseManagerRef->OnObjectiveComplete().AddDynamic(this, &USI_HUD::OnObjectiveComplete);
	bBindingsSetup = true;
}

void USI_HUD::OnObjectiveComplete_Implementation(USI_ObjectiveData* CompletedObjective)
{
	
}