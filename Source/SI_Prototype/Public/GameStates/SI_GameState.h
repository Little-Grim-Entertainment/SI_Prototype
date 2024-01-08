// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Characters/SI_CharacterTypes.h"
#include "SI_GameState.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_GameState : public AGameState
{
	GENERATED_BODY()

public:

	
	FSI_CharacterState* GetCharacterStateByTag(const FGameplayTag& InCharacterTag);
	void AddNewCharacterState(FSI_CharacterState* InCharacterState);

	
protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	TMap<FGameplayTag, FSI_CharacterState> CharacterStates;

	bool CreateCharacterStatesSaveFile() const;
	bool SaveCharacterStates() const;
	bool LoadCharacterStates();
};
