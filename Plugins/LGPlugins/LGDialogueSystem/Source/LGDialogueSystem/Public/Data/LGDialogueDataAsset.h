// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LGDialogueTypes.h"
#include "LGDialogueDataAsset.generated.h"



UCLASS()
class LGDIALOGUESYSTEM_API ULGDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UFUNCTION(CallInEditor)
	void UpdateDialogue();

private:

	UPROPERTY(EditAnywhere)
	FString FolderPath;
	
	UPROPERTY(EditAnywhere)
	FString CsvName;

	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DialogueURLs;
};
