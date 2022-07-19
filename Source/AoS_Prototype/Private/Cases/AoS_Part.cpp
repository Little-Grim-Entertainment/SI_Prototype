// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/AoS_Part.h"
#include "Cases/AoS_Objective.h"

UAoS_Part::UAoS_Part()
{
	bIsComplete = false;
}

TArray<UAoS_Objective*> UAoS_Part::GetActiveObjectives() const
{
	TArray<UAoS_Objective*> ActiveObjectives;
	for (UAoS_Objective* CurrentObjective : Objectives)
	{
		if (CurrentObjective->GetObjectiveIsActive())
		{
			ActiveObjectives.AddUnique(CurrentObjective);
		}
	}
	return ActiveObjectives;
}

void UAoS_Part::ResetPart()
{
	bIsActive = false;
	bIsComplete = false;
	for (UAoS_Objective* CurrentObjective : GetAllObjectives())
	{
		CurrentObjective->ResetObjective();
	}
}

void UAoS_Part::SetPartComplete(bool bPartCompleted)
{
	bIsComplete = bPartCompleted;
}

void UAoS_Part::SetPartIsActive(bool bPartIsActive)
{
	bIsActive = bPartIsActive;
	if (bIsActive)
	{
		ActivateObjectives();
	}
	else
	{
		DeactivateObjectives();
	}
}

void UAoS_Part::ActivateObjectives()
{
	for (UAoS_Objective* CurrentObjective : Objectives)
	{
		if (CurrentObjective && !CurrentObjective->GetObjectiveComplete())
		{
			CurrentObjective->SetObjectiveIsActive(true);
			if (bCompleteObjectivesInOrder)
			{
				return;
			}
		}
	}
}

void UAoS_Part::DeactivateObjectives()
{
	for (UAoS_Objective* CurrentObjective : Objectives)
	{
		if (CurrentObjective && !CurrentObjective->GetObjectiveComplete())
		{
			CurrentObjective->SetObjectiveIsActive(false);
		}
	}
}
