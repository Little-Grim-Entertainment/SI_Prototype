// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/UAoS_CaseList.h"
#include "Data/Cases/AoS_CaseData.h"

TArray<UAoS_CaseData*> UUAoS_CaseList::GetAllCases()
{
	TArray<TArray<UAoS_CaseData*>> AllCaseArrays {
		StoryCases,
		NovaLuxDistrictCases,
		TestCases,
	};
	
	TArray<UAoS_CaseData*> AllCases;
	for (const TArray<UAoS_CaseData*>& CurrentCaseArray : AllCaseArrays)
	{
		if(CurrentCaseArray.IsEmpty()){continue;}
		
		for (UAoS_CaseData* CurrentCaseData : CurrentCaseArray)
		{
			if (!IsValid(CurrentCaseData)){continue;}
			AllCases.AddUnique(CurrentCaseData);
		}
	}
	
	return AllCases;
}
