// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/SI_AbilitySystemComponent.h"

#include "SI_Types.h"
#include "Abilities/SI_GameplayAbility.h"

// Sets default values for this component's properties
USI_AbilitySystemComponent::USI_AbilitySystemComponent()
{
}

// Called when the game starts
void USI_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USI_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	CurrentSIAbility = FSIGameplayAbilities(Cast<USI_GameplayAbility>(AbilitySpec.Ability), AbilitySpec.Ability->AbilityTags, AbilitySpec.Handle);

	SIAbilitiesArray.AddUnique(FSIGameplayAbilities(CurrentSIAbility));
}

FGameplayAbilitySpecHandle* USI_AbilitySystemComponent::GetGameplayAbilitySpecByTag(FGameplayTag InAbilityTag)
{
	if(SIAbilitiesArray.IsEmpty()) return nullptr;
	
	for(FSIGameplayAbilities& TempSIAbility : SIAbilitiesArray)
	{
		if(TempSIAbility.SIAbilityTagContainer.HasTag(InAbilityTag))
		{
			return &TempSIAbility.SIAbilitySpecHandle;
		}
	}
	return nullptr;
}

USI_GameplayAbility* USI_AbilitySystemComponent::GetGameplayAbilityByTag(FGameplayTag InAbilityTag)
{
	if(SIAbilitiesArray.IsEmpty()) return nullptr;
	
	for(FSIGameplayAbilities& TempSIAbility : SIAbilitiesArray)
	{
		if(TempSIAbility.SIAbilityTagContainer.HasTag(InAbilityTag))
		{
			return Cast<USI_GameplayAbility>(TempSIAbility.SIAbility);
		}
	}
	return nullptr;
}
