// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/AoS_Objective.h"

UAoS_Objective::UAoS_Objective()
{
	bIsComplete = false;
	bIsActive = false;
}

void UAoS_Objective::ResetObjective()
{
	bIsComplete = false;
	bIsActive = false;
}

void UAoS_Objective::SetObjectiveComplete(bool bObjectiveCompleted)
{
	bIsComplete = bObjectiveCompleted;
}

void UAoS_Objective::SetObjectiveIsActive(bool bObjectiveIsActive)
{
	bIsActive = bObjectiveIsActive;
}


