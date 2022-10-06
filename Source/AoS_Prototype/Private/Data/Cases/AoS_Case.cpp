// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_Case.h"
#include "Data/Cases/AoS_Part.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "Data/Cases/AoS_CaseManager.h"

UAoS_Case::UAoS_Case()
{
	bIsComplete = false;
	bIsActive = false;
}

UAoS_Part* UAoS_Case::GetActivePart() const
{
	for (UAoS_Part* CurrentPart : Parts)
	{
		if (CurrentPart->GetPartIsActive())
		{
			return CurrentPart;
		}
	}
	return nullptr;
}

void UAoS_Case::ResetCase()
{
	bIsActive = false;
	bIsComplete = false;
	for (UAoS_Part* CurrentPart : GetAllParts())
	{
		CurrentPart->ResetPart();
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Case %s reset."), *GetName()));
}

void UAoS_Case::SetCaseComplete(bool bCaseCompleted)
{
	bIsComplete = bCaseCompleted;
}

void UAoS_Case::SetCaseIsActive(bool bCaseIsActive, UAoS_CaseManager* CaseManagerRef)
{
	bIsActive = bCaseIsActive;
	if (bIsActive)
	{
		ActivatePart(CaseManagerRef);
	}
	else
	{
		DeactivatePart(CaseManagerRef);
	}
}

void UAoS_Case::ActivatePart(UAoS_CaseManager* CaseManagerRef)
{
	for (UAoS_Part* CurrentPart : Parts)
	{
		if (CurrentPart && !CurrentPart->GetPartIsComplete())
		{
			CurrentPart->SetPartIsActive(true, CaseManagerRef);
			CaseManagerRef->OnPartActivated.Broadcast(CurrentPart);
			return;
		}
	}
}

void UAoS_Case::DeactivatePart(UAoS_CaseManager* CaseManagerRef)
{
	for (UAoS_Part* CurrentPart : Parts)
	{
		if (CurrentPart && CurrentPart->GetPartIsActive())
		{
			CurrentPart->SetPartIsActive(false, CaseManagerRef);
			return;
		}
	}
}


