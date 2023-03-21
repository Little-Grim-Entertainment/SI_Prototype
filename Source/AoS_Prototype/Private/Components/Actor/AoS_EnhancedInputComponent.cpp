// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/AoS_EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"

UInputMappingContext* UAoS_EnhancedInputComponent::GetPlayerModeInputMappingContext(EPlayerMode InPlayerMode)
{
	for (FPlayerModeInputMapping CurrentPlayerModeMapping : PlayerModeInputMappings)
	{
		if (InPlayerMode == CurrentPlayerModeMapping.AssociatedPlayerMode)
		{
			return CurrentPlayerModeMapping.MappingContext;
		}
	}
	
	return nullptr;
}

UInputAction* UAoS_EnhancedInputComponent::GetActionInput(FString InInputName)
{
	for (FPlayerModeInputMapping CurrentMapping : PlayerModeInputMappings)
	{
		if(CurrentMapping.ActionInputs.Contains(InInputName))
		{
			return *CurrentMapping.ActionInputs.Find(InInputName);
		}
	}
	return nullptr;
}

UInputAction* UAoS_EnhancedInputComponent::GetAxisInput(FString InInputName)
{
	for (FPlayerModeInputMapping CurrentMapping : PlayerModeInputMappings)
	{
		if(CurrentMapping.AxisInputs.Contains(InInputName))
		{
			return *CurrentMapping.AxisInputs.Find(InInputName);
		}
	}
	return nullptr;
}



