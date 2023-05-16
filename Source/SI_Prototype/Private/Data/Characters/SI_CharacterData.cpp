// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Characters/SI_CharacterData.h"

#include "Data/Cases/SI_CaseData.h"
#include "Data/Cases/SI_CaseManager.h"

USI_CharacterData::USI_CharacterData()
{
	
}

FSI_DialogueData& USI_CharacterData::GetCurrentDialogueData(USI_CaseManager* CaseManager)
{
	if (!IsValid(CaseManager)) {return DefaultDialogueData;}

	for(FSI_DialogueData& CurrentDialogueData : CaseDialogueData)
	{
		if (CurrentDialogueData.Case == CaseManager->GetActiveCase() && CurrentDialogueData.Part == CaseManager->GetActivePart())
		{
			return CurrentDialogueData;
		}
	}
	
	return DefaultDialogueData;
}
