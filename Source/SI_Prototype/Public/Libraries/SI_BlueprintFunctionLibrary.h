// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SI_BlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Characters")
	static FString GetCharacterNameFromTag(const FGameplayTag& InGameplayTag);
};
