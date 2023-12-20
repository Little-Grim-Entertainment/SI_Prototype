// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EasyCsvTypes.h"
#include "GameplayTagContainer.h"
//#include "LGDialogueTypes.h"
#include "LGCsvDataTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCsvDataProcessor, Log, All);

USTRUCT(BlueprintType)
struct LGCSVDATAPROCESSOR_API FLGCsvInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString CSVToWrite;

	UPROPERTY()
	FEasyCsvInfo CSVInfoResults;

	UPROPERTY()
	TArray<FString> ExportKeys;

	UPROPERTY()
	TArray<FString> DialogueStringArray;
};

USTRUCT()
struct LGCSVDATAPROCESSOR_API FLGCsvInfoImportPayload
{
	GENERATED_BODY()

	UPROPERTY()
	FString URL;

	UPROPERTY()
	FGuid DialogueStructID;

	UPROPERTY()
	FGuid DialogueArrayID;

	UPROPERTY()
	FString DialogueLabel;
	
	UPROPERTY()
	FString FileName;

	UPROPERTY()
	FString FilePath;

	UPROPERTY()
	FString FolderName;

	UPROPERTY()
	UObject* Caller;

	UPROPERTY()
	FGameplayTag CsvArrayTypeTag;
};