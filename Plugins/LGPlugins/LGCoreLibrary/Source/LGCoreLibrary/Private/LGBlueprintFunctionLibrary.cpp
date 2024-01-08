// Fill out your copyright notice in the Description page of Project Settings.


#include "LGBlueprintFunctionLibrary.h"

void ULGBlueprintFunctionLibrary::FNameArrayToFStringArray(const TArray<FName>& InNameArray, TArray<FString>& OutStringArray)
{
	for (const FName& CurrentName : InNameArray)
	{
		FString CurrentString = CurrentName.ToString();
		OutStringArray.Add(CurrentString);
	}
}

FString ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(const FGameplayTag& InGameplayTag)
{
	const FString TagString = InGameplayTag.ToString();
	
	int32 StartingIndex;
	TagString.FindLastChar(TEXT('.'), StartingIndex);

	if(StartingIndex == INDEX_NONE) {return "NONE";}
	
	return TagString.RightChop(StartingIndex + 1);
}

FName ULGBlueprintFunctionLibrary::ConvertFileNameToTagName(const FString& InFileName)
{
	FString TagString = InFileName;

	const FString Underscore = "_";
	const FString Period = ".";
	
	TagString = TagString.Replace(*Underscore, *Period);

	const FName ConvertedTag = FName(TagString);
	
	return ConvertedTag;
}

int32 ULGBlueprintFunctionLibrary::ConvertIntStringToInt(const FString& InIntString)
{
	return *NumberList.Find(InIntString);
}
