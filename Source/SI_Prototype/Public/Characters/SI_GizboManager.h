// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/SI_GameInstanceSubsystem.h"
#include "SI_GizboManager.generated.h"

class USI_AbilitySystemComponent;
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
	virtual void OnGameplayTagAdded(const FGameplayTag& InAddedTag) override;
	virtual void OnGameplayTagRemoved(const FGameplayTag& InRemovedTag) override;
	
	UPROPERTY()
	USI_AbilitySystemComponent* GizboAbilitySystemComponent;

private:

	UPROPERTY()
	ASI_GizboController* GizboController;
	UPROPERTY()
	ASI_Gizbo* GizboCharacter;

	FString GizboStartTag;
};
