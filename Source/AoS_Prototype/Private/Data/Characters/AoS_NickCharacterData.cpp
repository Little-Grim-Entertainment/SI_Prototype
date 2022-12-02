// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Characters/AoS_NickCharacterData.h"

USkeletalMesh* UAoS_NickCharacterData::GetClothingMeshFromName(FName InClothingName) const
{
	for (FNickClothingOptions CurrentOption : ClothingOptions)
	{
		if (CurrentOption.ClothingName == InClothingName)
		{
			return CurrentOption.ClothingBaseMesh;
		}
	}
	return nullptr;
}
