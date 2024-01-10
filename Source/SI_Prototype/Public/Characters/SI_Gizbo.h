// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Characters/SI_NPC_Interactable.h"
#include "Abilities/SI_GameplayAbility.h"
#include "SI_Gizbo.generated.h"

class ASI_GizboController;
class USI_AbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_Gizbo : public ASI_NPC_Interactable , public IAbilitySystemInterface 
{
	GENERATED_BODY()
	
public:
	ASI_Gizbo();
	USI_AbilitySystemComponent* GetSIAbilitySystemComponent() const;
	
protected:
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USI_GameplayAbility>> DefaultAbilities;
	
private:
		
	void GiveAbilities();
};
