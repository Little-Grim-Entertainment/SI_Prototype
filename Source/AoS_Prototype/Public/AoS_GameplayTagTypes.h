// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AoS_GameplayTagTypes.generated.h"

USTRUCT(BlueprintType, meta = (HasNativeMake = "GameplayTags.BlueprintGameplayTagLibrary.MakeLiteralGameplayTag", HasNativeBreak = "GameplayTags.BlueprintGameplayTagLibrary.GetTagName", DisableSplitPin))
struct FAoS_GameplayTag : public FGameplayTag
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "GameplayTags.BlueprintGameplayTagLibrary.MakeGameplayTagContainerFromArray", HasNativeBreak = "GameplayTags.BlueprintGameplayTagLibrary.BreakGameplayTagContainer"))
struct FAoS_GameplayTagContainer : public FGameplayTagContainer
{
	GENERATED_BODY()

	void SetParentTag(const FAoS_GameplayTag& InParentTag);
	const FAoS_GameplayTag& GetParentTag() const;
	
private:

	FAoS_GameplayTag ParentTag;
};
