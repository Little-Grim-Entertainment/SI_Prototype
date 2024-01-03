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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 Line;

	//TODO: @Jeff replace with Data Asset references
	/*UPROPERTY()
	FSI_PressDialogueArray PressDialogue;

	UPROPERTY()
	FSI_ResponseDialogueArray ResponseDialogue;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
    bool IsTrueStatement;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
	FString PressURL;
	
	UPROPERTY(VisibleAnywhere, Category = "Dialogue", meta=(DisplayAfter="EmphasizedColorsString"))
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
struct SI_PROTOTYPE_API FSI_DefaultResponse : public FLGConversationDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int32 ResponseLine;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_BubbleDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FString BubbleTest;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PartDialogueData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USI_PartData* PartReference;

	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DialogueURLs;

	FString GetPartNameNoSpace() const;
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
struct SI_PROTOTYPE_API FSI_CaseDialogueDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USI_CaseDialogueDataAsset> CaseDialogueData;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultDialogueData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DefaultDialogueURLs;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultBubbleDialogueData
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

	/*FSI_DialogueState(){}
	FSI_DialogueState(FSI_PrimaryDialogueArray* InPrimaryDialogueArray);

	UPROPERTY(VisibleAnywhere, Category = "Dialogue")
	FSI_PrimaryDialogueArray CasePrimaryDialogueArray;*/
};
