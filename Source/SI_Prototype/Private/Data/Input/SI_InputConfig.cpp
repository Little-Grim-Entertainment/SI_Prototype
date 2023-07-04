// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Input/SI_InputConfig.h"
#include "InputAction.h"


const UInputAction* USI_InputConfig::GetInputActionByTag(const FGameplayTag& InInputTag) const
{
	TArray<TArray<FSI_InputAction>> AllInputActions =
	{
		BasicInputActions,
		DialogueInputActions,
		MovementInputActions,
		GizboInputActions
	};

	for (TArray<FSI_InputAction> CurrentInputActionArray :AllInputActions)
	{
		for (FSI_InputAction CurrentInputAction : CurrentInputActionArray)
		{
			if (CurrentInputAction.GetInputTag() == InInputTag)
			{
				return CurrentInputAction.GetInputAction();
			}
		}
	}

	return nullptr;
}

const UInputMappingContext* USI_InputConfig::GetInputMappingByTag(const FGameplayTag& InAssociatedPlayerModeTag, const FGameplayTag& InSecondaryTag) const
{
	TArray<FSI_InputMapping> MatchedMappings;

	if (!InAssociatedPlayerModeTag.IsValid()) {return nullptr;}
	
	for (FSI_InputMapping CurrentInputMapping: PrimaryInputMappings)
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
			for (const FSI_InputMapping CurrentInputMapping : MatchedMappings)
			{
				if(CurrentInputMapping.IsDefaultMappingForMode())
				{
					return CurrentInputMapping.GetInputMappingContext();
				}
			}
		}
		else
		{
			for (FSI_InputMapping CurrentInputMapping : MatchedMappings)
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

const TArray<FSI_InputMapping>& USI_InputConfig::GetPrimaryInputMappings()
{
	return PrimaryInputMappings;
}

const TArray<FSI_InputMapping>& USI_InputConfig::GetSecondaryInputMappings()
{
	return SecondaryInputMappings;
}

const TArray<FSI_InputAction>& USI_InputConfig::GetBasicInputActions()
{
	return BasicInputActions;
}

const TArray<FSI_InputAction>& USI_InputConfig::GetDialogueInputActions()
{
	return DialogueInputActions;
}

const TArray<FSI_InputAction>& USI_InputConfig::GetMovementInputActions()
{
	return MovementInputActions;
}

const TArray<FSI_InputAction>& USI_InputConfig::GetGizboInputActions()
{
	return GizboInputActions;
}
