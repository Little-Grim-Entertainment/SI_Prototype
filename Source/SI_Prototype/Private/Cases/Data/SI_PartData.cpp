// Fill out your copyright notice in the Description page of Project Settings.


#include "Cases/Data/SI_PartData.h"
#include "LGBlueprintFunctionLibrary.h"


USI_PartData::USI_PartData()
{
	
}

FString USI_PartData::GetPartNameNoSpace() const
{
	if(PartName.IsEmpty()) {return FString();}

	FString PartNameString = PartName.ToString();
	const int32 SpaceIndex = PartNameString.Find(" ");
	PartNameString.RemoveAt(SpaceIndex);

	return PartNameString;
}

FString USI_PartData::GetPartNameTruncated() const
{
	const FString PartNameString = PartName.ToString();
	const int32 SpaceIndex = PartNameString.Find(" ");
	const int32 ChopIndex = PartNameString.Len() - SpaceIndex;

	const FString NumberText = PartNameString.RightChop(ChopIndex + 1);

	const int32 NumberValue = ULGBlueprintFunctionLibrary::ConvertIntStringToInt(NumberText);

	FString ReturnString = "P";
	if(NumberValue < 10)
	{
		ReturnString.Append("0");
	}
	ReturnString.Append(FString::FromInt(NumberValue));

	return ReturnString;
}
