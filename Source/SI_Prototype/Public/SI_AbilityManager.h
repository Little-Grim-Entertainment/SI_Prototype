// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_LocalPlayerSubsystem.h"
#include "SI_AbilityManager.generated.h"

class USI_AbilitySystemComponent;
class USI_GizboManager;
class USI_PlayerManager;

DECLARE_LOG_CATEGORY_EXTERN(LogSI_AbilityManager, Log, All);

/**
 * 
 */

UCLASS()
class SI_PROTOTYPE_API USI_AbilityManager : public USI_LocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	
protected:

	void TryActivateAbilityByTag(const FGameplayTag& InAddedTag);
	void TryCancelAbilityByTag(const FGameplayTag& InAddedTag);
	void AddRemoveLooseAbilityTags(const FGameplayTag& InAddedTag);
	void GetAbilitySystemComponents();

	UPROPERTY()
	USI_AbilitySystemComponent* GizboAbilitySystemComponent;
	UPROPERTY()
	USI_AbilitySystemComponent* NickAbilitySystemComponent;
	
	
};
