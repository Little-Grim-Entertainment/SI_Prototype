// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_CharacterTypes.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_CharacterManager.generated.h"

class ASI_Character;
class USI_PartData;
class USI_CharacterData;

UCLASS()
class SI_PROTOTYPE_API USI_CharacterManager : public USI_WorldSubsystem
{
	GENERATED_BODY()

public:

	// returns nullptr if character's name is not found in the list
	USI_CharacterData* GetActiveCharacterData(const FGameplayTag& CharacterTag);

	USI_CharacterData* GetCharacterDataByTag(const FGameplayTag& InCharacterTag);
	FSI_CharacterState* GetCharacterStateByTag(const FGameplayTag& InCharacterTag);


	bool IsActiveCharacter(USI_CharacterData* InCharacterData);
	TSubclassOf<ASI_Character> GetCharacterClassByTag(const FGameplayTag& InCharacterTag);
	
protected:

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private: 

	// Assumption: this is always kept up to date by calling functions in this class to update it
	// We will create a binding with an event in the case manager
	TArray<USI_CharacterData*> ActiveCharactersData;
	
	// Called when a new part of a case is activated in order to update ActiveCharactersData
	UFUNCTION()
	void OnPartActivated(USI_PartData* ActivatedPart);
	
	// Called when a part is completed to update ActiveCharactersData
	UFUNCTION()
	void OnPartCompleted(USI_PartData* CompletedPart);
};
