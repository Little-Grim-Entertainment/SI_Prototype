// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_HUD.h"
#include "DlgContext.h"
#include "Cases/AoS_CaseManager.h"

UAoS_HUD::UAoS_HUD()
{
	bBindingsSetup = false;
}

void UAoS_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	CaseManagerRef = GetGameInstance()->GetSubsystem<UAoS_CaseManager>();

	if (CaseManagerRef && !bBindingsSetup)
	{
		SetupBindings();
	}
}

void UAoS_HUD::SetupBindings()
{
	CaseManagerRef->OnObjectiveComplete.AddDynamic(this, &UAoS_HUD::OnObjectiveComplete);
	bBindingsSetup = true;
}

void UAoS_HUD::DisplayDialogueBox_Implementation(UDlgContext* DlgContext)
{
	
}

void UAoS_HUD::OnObjectiveComplete_Implementation(UAoS_Objective* CompletedObjective)
{
	
}