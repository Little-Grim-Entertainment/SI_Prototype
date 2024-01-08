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
	const FName RowName = FName(InCaseData->CaseTag.ToString());
	const FSI_CaseDialogueData CaseDialogueData = FSI_CaseDialogueData(InCaseData);
	const FSI_CaseDialogueDataTableRow CaseDialogueDataTableRow = FSI_CaseDialogueDataTableRow(CaseDialogueData);

	AddRow(RowName, CaseDialogueDataTableRow);
}
