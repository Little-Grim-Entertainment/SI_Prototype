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
			if (CurrentInputAction.GetInputTag() == InInputTag)
			{
				return CurrentInputAction.GetInputAction();
			}
		}
	}

	return nullptr;
}

const UInputMappingContext* UAoS_InputConfig::GetInputMappingByTag(const FGameplayTag& InAssociatedPlayerModeTag, const FGameplayTag& InSecondaryTag) const
{
	TArray<FAoS_InputMapping> MatchedMappings;

	if (!InAssociatedPlayerModeTag.IsValid()) {return nullptr;}
	
	for (FAoS_InputMapping CurrentInputMapping: InputMappings)
	{
		if(CurrentInputMapping.GetAssociatedTag() == InAssociatedPlayerModeTag)
		{
			MatchedMappings.AddUnique(CurrentInputMapping);
		}
	}
	
	if (MatchedMappings.Num() > 1)
	{
		if (!InSecondaryTag.IsValid())
		{
			for (const FAoS_InputMapping CurrentInputMapping : MatchedMappings)
			{
				if(CurrentInputMapping.IsDefaultMappingForMode())
				{
					return CurrentInputMapping.GetInputMappingContext();
				}
			}
		}
		else
		{
			for (FAoS_InputMapping CurrentInputMapping : MatchedMappings)
			{
				if(CurrentInputMapping.GetSecondaryTag() == InSecondaryTag)
				{
					return CurrentInputMapping.GetInputMappingContext();
				}
			}
		}
	}
	else if(MatchedMappings.Num() == 1)
	{
		return MatchedMappings[0].GetInputMappingContext();
	}

	return nullptr;
}

const TArray<FAoS_InputMapping>& UAoS_InputConfig::GetInputMappings()
{
	return InputMappings;
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
