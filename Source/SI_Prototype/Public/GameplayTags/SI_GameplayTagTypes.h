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

USTRUCT(BlueprintType)
struct FSITagPayload 
{
	GENERATED_BODY()

	FSITagPayload() {}
	FSITagPayload(AActor* InCaller, AActor* InTarget);
	
	UPROPERTY()
	TObjectPtr<AActor> Instigator = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> Target = nullptr;

	bool operator == (const FSITagPayload& Other) const;
	bool operator != (const FSITagPayload& Other) const;

	template<typename PayloadType>
	FORCEINLINE PayloadType* GetPayloadByType()
	{
		return static_cast<PayloadType*>(this);
	}
};
