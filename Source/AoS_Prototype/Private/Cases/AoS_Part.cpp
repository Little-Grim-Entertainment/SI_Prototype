// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/AoS_Part.h"
#include "Cases/AoS_Objective.h"

UAoS_Part::UAoS_Part()
{
	bIsComplete = false;
}

void UAoS_Part::SetPartComplete(bool bPartCompleted)
{
	bIsComplete = bPartCompleted;
	bIsActive = !bPartCompleted;
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
	if (ActiveObjectives.Num() > 0)
	{
		ActiveObjectives.Empty();
	}
	
	for (UAoS_Objective* CurrentObjective : Objectives)
	{
		if (CurrentObjective && !CurrentObjective->GetObjectiveComplete())
		{
			CurrentObjective->SetObjectiveIsActive(true);
			ActiveObjectives.AddUnique(CurrentObjective);
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
