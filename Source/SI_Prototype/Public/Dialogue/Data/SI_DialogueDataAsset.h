// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_CaseDialogueDataTable.h"
#include "Data/LGDialogueDataAsset.h"
#include "Dialogue/SI_DialogueTypes.h"
#include "SI_DialogueDataAsset.generated.h"

class USI_CsvDataProcessorObject;

UCLASS()
class SI_PROTOTYPE_API USI_DialogueDataAsset : public ULGDialogueDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "FileInfo", meta=(Categories="Character"))
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	FSI_DefaultDialogueInfo DefaultDialogue;

	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	FSI_DefaultBubbleDialogueInfo DefaultBubbleDialogue;
	
	UPROPERTY(EditAnywhere, Category = "Dialogue | DialogueData")
	TArray<FSI_CaseDialogueInfo> CaseDialogue;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue | DialogueTables")
	const UDataTable* DefaultPrimaryDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue | DialogueTables")
	const UDataTable* DefaultCorrectedDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue | DialogueTables")
	const UDataTable* DefaultResponseDialogueDataTable = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Dialogue | DialogueTables")
	const UDataTable* DefaultRandomBubbleDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue | DialogueTables")
	const UDataTable* DefaultSeeNickBubbleDialogueDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Dialogue | DialogueTables")
	USI_CaseDialogueDataTable* CaseDialogueDataTable = nullptr;

	void SetDataTableByTypeAndTag(const UDataTable* InDataTable, const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag);
	void SetEmbeddedDialogueDataTableByTypeTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag, const UDataTable* InDataTable);

	const UDataTable* GetDialogueDataTableByType(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag = FSI_DialogueTag()) const;
	const UDataTable* GetEmbeddedDialogueDataTableByTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const;

	const UDataTable* GetCaseDialogueDataTableByType(const FGameplayTag& InCaseTag, const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag = FSI_DialogueTag()) const;

	template <class DialogueStruct>
	DialogueStruct* GetTableDialogueByTag(const UDataTable* InDataTable, const FSI_DialogueTag& InDialogueTag);
	
	template <class DialogueStructType>
	DialogueStructType* GetDialogueByTypeAndTag(const FSI_DialogueTag& InDialogueTag);
};

template <class DialogueStruct>
DialogueStruct* USI_DialogueDataAsset::GetTableDialogueByTag(const UDataTable* InDataTable, const FSI_DialogueTag& InDialogueTag)
{
	if(!IsValid(InDataTable)) {return nullptr;}
	
	TArray<DialogueStruct*> DialogueStructArray;
	InDataTable->GetAllRows(nullptr, DialogueStructArray);

	for(DialogueStruct* CurrentDialogue : DialogueStructArray)
	{
		if(CurrentDialogue->DialogueTag == InDialogueTag.GetName())
		{
			return CurrentDialogue;
		}
	}

	return nullptr;
}

template <class DialogueStructType>
DialogueStructType* USI_DialogueDataAsset::GetDialogueByTypeAndTag(const FSI_DialogueTag& InDialogueTag)
{
	if(!InDialogueTag.IsValid()) {return nullptr;}
		
	if(InDialogueTag.IsCaseDialogueTag())
	{
		const USI_CaseDialogueDataTable* CaseDataTable = CaseDialogueDataTable;
		if(!IsValid(CaseDataTable)){return nullptr;}
		
		TArray<FSI_CaseDialogueDataTableRow*> CaseDialogueDataTableRows;
		CaseDataTable->GetAllRows(nullptr, CaseDialogueDataTableRows);
		
		for(FSI_CaseDialogueDataTableRow* CurrentDialogueCaseDataTableRow : CaseDialogueDataTableRows)
		{
			if(!CurrentDialogueCaseDataTableRow) {continue;}
						
			FSI_CaseDialogueData& CaseDialogueData = CurrentDialogueCaseDataTableRow->CaseDialogueData;
			if(!InDialogueTag.Contains(CaseDialogueData.DialogueDataID.ToString())) {continue;}
			
			for(FSI_PartDialogueData& CurrentPartDialogueData : CaseDialogueData.PartDialogueData)
			{
				if(!InDialogueTag.Contains(CurrentPartDialogueData.DialogueDataID.ToString())) {continue;}

				const UDataTable* DialogueDataTable = CurrentPartDialogueData.GetDialogueDataTableByType(DialogueStructType::GetGetTypeTag());
				if(!IsValid(DialogueDataTable)) {return nullptr;}

				return GetTableDialogueByTag<DialogueStructType>(DialogueDataTable, InDialogueTag);
			}
		}
		return nullptr;
	}

	const UDataTable* DialogueDataTable = GetDialogueDataTableByType(DialogueStructType::GetGetTypeTag());
	if(!IsValid(DialogueDataTable)) {return nullptr;}

	return GetTableDialogueByTag<DialogueStructType>(DialogueDataTable, InDialogueTag);
};