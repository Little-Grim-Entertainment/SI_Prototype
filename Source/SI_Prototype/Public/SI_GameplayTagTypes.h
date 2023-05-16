// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SI_GameplayTagTypes.generated.h"

USTRUCT(BlueprintType)
struct FSI_GameplayTag : public FGameplayTag
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FSI_GameplayTagContainer : public FGameplayTagContainer
{
	GENERATED_BODY()

	void SetParentTag(const FGameplayTag& InParentTag);
	const FGameplayTag& GetParentTag() const;
		
private:

	FGameplayTag ParentTag;
};
