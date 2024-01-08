// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_DialogueDataTable.h"
#include "SI_CaseDialogueDataTable.generated.h"

class USI_CaseData;

UCLASS()
class SI_PROTOTYPE_API USI_CaseDialogueDataTable : public USI_DialogueDataTable
{
	GENERATED_BODY()

	USI_CaseDialogueDataTable();

public:

	void AddNewCaseToTable(const USI_CaseData* InCaseData);
};
