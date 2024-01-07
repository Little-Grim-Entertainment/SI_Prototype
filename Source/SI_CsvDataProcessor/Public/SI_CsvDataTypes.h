// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGCsvDataTypes.h"
#include "GameplayTagContainer.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_CsvDataTypes.generated.h"

USTRUCT()
struct SI_CSVDATAPROCESSOR_API FSI_DialogueArrayData : public FLGDialogueArrayData
{
	GENERATED_BODY()

	virtual void AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload, const FName& InDialogueTag) override;
	virtual FLGDialogueArray* GetDialogueArrayByID(const FGuid& InDialogueArrayID) override;

	FName ConvertFileNameToEmbeddedTag(const FGameplayTag& InCaseTag, const FString& InFileName);
};

USTRUCT()
struct SI_CSVDATAPROCESSOR_API FSI_PrimaryDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_PrimaryDialogueArray();
	FSI_PrimaryDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType);
	

	UPROPERTY()
	TArray<FSI_PrimaryDialogue> PrimaryDialogueArray;

	UPROPERTY()
	UDataTable* PrimaryDialogueDataTable = nullptr;

	void UpdateDataTableStructValues(TArray<FSI_PrimaryDialogue*>& OutDataTableStructArray);
	void SetEmbeddedDialogueTableByTag(const UDataTable* InDataTable, const FGameplayTag& InStructType);
	
	TArray<FSI_PrimaryDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual UDataTable* GetDialogueDataTable() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
	virtual void InitializeContainedDialogueTags() override;
};

USTRUCT()
struct SI_CSVDATAPROCESSOR_API FSI_CorrectedDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_CorrectedDialogueArray();
	FSI_CorrectedDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType);

	UPROPERTY()
	TArray<FSI_CorrectedDialogue> CorrectedDialogueArray;

	UPROPERTY()
	UDataTable* CorrectedDialogueDataTable = nullptr;

	void UpdateDataTableStructValues(TArray<FSI_CorrectedDialogue*>& OutDataTableStructArray);

	TArray<FSI_CorrectedDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual UDataTable* GetDialogueDataTable() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
	virtual void InitializeContainedDialogueTags() override;
};

USTRUCT()
struct SI_CSVDATAPROCESSOR_API FSI_DefaultResponseArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_DefaultResponseArray();
	FSI_DefaultResponseArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType);

	UPROPERTY(VisibleAnywhere)
	FGuid DialogueID;

	UPROPERTY()
	TArray<FSI_DefaultResponse> DefaultResponseArray;

	UPROPERTY()
	UDataTable* DefaultResponseDataTable = nullptr;

	void UpdateDataTableStructValues(TArray<FSI_DefaultResponse*>& OutDataTableStructArray);

	TArray<FSI_DefaultResponse>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual UDataTable* GetDialogueDataTable() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
	virtual void InitializeContainedDialogueTags() override;
};

USTRUCT()
struct SI_CSVDATAPROCESSOR_API FSI_BubbleDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_BubbleDialogueArray();
	FSI_BubbleDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType);

	UPROPERTY()
	TArray<FSI_BubbleDialogue> BubbleDialogueArray;

	UPROPERTY()
	UDataTable* BubbleDialogueDataTable = nullptr;

	void UpdateDataTableStructValues(TArray<FSI_BubbleDialogue*>& OutDataTableStructArray);

	TArray<FSI_BubbleDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual UDataTable* GetDialogueDataTable() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
	virtual void InitializeContainedDialogueTags() override;
};

USTRUCT()
struct SI_CSVDATAPROCESSOR_API FSI_PressDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_PressDialogueArray();
	FSI_PressDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType);

	UPROPERTY()
	TArray<FSI_PressDialogue> PressDialogueArray;

	UPROPERTY()
	UDataTable* PressDialogueDataTable = nullptr;

	void UpdateDataTableStructValues(TArray<FSI_PressDialogue*>& OutDataTableStructArray);

	TArray<FSI_PressDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual UDataTable* GetDialogueDataTable() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
	virtual void InitializeContainedDialogueTags() override;
};

USTRUCT()
struct SI_CSVDATAPROCESSOR_API FSI_ResponseDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_ResponseDialogueArray();
	FSI_ResponseDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType);

	UPROPERTY()
	TArray<FSI_ResponseDialogue> ResponseDialogueArray;

	UPROPERTY()
	UDataTable* ResponseDialogueDataTable = nullptr;

	void UpdateDataTableStructValues(TArray<FSI_ResponseDialogue*>& OutDataTableStructArray);

	TArray<FSI_ResponseDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual UDataTable* GetDialogueDataTable() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
	virtual void InitializeContainedDialogueTags() override;
};


