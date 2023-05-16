// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_Character.h"
#include "Engine/DataAsset.h"
#include "SI_CharacterData.generated.h"

class UDialogueSession;
class UDialogueSessionNode;
class USI_CaseData;
class USI_PartData;
class USI_CaseManager;

USTRUCT(BlueprintType)
struct FSI_DialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bIsDefaultDialogue = true;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bIsDefaultDialogue", EditConditionHides))
	USI_CaseData* Case = nullptr;
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bIsDefaultDialogue", EditConditionHides))
	USI_PartData* Part = nullptr;
	UPROPERTY(EditAnywhere)
	UDialogueSession* RelevantDialogue = nullptr;

	// --- Saved info --- //
	UPROPERTY(EditAnywhere)
	int32 AngerLevel = 0;
	UDialogueSessionNode* SavedNode = nullptr;
};


UCLASS(BlueprintType)
class SI_PROTOTYPE_API USI_CharacterData : public UDataAsset
{
	GENERATED_BODY()

public:

	USI_CharacterData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	FText CharacterName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterDetails")
	TSubclassOf<ASI_Character> CharacterClass;
	bool IsCharacterActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueData")
	FSI_DialogueData DefaultDialogueData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueData")
	TArray<FSI_DialogueData> CaseDialogueData;
	UFUNCTION(BlueprintPure, Category = "DialogueData")
	FSI_DialogueData& GetCurrentDialogueData(USI_CaseManager* CaseManager);

private:



};