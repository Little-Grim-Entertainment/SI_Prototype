// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_CaseDialogueDataTable.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "Cases/Data/SI_CaseData.h"


USI_CaseDialogueDataTable::USI_CaseDialogueDataTable()
{
	RowStruct = FSI_CaseDialogueDataTableRow::StaticStruct();
}

void USI_CaseDialogueDataTable::AddNewCaseToTable(const USI_CaseData* InCaseData)
{
	if(!IsValid(InCaseData)) {return;}
	const FName RowName = FName(InCaseData->CaseTag.ToString());

	AddRow(RowName, FSI_CaseDialogueDataTableRow(InCaseData));
}
