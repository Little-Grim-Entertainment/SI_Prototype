// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_GizboManager.generated.h"

class USI_AbilitySystemComponent;
class USI_GameplayAbility;
class ASI_Nick;
class ASI_Gizbo;
class ASI_GizboController;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_GizboManager : public USI_GameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Gizbo")
	void SpawnGizbo();
	UFUNCTION()
	void SetGizboStartTag(FString InStartTag);
	UFUNCTION(BlueprintPure, Category = "Gizbo")
	ASI_Gizbo* GetGizbo();
	UFUNCTION(BlueprintCallable, Category = "Gizbo")
	void ShowGizbo(bool bShouldHide);
	UFUNCTION(BlueprintPure, Category = "Gizbo")
	ASI_GizboController* GetGizboController();
	
	UPROPERTY()
	ASI_Nick* Nick;
	
protected:

	virtual void OnGameModeBeginPlay() override;
	
	virtual void InitializeDelegates() override;
	void InitializeDelegateMaps();
	
	// Listens for broadcast of GameplayTag being added to the TagManager and applies logic
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	// Listens for broadcast of GameplayTag being added to the TagManager and applies logic
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag) override;
	// Tries to activate an ability based on the CurrentAbilityTag
	void TryActivateAbilityByTag();
	// Tries to cancel an ability based on the CurrentAbilityTag
	void TryCancelAbilityByTag();

	UPROPERTY()
	USI_AbilitySystemComponent* GizboAbilitySystemComponent;

private:

	UPROPERTY()
	ASI_GizboController* GizboController;
	UPROPERTY()
	ASI_Gizbo* GizboCharacter;

	FString GizboStartTag;

	//Current Ability Tag that is updated when an AbilityTag is received from GameplayTagManager
	FGameplayTag CurrentAbilityTag;
	
	TMap<FGameplayTag, FSimpleDelegate> GizboDelegateContainer;
	TMap<FGameplayTag, USI_GameplayAbility*> ActiveAbilitiesContainer;

	FSimpleDelegate ActivateAbilityDelegate;

};
