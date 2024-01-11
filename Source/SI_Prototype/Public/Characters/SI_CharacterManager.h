// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_CharacterTypes.h"
#include "Subsystems/SI_WorldSubsystem.h"
#include "SI_CharacterManager.generated.h"

class ASI_Gizbo;
class ASI_Nick;
class ASI_Character;
class USI_PartData;
class USI_CharacterData;

UCLASS()
class SI_PROTOTYPE_API USI_CharacterManager : public USI_WorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Characters")
	ASI_Nick* GetNick();

	UFUNCTION(BlueprintPure, Category = "Characters")
	ASI_Gizbo* GetGizbo();
	
	// returns nullptr if character's name is not found in the list
	USI_CharacterData* GetActiveCharacterData(const FGameplayTag& CharacterTag);

	USI_CharacterData* GetCharacterDataByTag(const FGameplayTag& InCharacterTag);
	
	FSI_CharacterState* GetCharacterStateByTag(const FGameplayTag& InCharacterTag, const ASI_Character* InCharacter = nullptr);
	void AddNewCharacterState(FSI_CharacterState* InCharacterState);
		
	bool IsActiveCharacter(USI_CharacterData* InCharacterData);

	bool SaveCharacterStates() const;
	bool LoadCharacterStates();

	void SetNickRef(ASI_Nick* InNick);
	void SetGizboRef(ASI_Gizbo* InGizbo);
	
protected:

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	bool CreateCharacterStatesSaveFile();


private:

	UPROPERTY()
	TSoftObjectPtr<ASI_Nick> NickRef;
	UPROPERTY()
	TSoftObjectPtr<ASI_Gizbo> GizboRef;

	TMap<FGameplayTag, FSI_CharacterState> LoadedCharacterStates;

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
