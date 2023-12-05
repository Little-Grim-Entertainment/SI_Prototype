// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGCsvDataTypes.h"
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
	void OnInteractComplete(UObject* Caller, const FLGCsvInfo& InCvsInfo);
};
