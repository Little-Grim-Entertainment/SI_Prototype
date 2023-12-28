// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_Character.h"
#include "Engine/DataAsset.h"
#include "SI_CharacterData.generated.h"

class ULGDialogueDataAsset;
class UDialogueSession;
class UDialogueSessionNode;
class USI_CaseData;
class USI_PartData;
class USI_CaseManager;


UCLASS(BlueprintType)
class SI_PROTOTYPE_API USI_CharacterData : public UDataAsset
{
	GENERATED_BODY()

public:

	USI_CharacterData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	FGameplayTag CharacterTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	TSubclassOf<ASI_Character> CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	TSoftObjectPtr<ULGDialogueDataAsset> CharacterDialogue;
};