// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SI_CharacterList.generated.h"

class USI_CharacterData;
/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_CharacterList : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Characters")
	TSoftObjectPtr<USI_CharacterData> NickData;

	UPROPERTY(EditAnywhere, Category = "Characters")
	TSoftObjectPtr<USI_CharacterData> GizboData;
	
	UPROPERTY(EditAnywhere, Category = "Characters")
	TArray<TSoftObjectPtr<USI_CharacterData>> MainCharacters;

	UPROPERTY(EditAnywhere, Category = "Characters")
	TArray<TSoftObjectPtr<USI_CharacterData>> SideCharacters;

	UPROPERTY(EditAnywhere, Category = "Characters")
	TArray<TSoftObjectPtr<USI_CharacterData>> TestCharacters;

public:
	
	USI_CharacterData* GetCharacterDataByTag(const FGameplayTag& InCharacterTag);
};
