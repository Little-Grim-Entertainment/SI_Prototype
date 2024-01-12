// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_DialogueDataAsset.h"

#include "Cases/Data/SI_CaseData.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"

void USI_DialogueDataAsset::SetDataTableByTypeAndTag(const UDataTable* InDataTable, const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag)
{
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		DefaultPrimaryDialogueDataTable = InDataTable;
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		DefaultCorrectedDialogueDataTable = InDataTable;
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		DefaultResponseDialogueDataTable = InDataTable;
		return;
	}	
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		if(InDialogueTag.ContainsSectionName("RandomBubbleDialogue"))
		{
			DefaultRandomBubbleDialogueDataTable = InDataTable;
			return;
		}
		if(InDialogueTag.ContainsSectionName("SeeNickBubbleDialogue"))
		{
			DefaultSeeNickBubbleDialogueDataTable = InDataTable;
		}
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		if(!InDialogueTag.IsValid()){return;}
		SetEmbeddedDialogueDataTableByTypeTag(InStructType, InDialogueTag, InDataTable);
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		if(!InDialogueTag.IsValid()){return;}
		SetEmbeddedDialogueDataTableByTypeTag(InStructType, InDialogueTag, InDataTable);
	}
}

void USI_DialogueDataAsset::SetEmbeddedDialogueDataTableByTypeTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag, const UDataTable* InDataTable)
{
	if(!InDialogueTag.IsValid()){return;}

	TArray<FSI_PrimaryDialogue*> PrimaryDialogueArray;
	DefaultPrimaryDialogueDataTable->GetAllRows(nullptr, PrimaryDialogueArray);
	for(FSI_PrimaryDialogue* CurrentPrimaryDialogue : PrimaryDialogueArray)
	{
		if(CurrentPrimaryDialogue->DialogueTag == InDialogueTag.GetName())
		{
			if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
			{
				CurrentPrimaryDialogue->PressDialogueDataTable = InDataTable;
				return;
			}
			if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
			{
				CurrentPrimaryDialogue->ResponseDialogueDataTable = InDataTable;
				return;
			}
		}
	}
}

const UDataTable* USI_DialogueDataAsset::GetDialogueDataTableByType(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
{
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		if(InDialogueTag.ContainsSectionName("RandomBubbleDialogue"))
		{
			return DefaultRandomBubbleDialogueDataTable;
		}
		if(InDialogueTag.ContainsSectionName("SeeNickBubbleDialogue"))
		{
			return DefaultSeeNickBubbleDialogueDataTable;
		}
		return nullptr;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		return DefaultResponseDialogueDataTable;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		return DefaultCorrectedDialogueDataTable;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		return DefaultPrimaryDialogueDataTable;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		if(!InDialogueTag.IsValid()){return nullptr;}
		return GetEmbeddedDialogueDataTableByTag(InStructType, InDialogueTag);
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		if(!InDialogueTag.IsValid()){return nullptr;}
		return GetEmbeddedDialogueDataTableByTag(InStructType, InDialogueTag);
	}
	return nullptr;
}

const UDataTable* USI_DialogueDataAsset::GetEmbeddedDialogueDataTableByTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
{
	TArray<FSI_PrimaryDialogue*> PrimaryDialogueArray;
	DefaultPrimaryDialogueDataTable->GetAllRows(nullptr, PrimaryDialogueArray);
	const FSI_DialogueTag PrimaryDialogueTag = InDialogueTag.GetParentTagBySectionIndex(4);
	for(const FSI_PrimaryDialogue* CurrentPrimaryDialogue : PrimaryDialogueArray)
	{
		if(CurrentPrimaryDialogue->DialogueTag == InDialogueTag.GetName())
		{
			if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
			{
				return CurrentPrimaryDialogue->PressDialogueDataTable;
			}
			if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
			{
				return CurrentPrimaryDialogue->ResponseDialogueDataTable;
			}
		}
	}
	return nullptr;
}

const UDataTable* USI_DialogueDataAsset::GetCaseDialogueDataTableByType(const FGameplayTag& InCaseTag, const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
{
	TArray<FSI_CaseDialogueDataTableRow*> CaseDialogueDataTables;
	CaseDialogueDataTable->GetAllRows(nullptr, CaseDialogueDataTables);
	
	for(FSI_CaseDialogueDataTableRow* CurrentCaseTableRow : CaseDialogueDataTables)
	{
		if(!CurrentCaseTableRow) {continue;}
		{
			const USI_CaseData* CurrentCaseData = CurrentCaseTableRow->CaseDialogueData.CaseReference;
			if(!IsValid(CurrentCaseData) || CurrentCaseData->CaseTag != InCaseTag) {continue;}
			{
				const FSI_CaseDialogueData& CaseDialogueData =  CurrentCaseTableRow->CaseDialogueData;
				for(const FSI_PartDialogueData& CurrentPartDialogueData : CaseDialogueData.PartDialogueData)
				{
					return CurrentPartDialogueData.GetDialogueDataTableByType(InStructType, InDialogueTag);
				}
			}
		}
	}

	return nullptr;
}
