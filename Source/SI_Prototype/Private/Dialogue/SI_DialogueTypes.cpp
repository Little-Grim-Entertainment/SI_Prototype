// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueTypes.h"
#include "Cases/Data/SI_CaseData.h"
#include "LGBlueprintFunctionLibrary.h"
#include "Cases/Data/SI_PartData.h"

DEFINE_LOG_CATEGORY(LogSI_Dialogue);

FString FSI_PartDialogueData::GetPartNameNoSpace() const
{
	if(!IsValid(PartReference)) {return "NONE";}

	FString PartNameNoSpace = PartReference->PartName.ToString();
	return PartNameNoSpace;
}

FString FSI_CaseDialogueData::GetCaseNameNoSpace() const
{
	if(!IsValid(CaseReference)) {return "NONE";}

	FString CaseNameNoSpace = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(CaseReference->CaseTag);
	return CaseNameNoSpace;
}

/*FSI_DialogueState::FSI_DialogueState(FSI_PrimaryDialogueArray* InPrimaryDialogueArray) : CasePrimaryDialogueArray(*InPrimaryDialogueArray)
{
}*/

