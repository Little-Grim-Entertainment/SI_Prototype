// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGDialogueTypes.h"
#include "SI_DialogueTypes.generated.h"

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PressDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PressLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText SpeakerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Dialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanPresentEvidence;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_ResponseDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PressLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText SpeakerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Dialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanPresentEvidence;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PrimaryDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Line;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText SpeakerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Dialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString PressURL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FSI_PressDialogue> PressDialogueArray;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString ResponseURL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FSI_ResponseDialogue> ResponseDialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsTrueStatement;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CorrectedDialogue : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CorrectedLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 SpeakerLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText SpeakerName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Dialogue;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultResponse : public FLGDialogue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CorrectedLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 SpeakerLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText SpeakerName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Dialogue;	
};

USTRUCT(BlueprintType)
struct FSI_DialogueArrays
{
	GENERATED_BODY()

	FSI_DialogueArrays();

	UPROPERTY(VisibleAnywhere)
	FString DialogueLabel;

	UPROPERTY(VisibleAnywhere)
	FGuid DialogueDataID;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FSI_PrimaryDialogue> PrimaryDialogueArray;

	UPROPERTY(VisibleAnywhere)
	TArray<FSI_CorrectedDialogue> CorrectedDialogueArray;

	UPROPERTY(VisibleAnywhere)
	TArray<FSI_DefaultResponse> DefaultResponseArray;

	FLGDialogue* GetDialogueByID(const FGuid& InDialogueID);
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PartDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PartNumber;

	UPROPERTY(EditAnywhere, Category = "URLs")
	TArray<FLGDialogueURL> DialogueURLs;

	UPROPERTY(VisibleAnywhere, Category = "DialogueData")
	FSI_DialogueArrays DialogueData;
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