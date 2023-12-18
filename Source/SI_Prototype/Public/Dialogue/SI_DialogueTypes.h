// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGDialogueTypes.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
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
struct FSI_PressDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_PressDialogueArray();

	UPROPERTY()
	TArray<FSI_PressDialogue> PressDialogueArray;

	TArray<FSI_PressDialogue>* GetDialogueArray();
	virtual FArrayProperty* GetArrayProperty() override;
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
struct FSI_ResponseDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_ResponseDialogueArray();

	UPROPERTY()
	TArray<FSI_ResponseDialogue> ResponseDialogueArray;

	TArray<FSI_ResponseDialogue>* GetDialogueArray();
	virtual FArrayProperty* GetArrayProperty() override;
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
	FSI_PressDialogueArray PressDialogue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
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
	
	TArray<FSI_PrimaryDialogue>* GetDialogueArray();
	virtual FArrayProperty* GetArrayProperty() override;
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
struct FSI_CorrectedDialogueArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_CorrectedDialogueArray();

	UPROPERTY()
	TArray<FSI_CorrectedDialogue> CorrectedDialogueArray;

	TArray<FSI_CorrectedDialogue>* GetDialogueArray();
	virtual FArrayProperty* GetArrayProperty() override;
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
struct FSI_DefaultResponseArray : public FLGDialogueArray
{
	GENERATED_BODY()

	FSI_DefaultResponseArray();

	UPROPERTY()
	TArray<FSI_DefaultResponse> DefaultResponseArray;

	TArray<FSI_DefaultResponse>* GetDialogueArray();
	virtual FArrayProperty* GetArrayProperty() override;
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

	TArray<FLGDialogueArray*> DialogueArrays;

	void AddNewArrayByTag(const FGameplayTag& InStructTypeTag);
	void RemoveArrayByTag(const FGameplayTag& InStructTypeTag);
	bool ContainsArrayByTypeTag(const FGameplayTag& InStructTypeTag) const;
	FLGDialogueArray* GetDialogueArrayByTag(const FGameplayTag& InStructTypeTag);
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
