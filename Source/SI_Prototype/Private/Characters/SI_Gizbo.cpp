// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_Gizbo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"


using namespace SI_NativeGameplayTagLibrary;

ASI_Gizbo::ASI_Gizbo()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<USI_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called every frame
void ASI_Gizbo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* ASI_Gizbo::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USI_AbilitySystemComponent* ASI_Gizbo::GetSIAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASI_Gizbo::BeginPlay()
{
	Super::BeginPlay();

	GiveAbilities();
	CurrentBehaviorTag = SITag_Behavior_Following;
}

void ASI_Gizbo::GiveAbilities()
{
	if (!IsValid(AbilitySystemComponent)) {return;}

	for (TSubclassOf<USI_GameplayAbility>& Ability : DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
	}
}