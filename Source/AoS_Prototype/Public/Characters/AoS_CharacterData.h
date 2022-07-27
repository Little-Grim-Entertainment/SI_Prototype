// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AoS_Character.h"
#include "Engine/DataAsset.h"
#include "AoS_CharacterData.generated.h"


UCLASS(BlueprintType)
class AOS_PROTOTYPE_API UAoS_CharacterData : public UDataAsset
{
	GENERATED_BODY()

public:

	UAoS_CharacterData();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	FText CharacterName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	TSubclassOf<AAoS_Character> CharacterClass;

private:



};
