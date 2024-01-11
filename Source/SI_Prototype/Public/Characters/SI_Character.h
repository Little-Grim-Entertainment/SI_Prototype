// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_CharacterTypes.h"
#include "GameFramework/Character.h"
#include "SI_Character.generated.h"

class USI_CharacterManager;
class USI_CharacterData;
class USI_AbilitySystemComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASI_Character();

	USI_AbilitySystemComponent* GetAbilitySystemComponent() {return AbilitySystemComponent;}

	USI_CharacterData* GetCharacterData() const;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character | Abilities")
	USI_AbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Info")
	USI_CharacterData* CharacterData = nullptr;


};
