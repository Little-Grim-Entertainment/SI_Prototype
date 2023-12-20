// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGCsvDataTypes.h"
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

	virtual void OnCsvProcessComplete_Implementation(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr) override;

protected:

	UPROPERTY(EditAnywhere, Category = "FileInfo")
	FString FolderPath;
	
	UPROPERTY(EditAnywhere, Category = "FileInfo")
	FString FolderName;

	void OnPayLoadReadyForImport(const FLGCsvInfoImportPayload& InImportPayload);

	virtual void UpdateDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr);
	virtual void InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);

	virtual void* GetDialogueStructArrayByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);

	virtual FName GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag);
	virtual FName GetStructTypeNameByTag(const FGameplayTag& InGameplayTag);
	
	virtual UScriptStruct* GetStructContainerByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	virtual UScriptStruct* GetStructTypeByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID);
	virtual UDataTable* GenerateNewDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo);
	
private:

	UFUNCTION(CallInEditor)
	void UpdateDialogue();
};
