// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/AoS_CaseManager.h"
#include "Cases/AoS_Case.h"
#include "Cases/AoS_Part.h"
#include "Cases/AoS_Objective.h"

UAoS_CaseManager::UAoS_CaseManager()
{
	
}

void UAoS_CaseManager::AcceptCase(UAoS_Case* CaseToAccept)
{
	if (!CaseToAccept)
	{
		return;
	}
	
	AcceptedCases.AddUnique(CaseToAccept);
	OnCaseAccepted.Broadcast(CaseToAccept);	
}

void UAoS_CaseManager::SetActiveCase(UAoS_Case* CaseToSet)
{
	if (!CaseToSet)
	{
		return;
	}
	
	if (ActiveCase)
	{
		ActiveCase->SetCaseIsActive(false);
	}
	
	CaseToSet->SetCaseIsActive(true);
	ActiveCase = CaseToSet;
}

void UAoS_CaseManager::CompleteObjective(UAoS_Objective* ObjectiveToComplete)
{
	if (!ObjectiveToComplete)
	{
		return;
	}
	
	for (const UAoS_Objective* CurrentObjective : ActiveCase->GetActivePart()->GetActiveObjectives())
	{
		if (ObjectiveToComplete == CurrentObjective && CurrentObjective->GetObjectiveIsActive())
		{
			ObjectiveToComplete->SetObjectiveComplete(true);
			ObjectiveCompleted(ObjectiveToComplete);
		}
	}
}

UAoS_Case* UAoS_CaseManager::GetActiveCase() const
{
	return ActiveCase;
}

TArray<UAoS_Case*> UAoS_CaseManager::GetAcceptedCases() const
{
	return AcceptedCases;
}

UAoS_Part* UAoS_CaseManager::GetActivePart() const
{
	return ActiveCase->GetActivePart();
}

TArray<UAoS_Objective*> UAoS_CaseManager::GetActiveObjectives() const
{
	return ActiveCase->GetActivePart()->GetActiveObjectives();
}

void UAoS_CaseManager::ObjectiveCompleted(UAoS_Objective* CompletedObjective)
{
	if (!CompletedObjective)
	{
		return;
	}
	
	if (ActiveCase->GetActivePart()->GetActiveObjectives().Num() > 0)
	{
		ActiveCase->GetActivePart()->GetActiveObjectives().RemoveSingle(CompletedObjective);
	}
	if(!CheckForCompletedPart())
	{
		OnObjectiveComplete.Broadcast(CompletedObjective);
	}
}

void UAoS_CaseManager::PartCompleted(UAoS_Part* CompletedPart)
{
	if (!CompletedPart)
	{
		return;
	}
	
	if(!CheckForCompletedCase())
	{
		OnPartComplete.Broadcast(CompletedPart);
	}
}

void UAoS_CaseManager::CaseCompleted(UAoS_Case* CompletedCase)
{
	if (!CompletedCase)
	{
		return;
	}
	
	OnCaseComplete.Broadcast(CompletedCase);
}

bool UAoS_CaseManager::CheckForCompletedPart()
{
	int32 CompletedObjectives = 0;
	for (const UAoS_Objective* CurrentObjective : ActiveCase->GetActivePart()->GetAllObjectives())
	{
		if(CurrentObjective->GetObjectiveComplete())
		{
			CompletedObjectives++;
		}
	}
	if (CompletedObjectives == ActiveCase->GetActivePart()->GetAllObjectives().Num())
	{
		ActiveCase->GetActivePart()->SetPartComplete(true);
		PartCompleted(ActiveCase->GetActivePart());
		return true;
	}
	
	ActiveCase->GetActivePart()->ActivateObjectives();
	return false;
}

bool UAoS_CaseManager::CheckForCompletedCase()
{
	int32 CompletedParts = 0;
	for (const UAoS_Part* CurrentPart : ActiveCase->GetAllParts())
	{
		if(CurrentPart->GetPartIsComplete())
		{
			CompletedParts++;
		}
	}
	if (CompletedParts == ActiveCase->GetAllParts().Num())
	{
		ActiveCase->SetCaseComplete(true);
		CaseCompleted(ActiveCase);
		return true;
	}
	
	ActiveCase->ActivatePart();
	return false;
}
