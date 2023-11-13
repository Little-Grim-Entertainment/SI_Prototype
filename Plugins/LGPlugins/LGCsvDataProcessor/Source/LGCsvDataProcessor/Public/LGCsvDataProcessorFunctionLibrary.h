// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LGCsvDataTypes.h"
#include "LGCsvDataProcessorFunctionLibrary.generated.h"

struct FRuntimeDataTableCallbackInfo;

UCLASS()
class LGCSVDATAPROCESSOR_API ULGCsvDataProcessorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	static void ImportCsvFromURL(const FString& InURL, const FString& InFilePath, const FString& InFileName);

	UFUNCTION()
	static void FNameArrayToFStringArray(const TArray<FName>& InNameArray, TArray<FString>& OutStringArray);

private:

	void OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo);
};
