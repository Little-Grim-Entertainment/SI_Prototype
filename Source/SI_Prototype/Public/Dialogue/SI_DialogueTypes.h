// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGCsvDataTypes.h"
#include "LGDialogueTypes.h"
#include "SI_DialogueTypes.generated.h"

class USI_PartData;
class USI_DialogueDataTable;
class USI_CaseData;
DECLARE_LOG_CATEGORY_EXTERN(LogSI_Dialogue, Log, All);

class ASI_Evidence;

UENUM()
enum ESI_MainDialogueTypes : uint8
{
	MD_NONE				UMETA(DisplayName = "NONE"),
	MD_DefaultDialogue	UMETA(DisplayName = "DefaultDialogue"),
	MD_BubbleDialogue   UMETA(DisplayName = "BubbleDialogue"),
	MD_CaseDialogue		UMETA(DisplayName = "CaseDialogue"),
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PressDialogue : public FLGConversationDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 PressLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	bool CanPresentEvidence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue", meta=(EditCondition="CanPresentEvidence", EditConditionHides))
	TSubclassOf<ASI_Evidence> CorrectEvidence;
};

USTRUCT(BlueprintType)
struct FSI_PressDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_PressDialogueArray();

	UPROPERTY()
	TArray<FSI_PressDialogue> PressDialogueArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USI_DialogueDataTable* PressDialogueDataTable;

	void UpdateDataTableStructValues(TArray<FSI_PressDialogue*>& OutDataTableStructArray);

	TArray<FSI_PressDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_ResponseDialogue : public FLGConversationDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 ResponseLine;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	bool IsEvidenceCorrect;
};

USTRUCT(BlueprintType)
struct FSI_ResponseDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_ResponseDialogueArray();

	UPROPERTY()
	TArray<FSI_ResponseDialogue> ResponseDialogueArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USI_DialogueDataTable* ResponseDialogueDataTable;

	void UpdateDataTableStructValues(TArray<FSI_ResponseDialogue*>& OutDataTableStructArray);

	TArray<FSI_ResponseDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PrimaryDialogue : public FLGConversationDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 Line;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
	FSI_PressDialogueArray PressDialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
	FSI_ResponseDialogueArray ResponseDialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
    bool IsTrueStatement;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
	FString PressURL;
	
	UPROPERTY(VisibleAnywhere, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
	FString ResponseURL;
};

USTRUCT(BlueprintType)
struct FSI_PrimaryDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_PrimaryDialogueArray();

	UPROPERTY()
	TArray<FSI_PrimaryDialogue> PrimaryDialogueArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USI_DialogueDataTable* PrimaryDialogueDataTable;

	void UpdateDataTableStructValues(TArray<FSI_PrimaryDialogue*>& OutDataTableStructArray);
	
	TArray<FSI_PrimaryDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CorrectedDialogue : public FLGConversationDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Dialogue", BlueprintReadOnly)
	int32 CorrectedLine;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue", BlueprintReadOnly)
	int32 SpeakerLine;
};

USTRUCT(BlueprintType)
struct FSI_CorrectedDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_CorrectedDialogueArray();

	UPROPERTY()
	TArray<FSI_CorrectedDialogue> CorrectedDialogueArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USI_DialogueDataTable* CorrectedDialogueDataTable;

	void UpdateDataTableStructValues(TArray<FSI_CorrectedDialogue*>& OutDataTableStructArray);

	TArray<FSI_CorrectedDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultResponse : public FLGConversationDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 ResponseLine;
};

USTRUCT(BlueprintType)
struct FSI_DefaultResponseArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_DefaultResponseArray();

	UPROPERTY(VisibleAnywhere)
	FGuid DialogueID;

	UPROPERTY()
	TArray<FSI_DefaultResponse> DefaultResponseArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USI_DialogueDataTable* DefaultResponseDataTable;

	void UpdateDataTableStructValues(TArray<FSI_DefaultResponse*>& OutDataTableStructArray);

	TArray<FSI_DefaultResponse>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_BubbleDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FString BubbleTest;
};

USTRUCT(BlueprintType)
struct FSI_BubbleDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_BubbleDialogueArray();

	UPROPERTY()
	TArray<FSI_BubbleDialogue> BubbleDialogueArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USI_DialogueDataTable* BubbleDialogueDataTable;

	void UpdateDataTableStructValues(TArray<FSI_BubbleDialogue*>& OutDataTableStructArray);

	TArray<FSI_BubbleDialogue>* GetDialogueArray();
	virtual UScriptStruct* GetStructContainer() override;
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable) override;
	virtual void SetDataTable(UDataTable* InDataTable) override;
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

	UPROPERTY(VisibleAnywhere)
	TArray<FLGDialogueArray> DialogueArrays;

	TArray<FLGDialogueArray*> DialogueArrayPtrs;

	void AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload);
	FLGDialogueArray* GetDialogueArrayByID(const FGuid& InDialogueArrayID);
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PartDialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USI_PartData* PartReference;

	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DialogueURLs;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FSI_DialogueArrayData DialogueData;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CaseDialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USI_CaseData* CaseReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSI_PartDialogueData> PartDialogue;

	FString GetCaseNameNoSpace() const;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultDialogueData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DefaultDialogueURLs;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FSI_DialogueArrayData DefaultDialogueData;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultBubbleDialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "URLs")
	FLGDialogueURL RandomBubbleDialogueURL;

	UPROPERTY(EditAnywhere, Category = "URLs")
	FLGDialogueURL SeeNickBubbleDialogueURL;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FSI_DialogueArrayData BubbleDialogueData;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DialogueState : public FLGDialogueState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	FSI_PrimaryDialogueArray StatePrimaryDialogueArray;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	TSoftObjectPtr<USI_DialogueDataTable> StateDialogueDataTable;
};
