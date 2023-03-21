// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Input/AoS_InputConfig.h"
#include "InputAction.h"


const UInputAction* UAoS_InputConfig::GetInputActionByTag(const FGameplayTag& InInputTag) const
{
	TArray<TArray<FAoS_InputAction>> AllInputActions =
	{
		BasicInputActions,
		DialogueInputActions,
		MovementInputActions,
		GizboInputActions
	};

	for (TArray<FAoS_InputAction> CurrentInputActionArray :AllInputActions)
	{
		for (FAoS_InputAction CurrentInputAction : CurrentInputActionArray)
		{
			if (CurrentInputAction.InputTag == InInputTag)
			{
				return CurrentInputAction.InputAction;
			}
		}
	}

	return nullptr;
}

const TArray<FAoS_InputAction>& UAoS_InputConfig::GetBasicInputActions()
{
	return BasicInputActions;
}

const TArray<FAoS_InputAction>& UAoS_InputConfig::GetDialogueInputActions()
{
	return DialogueInputActions;
}

const TArray<FAoS_InputAction>& UAoS_InputConfig::GetMovementInputActions()
{
	return MovementInputActions;
}

const TArray<FAoS_InputAction>& UAoS_InputConfig::GetGizboInputActions()
{
	return GizboInputActions;
}
