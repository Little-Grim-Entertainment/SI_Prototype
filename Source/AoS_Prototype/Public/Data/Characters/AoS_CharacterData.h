// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AoS_Character.h"
#include "Engine/DataAsset.h"
#include "AoS_CharacterData.generated.h"

class UDialogueSession;
class UDialogueSessionNode;
class UAoS_CaseData;
class UAoS_PartData;
class UAoS_CaseManager;

USTRUCT(BlueprintType)
struct FAoS_DialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bIsDefaultDialogue = true;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bIsDefaultDialogue", EditConditionHides))
	UAoS_CaseData* Case = nullptr;
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bIsDefaultDialogue", EditConditionHides))
	UAoS_PartData* Part = nullptr;
	UPROPERTY(EditAnywhere)
	UDialogueSession* RelevantDialogue = nullptr;

	// --- Saved info --- //
	UPROPERTY(EditAnywhere)
	int32 AngerLevel = 0;
	UDialogueSessionNode* SavedNode = nullptr;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueData")
	FAoS_DialogueData DefaultDialogueData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueData")
	TArray<FAoS_DialogueData> CaseDialogueData;
	UFUNCTION(BlueprintPure, Category = "DialogueData")
	FAoS_DialogueData& GetCurrentDialogueData(UAoS_CaseManager* CaseManager);

private:



};