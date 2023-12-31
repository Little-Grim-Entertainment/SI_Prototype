// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SI_CaseDialogueDataAsset.generated.h"

class USI_CaseData;
class USI_PartDialogueDataAsset;


UCLASS()
class SI_PROTOTYPE_API USI_CaseDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USI_CaseData* CaseReference;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	TArray<TSoftObjectPtr<USI_PartDialogueDataAsset>> PartDialogueData;

	FString GetCaseNameNoSpace() const;
};
