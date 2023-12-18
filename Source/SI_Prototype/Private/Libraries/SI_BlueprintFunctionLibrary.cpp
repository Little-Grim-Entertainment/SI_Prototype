// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/SI_BlueprintFunctionLibrary.h"

FString USI_BlueprintFunctionLibrary::GetCharacterNameFromTag(const FGameplayTag& InGameplayTag)
{
	FString TagString = InGameplayTag.ToString();
	if(!TagString.Contains("Character.Main")) {return "NONE";}

	TagString = TagString.RightChop(15);

	for (int32 CurrentIndex = 0; CurrentIndex < TagString.Len(); CurrentIndex++)
	{
		const char CurrentChar = TagString[CurrentIndex];
		if(CurrentIndex > 0 && std::isupper(CurrentChar))
		{
			TagString.InsertAt(CurrentIndex, " ");
			return TagString;
		}
	}

	return "NONE";
}
