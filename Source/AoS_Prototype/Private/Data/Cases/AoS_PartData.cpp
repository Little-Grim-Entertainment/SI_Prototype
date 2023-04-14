// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_PartData.h"

#include "Data/Cases/AoS_ObjectiveData.h"
#include "Data/Cases/AoS_CaseManager.h"


UAoS_PartData::UAoS_PartData()
{
	bIsComplete = false;
}

TArray<UAoS_ObjectiveData*> UAoS_PartData::GetActiveObjectives() const
{
	TArray<UAoS_ObjectiveData*> ActiveObjectives;
	if (Objectives.Num() > 0)
	{
		for (UAoS_ObjectiveData* CurrentObjective : Objectives)
		{
			if (CurrentObjective && CurrentObjective->GetObjectiveIsActive())
			{
				ActiveObjectives.AddUnique(CurrentObjective);
			}
		}
	}
	return ActiveObjectives;
}

void UAoS_PartData::ResetPart()
{
	bIsActive = false;
	bIsComplete = false;
	for (UAoS_ObjectiveData* CurrentObjective : GetAllObjectives())
	{
		CurrentObjective->ResetObjective();
	}
}

void UAoS_PartData::SetPartComplete(bool bPartCompleted)
{
	bIsComplete = bPartCompleted;
}

void UAoS_PartData::SetPartIsActive(bool bPartIsActive, UAoS_CaseManager* CaseManagerRef)
{
	bIsActive = bPartIsActive;
	if (bIsActive)
	{
		CaseManagerRef->SetActivePart(this);
		ActivateObjectives(CaseManagerRef);
	}
	else
	{
		DeactivateObjectives();
	}
}

void UAoS_PartData::ActivateObjectives(UAoS_CaseManager* CaseManagerRef)
{
	TArray<UAoS_ObjectiveData*> ActiveObjectives;
	
	for (UAoS_ObjectiveData* CurrentObjective : Objectives)
	{
		if (CurrentObjective)
		{
			if (bCompleteObjectivesInOrder)
			{
				if (!CurrentObjective->GetObjectiveComplete())
				{
					CurrentObjective->SetObjectiveIsActive(true);
					CaseManagerRef->OnObjectiveActivated.Broadcast(CurrentObjective);
					ActiveObjectives.AddUnique(CurrentObjective);
					CaseManagerRef->SetActiveObjectives(ActiveObjectives);
					return;	
				}
			}
			else
			{
				ActiveObjectives.AddUnique(CurrentObjective);
				CaseManagerRef->SetActiveObjectives(ActiveObjectives);
				CurrentObjective->SetObjectiveIsActive(true);
				CaseManagerRef->OnObjectiveActivated.Broadcast(CurrentObjective);
			}
		}
	}
}

void UAoS_PartData::DeactivateObjectives()
{
	for (UAoS_ObjectiveData* CurrentObjective : Objectives)
	{
		if (CurrentObjective && !CurrentObjective->GetObjectiveComplete())
		{
			CurrentObjective->SetObjectiveIsActive(false);
		}
	}
}
