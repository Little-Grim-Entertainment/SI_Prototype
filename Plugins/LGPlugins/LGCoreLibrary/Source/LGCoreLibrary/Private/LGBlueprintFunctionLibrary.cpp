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
