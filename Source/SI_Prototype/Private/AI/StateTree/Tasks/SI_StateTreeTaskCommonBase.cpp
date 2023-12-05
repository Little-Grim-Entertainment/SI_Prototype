// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Tasks/SI_StateTreeTaskCommonBase.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeLinker.h"

bool FSI_StateTreeTaskCommonBase::Link(FStateTreeLinker& Linker)
{
	Linker.LinkExternalData(SmartObjectSubsystemHandle);
	return true;
}
