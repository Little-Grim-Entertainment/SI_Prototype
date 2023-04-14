// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_CaseData.h"
#include "Data/Cases/AoS_PartData.h"
#include "Data/Cases/AoS_CaseManager.h"

UAoS_CaseData::UAoS_CaseData()
{
	bIsComplete = false;
	bIsActive = false;
}

UAoS_PartData* UAoS_CaseData::GetActivePart() const
{
	for (UAoS_PartData* CurrentPart : Parts)
	{
		if (CurrentPart->GetPartIsActive())
		{
			return CurrentPart;
		}
	}
	return nullptr;
}

void UAoS_CaseData::ResetCase()
{
	bIsActive = false;
	bIsComplete = false;
	for (UAoS_PartData* CurrentPart : GetAllParts())
	{
		CurrentPart->ResetPart();
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Case %s reset."), *GetName()));
}

void UAoS_CaseData::SetCaseComplete(bool bCaseCompleted)
{
	bIsComplete = bCaseCompleted;
}

void UAoS_CaseData::SetCaseIsActive(bool bCaseIsActive, UAoS_CaseManager* CaseManagerRef)
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

void UAoS_CaseData::ActivatePart(UAoS_CaseManager* CaseManagerRef)
{
	for (UAoS_PartData* CurrentPart : Parts)
	{
		if (CurrentPart && !CurrentPart->GetPartIsComplete())
		{
			CurrentPart->SetPartIsActive(true, CaseManagerRef);
			CaseManagerRef->OnPartActivated.Broadcast(CurrentPart);
			return;
		}
	}
}

void UAoS_CaseData::DeactivatePart(UAoS_CaseManager* CaseManagerRef)
{
	for (UAoS_PartData* CurrentPart : Parts)
	{
		if (CurrentPart && CurrentPart->GetPartIsActive())
		{
			CurrentPart->SetPartIsActive(false, CaseManagerRef);
			return;
		}
	}
}


