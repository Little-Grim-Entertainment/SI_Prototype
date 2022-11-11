// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "Engine/DataAsset.h"
#include "AoS_CharacterData.generated.h"

class UDlgDialogue;
class UAoS_Case;
class UAoS_Part;

struct FAoS_DialogueData
{
	UAoS_Case* Case;
	UAoS_Part* Part;
	int32 Subpart;
	int32 AngerLevel;
	UDlgDialogue* RelevantDialogue;
};


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
	bool IsCharacterActive;

	FAoS_DialogueData CurrentDialogueData;

private:



};
