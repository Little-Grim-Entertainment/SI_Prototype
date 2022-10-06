// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_Part.h"
#include "Data/Cases/AoS_Objective.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "Data/Cases/AoS_CaseManager.h"

UAoS_Part::UAoS_Part()
{
	bIsComplete = false;
}

TArray<UAoS_Objective*> UAoS_Part::GetActiveObjectives() const
{
	TArray<UAoS_Objective*> ActiveObjectives;
	if (Objectives.Num() > 0)
	{
		for (UAoS_Objective* CurrentObjective : Objectives)
		{
			if (CurrentObjective && CurrentObjective->GetObjectiveIsActive())
			{
				ActiveObjectives.AddUnique(CurrentObjective);
			}
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

void UAoS_Part::SetPartIsActive(bool bPartIsActive, UAoS_CaseManager* CaseManagerRef)
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

void UAoS_Part::ActivateObjectives(UAoS_CaseManager* CaseManagerRef)
{
	TArray<UAoS_Objective*> ActiveObjectives;
	
	for (UAoS_Objective* CurrentObjective : Objectives)
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
