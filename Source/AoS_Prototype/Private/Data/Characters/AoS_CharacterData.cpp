// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Characters/AoS_CharacterData.h"

#include "Data/Cases/AoS_CaseData.h"
#include "Data/Cases/AoS_CaseManager.h"

UAoS_CharacterData::UAoS_CharacterData()
{
	
}

FAoS_DialogueData& UAoS_CharacterData::GetCurrentDialogueData(UAoS_CaseManager* CaseManager)
{
	if (!IsValid(CaseManager)) {return DefaultDialogueData;}

	for(FAoS_DialogueData& CurrentDialogueData : CaseDialogueData)
	{
		if (CurrentDialogueData.Case == CaseManager->GetActiveCase() && CurrentDialogueData.Part == CaseManager->GetActiveCase()->GetActivePart())
		{
			return CurrentDialogueData;
		}
	}
	
	return DefaultDialogueData;
}
