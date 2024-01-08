// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LGBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class LGCORELIBRARY_API ULGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Array Conversion")
	static void FNameArrayToFStringArray(const TArray<FName>& InNameArray, TArray<FString>& OutStringArray);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Tags")
	static FString GetLastValueInTagAsString(const FGameplayTag& InGameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Conversion")
	static FName ConvertFileNameToTagName(const FString& InFileName);

	UFUNCTION(BlueprintCallable, Category = "Conversion")
	static int32 ConvertIntStringToInt(const FString& InIntString);
	
private:
	
	static inline TMap<FString, int32> NumberList = {

		{"One",		1},
		{"Two",		2},
		{"Three",	3},
		{"Four",		4},
		{"Five",		5},
		{"Six",		6},
		{"Seven",	7},
		{"Eight",	8},
		{"Nine",		9},
		{"Ten",		10},
		
		};	
};
