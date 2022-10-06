// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Maps/AoS_MapList.h"

UAoS_MapList::UAoS_MapList()
{
	
}

TArray<UAoS_MapData*> UAoS_MapList::GetAllMaps()
{
	TArray<UAoS_MapData*> AllMaps;
	for (UAoS_MapData* CurrentMap : MenuMaps)
	{
		AllMaps.AddUnique(CurrentMap);
	}
	for (UAoS_MapData* CurrentMap : GlassDistrictInteriorMaps)
	{
		AllMaps.AddUnique(CurrentMap);
	}
	for (UAoS_MapData* CurrentMap : GlassDistrictExteriorMaps)
	{
		AllMaps.AddUnique(CurrentMap);
	}
	for (UAoS_MapData* CurrentMap : TestMaps)
	{
		AllMaps.AddUnique(CurrentMap);
	}
	return AllMaps;
}


