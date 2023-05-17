// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/SI_CaseList.h"
#include "Data/Cases/SI_CaseData.h"

TArray<USI_CaseData*> USI_CaseList::GetAllCases()
{
	TArray<TArray<USI_CaseData*>> AllCaseArrays {
		StoryCases,
		NovaLuxDistrictCases,
		TestCases,
	};
	
	TArray<USI_CaseData*> AllCases;
	for (const TArray<USI_CaseData*>& CurrentCaseArray : AllCaseArrays)
	{
		if(CurrentCaseArray.IsEmpty()){continue;}
		
		for (USI_CaseData* CurrentCaseData : CurrentCaseArray)
		{
			if (!IsValid(CurrentCaseData)){continue;}
			AllCases.AddUnique(CurrentCaseData);
		}
	}
	
	return AllCases;
}
