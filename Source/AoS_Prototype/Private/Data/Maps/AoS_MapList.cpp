// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Maps/AoS_MapList.h"

UAoS_MapList::UAoS_MapList()
{
	
}

TArray<UAoS_MapData*> UAoS_MapList::GetAllMaps()
{
	TArray<UAoS_MapData*> AllMaps;
	if (!MenuMaps.IsEmpty())
	{
		for (UAoS_MapData* CurrentMap : MenuMaps)
		{
			AllMaps.AddUnique(CurrentMap);
		}	
	}
	if (!NovaLuxDistrictInteriorMaps.IsEmpty())
	{
		for (UAoS_MapData* CurrentMap : NovaLuxDistrictInteriorMaps)
		{
			AllMaps.AddUnique(CurrentMap);
		}
	}
	if (!NovaLuxDistrictExteriorMaps.IsEmpty())
	{
		for (UAoS_MapData* CurrentMap : NovaLuxDistrictExteriorMaps)
		{
			AllMaps.AddUnique(CurrentMap);
		}
	}
	if (!TestMaps.IsEmpty())
	{
		for (UAoS_MapData* CurrentMap : TestMaps)
		{
			AllMaps.AddUnique(CurrentMap);
		}
	}
	
	return AllMaps;
}


