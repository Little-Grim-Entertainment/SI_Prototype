// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Data/SI_NickCharacterData.h"

USkeletalMesh* USI_NickCharacterData::GetClothingMeshFromName(FName InClothingName) const
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
