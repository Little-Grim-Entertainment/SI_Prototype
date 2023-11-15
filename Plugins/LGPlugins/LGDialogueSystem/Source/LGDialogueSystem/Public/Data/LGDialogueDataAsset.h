// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LGDialogueTypes.h"
#include "Interfaces/LGCsvProcessorInterface.h"
#include "LGDialogueDataAsset.generated.h"



UCLASS()
class LGDIALOGUESYSTEM_API ULGDialogueDataAsset : public UDataAsset, public ILGCsvProcessorInterface
{
	GENERATED_BODY()

public:
	
	void UpdateDialogue_Internal();

	virtual void OnInteractComplete_Implementation(UObject* Caller, const FLGCsvInfo& InCvsInfo) override;

private:

	UFUNCTION(CallInEditor)
	void UpdateDialogue();

	UPROPERTY(EditAnywhere)
	FString FolderPath;
	
	UPROPERTY(EditAnywhere)
	FString CsvName;

	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DialogueURLs;
};
