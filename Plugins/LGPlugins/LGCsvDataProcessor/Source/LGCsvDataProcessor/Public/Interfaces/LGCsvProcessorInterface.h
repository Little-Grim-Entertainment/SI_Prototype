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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueProcessing")
	void OnCsvProcessComplete(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueProcessing")
	void OnRequestCheckForEmbeddedCsv(const FGameplayTag& InStructType, const FString& InSavePath, const FString& InDialogueLabel, FGuid& InDialogueDataID, FGuid& InDialogueArrayID);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueProcessing")
	bool StructTypeHasEmbeddedCsv(const FGameplayTag& InStructType);
};
