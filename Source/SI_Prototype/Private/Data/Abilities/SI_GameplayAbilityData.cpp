// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Abilities/SI_GameplayAbilityData.h"

USI_GameplayAbility* USI_GameplayAbilityData::GetGameplayAbilityByTag(const FGameplayTag& InGameplayAbilityTag) const
{
	return GameplayAbilitiesMap.Find(InGameplayAbilityTag)->GetDefaultObject();
}
