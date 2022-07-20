// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"

#include "Cases/AoS_CaseManager.h"

UAoS_GameInstance::UAoS_GameInstance()
{
	
}

void UAoS_GameInstance::ResetCase(FString CaseToResetName)
{
	if (CaseManager)
	{
		if (CaseToResetName == "All")
		{
			CaseManager->ResetAllCases();
		}
		else
		{
			CaseManager->ResetCase(CaseToResetName);
		}
	}
}

void UAoS_GameInstance::Init()
{
	Super::Init();

	CaseManager = GetSubsystem<UAoS_CaseManager>();
}
