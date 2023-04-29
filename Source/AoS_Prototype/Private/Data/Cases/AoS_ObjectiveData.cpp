// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_ObjectiveData.h"

UAoS_ObjectiveData::UAoS_ObjectiveData()
{

}

bool UAoS_ObjectiveData::HasLevelMediaAssignments()
{
	if(LevelMediaAssignments.Num() > 0)
	{
		return true;
	}
	return false;
}

