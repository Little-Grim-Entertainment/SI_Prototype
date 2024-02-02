// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGDialogueTypes.h"
#include "SI_DialogueTypes.generated.h"

class USI_CaseDialogueDataAsset;
class USI_PartData;
class USI_DialogueDataTable;
class USI_CaseData;
DECLARE_LOG_CATEGORY_EXTERN(LogSI_Dialogue, Log, All);

class ASI_Evidence;

UENUM()
enum ESI_InterrogationState : uint8
{
	IS_NONE				UMETA(DisplayName = "NONE"),
	IS_Conversation		UMETA(DisplayName = "Conversation"),
	IS_Pressing			UMETA(DisplayName = "Pressing"),
	IS_Presenting		UMETA(DisplayName = "Presenting"),
	IS_Responding		UMETA(DisplayName = "Responding"),
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DialogueTagSectionName
{
	GENERATED_BODY()

	FSI_DialogueTagSectionName() {}
	FSI_DialogueTagSectionName(const FName& InSectionName);
	
	const FName& GetSectionName() const {return SectionName;}

	FString ToString() const;
	bool IsValid() const;

	bool operator==(const FSI_DialogueTagSectionName& OtherSectionName) const;
	bool operator!=(const FSI_DialogueTagSectionName& OtherSectionName) const;
	
protected:
	
	FName SectionName = FName();
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DialogueTag
{
	GENERATED_BODY()

	FSI_DialogueTag();
	FSI_DialogueTag(const FName& InFNameTag);

	void AppendNewSection(const FName& InSectionName);
	int32 SectionNum() const;
	bool IsValid() const;
	bool IsCaseDialogueTag() const;
	bool ContainsSectionName(const FString& InSectionName) const;
	bool Contains(const FString& InStringValue) const;
	
	FString ToString() const;
	FName GetName() const;
	
	const TArray<FSI_DialogueTagSectionName>& GetDialogueTagArray() const;

	FSI_DialogueTag GetParentTagBySectionIndex(const int32 InSectionIndex) const;
	FName GetSectionNameByIndex(const int32 InSectionIndex) const;
	
	bool operator==(const FSI_DialogueTag& OtherTag) const;
	bool operator!=(const FSI_DialogueTag& OtherTag) const;

private:

	void ConvertFNameToDialogueArray(const FName& InFNameTag);
	void GenerateDialogueTag();

	TArray<FSI_DialogueTagSectionName> DialogueTagArray;
	FName GeneratedDialogueTag = FName();
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
struct SI_PROTOTYPE_API FSI_ResponseDialogue : public FLGConversationDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 ResponseLine;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	bool IsEvidenceCorrect;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PrimaryDialogue : public FLGConversationDialogue
{
	GENERATED_BODY()
	
	FSI_PrimaryDialogue(){}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 Line = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
    bool IsTrueStatement = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	const UDataTable* PressDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	const UDataTable* ResponseDialogueDataTable = nullptr;

	UPROPERTY(meta=(DisplayAfter="EmphasizedColorsString"))
	FString PressURL;

	UPROPERTY(meta=(DisplayAfter="EmphasizedColorsString"))
	FString ResponseURL;
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
struct SI_PROTOTYPE_API FSI_DefaultResponse : public FSI_ResponseDialogue
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_BubbleDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FString BubbleTest;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PartDialogueInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const USI_PartData* PartReference;

	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DialogueURLs;

	FString GetPartNameNoSpace() const;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PartDialogueData : public FLGDialogueData
{
	GENERATED_BODY()

	FSI_PartDialogueData(){}
	FSI_PartDialogueData(const USI_PartData* InPartData);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	const USI_PartData* PartReference = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "DialogueTables")
	const UDataTable* RandomBubbleDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "DialogueTables")
	const UDataTable* SeeNickBubbleDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "DialogueTables")
	const UDataTable* DefaultResponseDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "DialogueTables")
	const UDataTable* CorrectedDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "DialogueTables")
	const UDataTable* PrimaryDialogueDataTable = nullptr;

	const UDataTable* GetDialogueDataTableByType(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag = FSI_DialogueTag()) const;
	void SetDialogueDataTableByType(const UDataTable* InDataTable, const FGameplayTag& InStructType, const  FSI_DialogueTag& InDialogueTag = FSI_DialogueTag());

	const UDataTable* GetEmbeddedDialogueDataTableByTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const;
	void SetEmbeddedDialogueDataTableByTypeTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag, const UDataTable* InDataTable);
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CaseDialogueInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const USI_CaseData* CaseReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSI_PartDialogueInfo> PartDialogue;

	FString GetCaseNameNoSpace() const;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CaseDialogueData : public FLGDialogueData
{
	GENERATED_BODY()

	FSI_CaseDialogueData(){}
	FSI_CaseDialogueData(const USI_CaseData* InCaseReference);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	const USI_CaseData* CaseReference;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
	TArray<FSI_PartDialogueData> PartDialogueData;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CaseDialogueDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	FSI_CaseDialogueDataTableRow(){}
	FSI_CaseDialogueDataTableRow(const FSI_CaseDialogueData& InCaseDialogueData);
	FSI_CaseDialogueDataTableRow(const USI_CaseData* InCaseData);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FSI_CaseDialogueData CaseDialogueData;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultDialogueInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DefaultDialogueURLs;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultBubbleDialogueInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "URLs")
	FLGDialogueURL RandomBubbleDialogueURL;

	UPROPERTY(EditAnywhere, Category = "URLs")
	FLGDialogueURL SeeNickBubbleDialogueURL;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DialogueState : public FLGDialogueState
{
	GENERATED_BODY()

	FSI_DialogueState(){}
	FSI_DialogueState(const UDataTable* InActivePartDialogueTable, const UDataTable* InActiveCorrectedDialogueTable, const UDataTable* InActiveDefaultResponseTable);
	
	UPROPERTY()
	const UDataTable* ActivePrimaryDialogueTable  = nullptr;
	UPROPERTY()
	const UDataTable* ActiveCorrectedDialogueTable  = nullptr;
	UPROPERTY()
	const UDataTable* ActiveDefaultResponseTable  = nullptr;
	
	UPROPERTY()
	TArray<FSI_PrimaryDialogue> CurrentPrimaryDialogueArray;
	UPROPERTY()
	TArray<FSI_CorrectedDialogue> CurrentCorrectedDialogueArray;
	UPROPERTY()
	TArray<FSI_DefaultResponse> CurrentDefaultResponseArray;
};
