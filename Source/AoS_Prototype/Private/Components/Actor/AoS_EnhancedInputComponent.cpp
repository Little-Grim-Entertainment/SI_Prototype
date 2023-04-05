// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/AoS_EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"

UInputMappingContext* UAoS_EnhancedInputComponent::GetPlayerModeInputMappingContext(EPlayerMode InPlayerMode)
{
	for (const FPlayerModeInputMapping CurrentPlayerModeMapping : PlayerModeInputMappings)
	{
		if (InPlayerMode == CurrentPlayerModeMapping.AssociatedPlayerMode)
		{
			return CurrentPlayerModeMapping.MappingContext;
		}
	}
	return nullptr;
}

const UInputAction* UAoS_EnhancedInputComponent::GetActionInput(FString InInputName) const
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

const UInputAction* UAoS_EnhancedInputComponent::GetAxisInput(FString InInputName) const
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
