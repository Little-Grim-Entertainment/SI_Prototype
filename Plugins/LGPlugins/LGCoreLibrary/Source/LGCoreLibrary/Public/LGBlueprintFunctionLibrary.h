// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
};
