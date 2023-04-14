// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Maps/AoS_MapList.h"
#include "Data/Maps/AoS_MapData.h"

UAoS_MapList::UAoS_MapList()
{
	
}

TArray<UAoS_MapData*> UAoS_MapList::GetAllMaps()
{
	TArray<TArray<UAoS_MapData*>> AllMapArrays {
		MenuMaps,
		NovaLuxDistrictInteriorMaps,
		NovaLuxDistrictExteriorMaps,
		TestMaps
	};
	
	TArray<UAoS_MapData*> AllMaps;
	for (const TArray<UAoS_MapData*>& CurrentMapArray : AllMapArrays)
	{
		if(CurrentMapArray.IsEmpty()){continue;}
		
		for (UAoS_MapData* CurrentMapData : CurrentMapArray)
		{
			if (!IsValid(CurrentMapData)){continue;}
			AllMaps.AddUnique(CurrentMapData);
		}
	}
	
	return AllMaps;
}


