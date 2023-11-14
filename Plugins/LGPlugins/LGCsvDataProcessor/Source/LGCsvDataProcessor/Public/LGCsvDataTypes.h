// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EasyCsvTypes.h"
#include "RuntimeDataTableTypes.h"
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

USTRUCT()
struct LGCSVDATAPROCESSOR_API FLGCsvInfoImportPayload
{
	GENERATED_BODY()

	UPROPERTY()
	FString URL;

	UPROPERTY()
	FString FilePath;

	UPROPERTY()
	FString FileName;

	UPROPERTY()
	UObject* Caller;

	FOnImportComplete OnImportCompleteDelegate;
};