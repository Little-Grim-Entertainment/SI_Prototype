// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Data/SI_CharacterList.h"
#include "Characters/Data/SI_CharacterData.h"

USI_CharacterData* USI_CharacterList::GetCharacterDataByTag(const FGameplayTag& InCharacterTag)
{
	TArray<TSoftObjectPtr<USI_CharacterData>> CombinedCharacterData;
	CombinedCharacterData.AddUnique(NickData);
	CombinedCharacterData.AddUnique(GizboData);
	CombinedCharacterData.Append(MainCharacters);
	CombinedCharacterData.Append(SideCharacters);
	CombinedCharacterData.Append(TestCharacters);

	for(TSoftObjectPtr<USI_CharacterData>& CharacterDataSftPtr : CombinedCharacterData)
	{
		USI_CharacterData* CharacterData = CharacterDataSftPtr.Get();
		if(!IsValid(CharacterData) || CharacterData->CharacterTag != InCharacterTag)  {continue;}

		return CharacterData;
	}

	return nullptr;
}
