// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EasyCsvTypes.generated.h"

USTRUCT(BlueprintType)
struct FEasyCsvStringValueArray
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "easyCSV")
	TArray<FString> StringValues;
};

USTRUCT(BlueprintType)
struct FEasyCsvInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "easyCSV")
	TMap<FName, FEasyCsvStringValueArray> CSV_Map;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "easyCSV")
	TArray<FName> CSV_Keys;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "easyCSV")
	TArray<FString> CSV_Headers;
};
