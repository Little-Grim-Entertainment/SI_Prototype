// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_Types.h"
#include "Abilities/SI_GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "SI_GameplayAbilityData.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GameplayAbilityData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	USI_GameplayAbility* GetGameplayAbilityByTag(const FGameplayTag& InGameplayAbilityTag) const;

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (Categories = "Ability", AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TSubclassOf<USI_GameplayAbility>> GameplayAbilitiesMap;	
};
