// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/Data/SI_ObjectiveData.h"

USI_ObjectiveData::USI_ObjectiveData()
{

}

bool USI_ObjectiveData::HasLevelMediaAssignments()
{
	if(LevelMediaAssignments.Num() > 0)
	{
		return true;
	}
	return false;
}

