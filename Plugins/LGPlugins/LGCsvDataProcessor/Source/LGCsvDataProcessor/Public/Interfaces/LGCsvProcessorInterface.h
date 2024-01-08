// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuntimeDataTable.h"
#include "LGDialogueTypes.h"
#include "UObject/Interface.h"
#include "LGCsvProcessorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULGCsvProcessorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LGCSVDATAPROCESSOR_API ILGCsvProcessorInterface
{
	GENERATED_BODY()

public:

	// This gets called once the CSVs have successfully been downloaded.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueProcessing")
	void OnCsvProcessComplete(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr);

	// This should be overriden to get any embedded CSVs and process them as well.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueProcessing")
	void OnRequestCheckForEmbeddedCsv(const FRuntimeDataTableCallbackInfo& InCallbackInfo, const FString& InSavePath);

	// Use if there is a quick check to determine if OnRequestCheckForEmbeddedCsv should be ran.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueProcessing")
	bool StructTypeHasEmbeddedCsv(const FGameplayTag& InStructType);
};
