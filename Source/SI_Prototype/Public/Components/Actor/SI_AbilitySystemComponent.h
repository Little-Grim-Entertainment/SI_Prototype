// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SI_AbilitySystemComponent.generated.h"

class USI_GameplayAbilityData;
class USI_GameplayAbility;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SI_PROTOTYPE_API USI_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USI_AbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USI_GameplayAbilityData* GameplayAbilityData;	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UGameplayAbility* GetGameplayAbilityFromTag(const FGameplayTag InGameplayAbilityTag) const;
};
