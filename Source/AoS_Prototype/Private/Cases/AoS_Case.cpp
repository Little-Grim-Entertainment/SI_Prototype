// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/AoS_Case.h"

UAoS_Case::UAoS_Case()
{
	bIsComplete = false;
}

void UAoS_Case::CompleteObjective()
{
	bIsComplete = true;
}
