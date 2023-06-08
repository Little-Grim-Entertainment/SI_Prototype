﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SI_AbilitySystemComponent.generated.h"


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
	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	USI_GameplayAbility* GetGameplayAbilityFromTag(FGameplayTag InAbilityTag);


};
