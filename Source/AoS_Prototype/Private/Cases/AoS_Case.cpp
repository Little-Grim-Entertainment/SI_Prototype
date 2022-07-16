// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/AoS_Case.h"
#include "Cases/AoS_Part.h"

UAoS_Case::UAoS_Case()
{
	bIsComplete = false;
}

void UAoS_Case::ResetCase()
{
	bIsActive = false;
	bIsComplete = false;
	ActivePart = nullptr;
	for (UAoS_Part* CurrentPart : GetAllParts())
	{
		CurrentPart->ResetPart();
	}
}

void UAoS_Case::SetCaseComplete(bool bCaseCompleted)
{
	bIsComplete = bCaseCompleted;
}

void UAoS_Case::SetCaseIsActive(bool bCaseIsActive)
{
	bIsActive = bCaseIsActive;
	if (bIsActive)
	{
		ActivatePart();
	}
	else
	{
		DeactivatePart();
	}
}

void UAoS_Case::ActivatePart()
{
	for (UAoS_Part* CurrentPart : Parts)
	{
		if (CurrentPart && !CurrentPart->GetPartIsComplete())
		{
			CurrentPart->SetPartIsActive(true);
			ActivePart = CurrentPart;
			return;
		}
	}
}

void UAoS_Case::DeactivatePart()
{
	for (UAoS_Part* CurrentPart : Parts)
	{
		if (CurrentPart && !CurrentPart->GetPartIsComplete())
		{
			CurrentPart->SetPartIsActive(false);
		}
	}
}


