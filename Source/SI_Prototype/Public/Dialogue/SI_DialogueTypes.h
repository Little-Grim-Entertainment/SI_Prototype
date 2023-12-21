// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGCsvDataTypes.h"
#include "LGDialogueTypes.h"
#include "SI_DialogueTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSI_Dialogue, Log, All);

class ASI_Evidence;

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PressDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PressLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanPresentEvidence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition="CanPresentEvidence", EditConditionHides))
	TSubclassOf<ASI_Evidence> CorrectEvidence;
};

USTRUCT(BlueprintType)
struct FSI_PressDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_PressDialogueArray();

	UPROPERTY()
	TArray<FSI_PressDialogue> PressDialogueArray;

	void UpdateDataTableStructValues(TArray<FSI_PressDialogue*>& OutDataTableStructArray);

	TArray<FSI_PressDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_ResponseDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ResponseLine;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsEvidenceCorrect;
};

USTRUCT(BlueprintType)
struct FSI_ResponseDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_ResponseDialogueArray();

	UPROPERTY()
	TArray<FSI_ResponseDialogue> ResponseDialogueArray;

	void UpdateDataTableStructValues(TArray<FSI_ResponseDialogue*>& OutDataTableStructArray);

	TArray<FSI_ResponseDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PrimaryDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Line;

	UPROPERTY(VisibleAnywhere)
	FString PressURL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FSI_PressDialogueArray PressDialogue;
	
	UPROPERTY(VisibleAnywhere)
	FString ResponseURL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FSI_ResponseDialogueArray ResponseDialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsTrueStatement;
};

USTRUCT(BlueprintType)
struct FSI_PrimaryDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_PrimaryDialogueArray();

	UPROPERTY()
	TArray<FSI_PrimaryDialogue> PrimaryDialogueArray;

	void UpdateDataTableStructValues(TArray<FSI_PrimaryDialogue*>& OutDataTableStructArray);
	
	TArray<FSI_PrimaryDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CorrectedDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CorrectedLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 SpeakerLine;
};

USTRUCT(BlueprintType)
struct FSI_CorrectedDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_CorrectedDialogueArray();

	UPROPERTY()
	TArray<FSI_CorrectedDialogue> CorrectedDialogueArray;

	void UpdateDataTableStructValues(TArray<FSI_CorrectedDialogue*>& OutDataTableStructArray);

	TArray<FSI_CorrectedDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultResponse : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ResponseLine;
};

USTRUCT(BlueprintType)
struct FSI_DefaultResponseArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_DefaultResponseArray();

	UPROPERTY()
	TArray<FSI_DefaultResponse> DefaultResponseArray;

	void UpdateDataTableStructValues(TArray<FSI_DefaultResponse*>& OutDataTableStructArray);

	TArray<FSI_DefaultResponse>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct FSI_DialogueArrayData
{
	GENERATED_BODY()

	FSI_DialogueArrayData();

	UPROPERTY(VisibleAnywhere)
	FGuid DialogueDataID;

	UPROPERTY(VisibleAnywhere)
	FString DialogueLabel;

	UPROPERTY(EditAnywhere)
	TArray<FLGDialogueArray> DialogueArrays;

	TArray<FLGDialogueArray*> DialogueArrayPtrs;

	void AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload);
	FLGDialogueArray* GetDialogueArrayByID(const FGuid& InDialogueArrayID);
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PartDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PartNumber;

	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DialogueURLs;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FSI_DialogueArrayData DialogueData;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CaseDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CaseNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSI_PartDialogue> PartDialogue;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "URLs")
	FLGDialogueURL DefaultDialogueURL;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_BubbleDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "URLs")
	FLGDialogueURL RandomBubbleDialogueURL;

	UPROPERTY(EditAnywhere, Category = "URLs")
	FLGDialogueURL SeeNickBubbleDialogueURL;
};
