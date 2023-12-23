// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveData/SI_SaveData_CharacterStates.h"

USI_SaveData_CharacterStates::USI_SaveData_CharacterStates()
{
}

void USI_SaveData_CharacterStates::UpdateCharacterState(const FSI_CharacterState& InCharacterState)
{
	FSI_CharacterState* FoundCharacterState = CharacterStates.Find(InCharacterState.GetCharacterTag());
	if(FoundCharacterState)
	{
		*FoundCharacterState = InCharacterState;
		return;
	}
	
	AddNewCharacterState(InCharacterState);
}

void USI_SaveData_CharacterStates::AddNewCharacterState(const FSI_CharacterState& InCharacterState)
{
	const TPair<FGameplayTag, FSI_CharacterState> NewCharacterStatePair = TPair<FGameplayTag, FSI_CharacterState>(InCharacterState.GetCharacterTag(), InCharacterState);
	CharacterStates.Add(NewCharacterStatePair);
}
