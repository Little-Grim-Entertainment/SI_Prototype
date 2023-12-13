// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LGDialogueTypes.h"
#include "Interfaces/LGCsvProcessorInterface.h"
#include "LGDialogueDataAsset.generated.h"


struct FRuntimeDataTableCallbackInfo;

UCLASS()
class LGDIALOGUESYSTEM_API ULGDialogueDataAsset : public UDataAsset, public ILGCsvProcessorInterface
{
	GENERATED_BODY()

public:
	
	virtual void UpdateDialogue_Internal();

	UFUNCTION()
	virtual void OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo);

protected:

	UPROPERTY(EditAnywhere, Category = "FileInfo")
	FString FolderPath;
	
	UPROPERTY(EditAnywhere, Category = "FileInfo")
	FString FolderName;

	void OnPayLoadReadyForImport(const FLGCsvInfoImportPayload& InImportPayload);
	
	virtual void OnCsvProcessComplete_Implementation(const FLGCsvInfo& InCvsInfo) override;

	virtual UStruct* GetUStructContainerByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueStructID);
	virtual void* GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueID);
	virtual FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag);
	virtual FName GetStructTypeNameByTag(const FGameplayTag& InGameplayTag);

	
private:

	UFUNCTION(CallInEditor)
	void UpdateDialogue();
};
