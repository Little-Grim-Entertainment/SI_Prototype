// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_CaseDialogueDataAsset.h"

#include "LGBlueprintFunctionLibrary.h"
#include "Cases/Data/SI_CaseData.h"

FString USI_CaseDialogueDataAsset::GetCaseNameNoSpace() const
{
	if(!IsValid(CaseReference)) {return "NONE";}

	FString CaseNameNoSpace = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(CaseReference->CaseTag);
	return CaseNameNoSpace;
}
