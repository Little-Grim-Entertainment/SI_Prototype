// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/Data/SI_MapList.h"
#include "Levels/Data/SI_MapData.h"

USI_MapList::USI_MapList()
{
	
}

TArray<USI_MapData*> USI_MapList::GetAllMaps()
{
	TArray<TArray<USI_MapData*>> AllMapArrays {
		MenuMaps,
		NovaLuxDistrictInteriorMaps,
		NovaLuxDistrictExteriorMaps,
		TestMaps
	};
	
	TArray<USI_MapData*> AllMaps;
	for (const TArray<USI_MapData*>& CurrentMapArray : AllMapArrays)
	{
		if(CurrentMapArray.IsEmpty()){continue;}
		
		for (USI_MapData* CurrentMapData : CurrentMapArray)
		{
			if (!IsValid(CurrentMapData)){continue;}
			AllMaps.AddUnique(CurrentMapData);
		}
	}
	
	return AllMaps;
}


