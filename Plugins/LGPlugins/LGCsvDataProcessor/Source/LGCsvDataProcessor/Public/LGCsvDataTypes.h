// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EasyCsv/Public/EasyCsv.h"

#include "LGCsvDataTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCsvDataProcessor, Log, All);

USTRUCT()
struct LGCSVDATAPROCESSOR_API FLGCsvStrings
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct LGCSVDATAPROCESSOR_API FLGCsvInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FLGCsvStrings> CsvStrings;

	UPROPERTY()
	FString CSVToWrite;

	UPROPERTY()
	FEasyCsvInfo CSVInfoResults;

	UPROPERTY()
	TArray<FString> ExportKeys;
};