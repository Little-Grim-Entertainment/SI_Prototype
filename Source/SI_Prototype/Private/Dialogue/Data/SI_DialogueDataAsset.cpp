// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_DialogueDataAsset.h"

#include "Cases/Data/SI_CaseData.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"

void USI_DialogueDataAsset::SetDataTableByTypeAndTag(const UDataTable* InDataTable, const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag)
{
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		DefaultPrimaryDialogueDataTable = InDataTable->GetPathName();
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		DefaultCorrectedDialogueDataTable = InDataTable->GetPathName();
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		DefaultResponseDialogueDataTable = InDataTable->GetPathName();
		return;
	}	
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		if(InDialogueTag.ContainsSectionName("RandomBubbleDialogue"))
		{
			DefaultRandomBubbleDialogueDataTable = InDataTable->GetPathName();
			return;
		}
		if(InDialogueTag.ContainsSectionName("SeeNickBubbleDialogue"))
		{
			DefaultSeeNickBubbleDialogueDataTable = InDataTable->GetPathName();
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
				CurrentPrimaryDialogue->PressDialogueDataTable = InDataTable->GetPathName();
				return;
			}
			if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
			{
				CurrentPrimaryDialogue->ResponseDialogueDataTable = InDataTable->GetPathName();
				return;
			}
		}
	}
}

UDataTable* USI_DialogueDataAsset::GetDialogueDataTableByType(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
{
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		if(InDialogueTag.ContainsSectionName("RandomBubbleDialogue"))
		{
			return DefaultRandomBubbleDialogueDataTable.Get();
		}
		if(InDialogueTag.ContainsSectionName("SeeNickBubbleDialogue"))
		{
			return DefaultSeeNickBubbleDialogueDataTable.Get();
		}
		return nullptr;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		return DefaultResponseDialogueDataTable.Get();
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		return DefaultCorrectedDialogueDataTable.Get();
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		return DefaultPrimaryDialogueDataTable.Get();
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

UDataTable* USI_DialogueDataAsset::GetEmbeddedDialogueDataTableByTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
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
				return CurrentPrimaryDialogue->PressDialogueDataTable.Get();
			}
			if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
			{
				return CurrentPrimaryDialogue->ResponseDialogueDataTable.Get();
			}
		}
	}
	return nullptr;
}

UDataTable* USI_DialogueDataAsset::GetCaseDialogueDataTableByType(const FGameplayTag& InCaseTag, const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
{
	TArray<FSI_CaseDialogueDataTableRow*> CaseDialogueDataTables;
	CaseDialogueDataTable->GetAllRows(nullptr, CaseDialogueDataTables);
	
	for(FSI_CaseDialogueDataTableRow* CurrentCaseTableRow : CaseDialogueDataTables)
	{
		if(!CurrentCaseTableRow) {continue;}
		{
			const USI_CaseData* CurrentCaseData = CurrentCaseTableRow->CaseDialogueData.CaseReference.Get();
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
