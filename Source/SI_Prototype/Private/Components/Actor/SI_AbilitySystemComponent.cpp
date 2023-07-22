// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor/SI_AbilitySystemComponent.h"

#include "Abilities/SI_GameplayAbility.h"
#include "Data/Abilities/SI_GameplayAbilityData.h"
#include "GameModes/SI_GameMode.h"


// Sets default values for this component's properties
USI_AbilitySystemComponent::USI_AbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USI_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USI_AbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UGameplayAbility* USI_AbilitySystemComponent::GetGameplayAbilityFromTag(const FGameplayTag InGameplayAbilityTag) const
{
	return GameplayAbilityData->GetGameplayAbilityByTag(InGameplayAbilityTag);
}