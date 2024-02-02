// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueTypes.h"
#include "Cases/Data/SI_CaseData.h"
#include "LGBlueprintFunctionLibrary.h"
#include "Cases/Data/SI_PartData.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"

DEFINE_LOG_CATEGORY(LogSI_Dialogue);

FSI_DialogueTagSectionName::FSI_DialogueTagSectionName(const FName& InSectionName) : SectionName(InSectionName)
{
}

bool FSI_DialogueTagSectionName::IsValid() const
{
	return SectionName.IsValid();
}

bool FSI_DialogueTagSectionName::operator==(const FSI_DialogueTagSectionName& OtherSectionName) const
{
	return OtherSectionName.GetSectionName() == SectionName;
}

bool FSI_DialogueTagSectionName::operator!=(const FSI_DialogueTagSectionName& OtherSectionName) const
{
	return OtherSectionName.GetSectionName() != SectionName;
}

FString FSI_DialogueTagSectionName::ToString() const
{
	return SectionName.ToString();
}

FSI_DialogueTag::FSI_DialogueTag()
{
	GenerateDialogueTag();
}

FSI_DialogueTag::FSI_DialogueTag(const FName& InFNameTag)
{
	ConvertFNameToDialogueArray(InFNameTag);
}

void FSI_DialogueTag::AppendNewSection(const FName& InSectionName)
{
	DialogueTagArray.Add(InSectionName);
}

int32 FSI_DialogueTag::SectionNum() const
{
	return DialogueTagArray.Num();
}

FSI_DialogueTag FSI_DialogueTag::GetParentTagBySectionIndex(const int32 InSectionIndex) const
{
	FString ParentTagString;
	const FString InvalidString = "InvalidParentLocation";

	if(InSectionIndex <= 0 || InSectionIndex > DialogueTagArray.Num() - 2)
	{
		return FName(*InvalidString);
	}
	
	for(int32 CurrentIndex = 0; CurrentIndex < DialogueTagArray.Num(); CurrentIndex++)
	{
		if(CurrentIndex > InSectionIndex)
		{
			const FName FoundTag = FName(*ParentTagString);
			return FSI_DialogueTag(FoundTag);
		}

		if(CurrentIndex > 0)
		{
			ParentTagString.Append(".");
		}
		ParentTagString.Append(DialogueTagArray[CurrentIndex].ToString());
	}
		
	return FName(*InvalidString);
}

FName FSI_DialogueTag::GetSectionNameByIndex(const int32 InSectionIndex) const
{
	if(DialogueTagArray.IsEmpty()) {return FName();}
	
	const FSI_DialogueTagSectionName CurrentTagSection = DialogueTagArray[InSectionIndex];
	if(!CurrentTagSection.IsValid()) {return FName();}

	const FString CurrentSectionString = CurrentTagSection.ToString();
	return FName(*CurrentSectionString);
}

void FSI_DialogueTag::ConvertFNameToDialogueArray(const FName& InFNameTag)
{
	if(!InFNameTag.IsValid()) {return;}
	
	FString FNameTagString = InFNameTag.ToString();
	bool bConversionComplete = false;
	
	if(FNameTagString.Find(".") == INDEX_NONE)
	{
		return;
	}
	
	while(!bConversionComplete)
	{
		const int32 PeriodIndex = FNameTagString.Find(".");
		if(PeriodIndex == INDEX_NONE)
		{
			FName SectionName = FName(*FNameTagString);
			if(SectionName.IsValid())
			{
				DialogueTagArray.Add(SectionName);
			}

			bConversionComplete = true;
		}
		else
		{
			const int32 LeftChopCount = (FNameTagString.Len()) - PeriodIndex;
			FString SectionNameString = FNameTagString.LeftChop(LeftChopCount);
			FNameTagString = FNameTagString.RightChop(PeriodIndex + 1);
			FName SectionName = FName(*SectionNameString);
			
			DialogueTagArray.Add(SectionName);
		}
	}

	GenerateDialogueTag();
}

void FSI_DialogueTag::GenerateDialogueTag()
{
	FString GeneratedDialogueTagString;
	for(int32 CurrentIndex = 0; CurrentIndex < DialogueTagArray.Num(); CurrentIndex++)
	{
		FSI_DialogueTagSectionName CurrentTagSection = DialogueTagArray[CurrentIndex];
		if(!CurrentTagSection.IsValid()) {continue;}

		if(CurrentIndex > 0)
		{
			GeneratedDialogueTagString.Append(".");
		}
		GeneratedDialogueTagString.Append(CurrentTagSection.ToString());
	}
	
	GeneratedDialogueTag = FName(*GeneratedDialogueTagString);
}

bool FSI_DialogueTag::IsValid() const
{
	return DialogueTagArray.Num() >= 2;
}

bool FSI_DialogueTag::IsCaseDialogueTag() const
{
	const FString SecondSectionName = GetSectionNameByIndex(1).ToString();
	const bool bIsCaseDialogue = SecondSectionName != "RandomBubbleDialogue" && SecondSectionName != "SeeNickBubbleDialogue" && SecondSectionName != "DefaultDialogue";
	return bIsCaseDialogue;
}

bool FSI_DialogueTag::ContainsSectionName(const FString& InSectionName) const
{
	for(const FSI_DialogueTagSectionName& CurrentSectionName : DialogueTagArray)
	{
		if(CurrentSectionName.ToString() == InSectionName)
		{
			return true;
		}
	}

	return false;
}

bool FSI_DialogueTag::Contains(const FString& InStringValue) const
{
	const FString TagString = ToString();
	return TagString.Contains(InStringValue);
}

FString FSI_DialogueTag::ToString() const
{
	return GeneratedDialogueTag.ToString();
}

FName FSI_DialogueTag::GetName() const
{
	return GeneratedDialogueTag;
}

const TArray<FSI_DialogueTagSectionName>& FSI_DialogueTag::GetDialogueTagArray() const
{
	return DialogueTagArray;
}

bool FSI_DialogueTag::operator==(const FSI_DialogueTag& OtherTag) const
{
	if(DialogueTagArray.Num() != OtherTag.GetDialogueTagArray().Num())
	{
		return false;
	}

	for (int32 CurrentSectionIndex = 0; CurrentSectionIndex < DialogueTagArray.Num(); CurrentSectionIndex++)
	{
		if(DialogueTagArray[CurrentSectionIndex] != OtherTag.GetDialogueTagArray()[CurrentSectionIndex])
		{
			return false;
		}
	}
	
	return true;
}

bool FSI_DialogueTag::operator!=(const FSI_DialogueTag& OtherTag) const
{
	if(DialogueTagArray.Num() != OtherTag.GetDialogueTagArray().Num())
	{
		return true;
	}

	for (int32 CurrentSectionIndex = 0; CurrentSectionIndex < DialogueTagArray.Num(); CurrentSectionIndex++)
	{
		if(DialogueTagArray[CurrentSectionIndex] != OtherTag.GetDialogueTagArray()[CurrentSectionIndex])
		{
			return true;
		}
	}
	
	return false;
}

FString FSI_PartDialogueInfo::GetPartNameNoSpace() const
{
	if(!IsValid(PartReference)) {return "NONE";}

	FString PartNameNoSpace = PartReference->PartName.ToString();
	return PartNameNoSpace;
}

FSI_PartDialogueData::FSI_PartDialogueData(const USI_PartData* InPartData)
{
	PartReference = InPartData;
}

const UDataTable* FSI_PartDialogueData::GetDialogueDataTableByType(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
{
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		if(!InDialogueTag.IsValid()){return nullptr;}
		
		if(InDialogueTag.ContainsSectionName("RandomBubbleDialogue"))
		{
			return RandomBubbleDialogueDataTable;
		}
		if(InDialogueTag.ContainsSectionName("SeeNickBubbleDialogue"))
		{
			return SeeNickBubbleDialogueDataTable;
		}
		return nullptr;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		return DefaultResponseDataTable;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		return CorrectedDialogueDataTable;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		return PrimaryDialogueDataTable;
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

void FSI_PartDialogueData::SetDialogueDataTableByType(const UDataTable* InDataTable, const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag)
{
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		if(!InDialogueTag.IsValid()){return;}
		if(InDialogueTag.ContainsSectionName("RandomBubbleDialogue"))
		{
			RandomBubbleDialogueDataTable = InDataTable;
			return;
		}
		if(InDialogueTag.ContainsSectionName("SeeNickBubbleDialogue"))
		{
			SeeNickBubbleDialogueDataTable = InDataTable;
			return;
		}
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		DefaultResponseDataTable = InDataTable;
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		CorrectedDialogueDataTable = InDataTable;
		return;
	}
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		PrimaryDialogueDataTable = InDataTable;
		return;
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

const UDataTable* FSI_PartDialogueData::GetEmbeddedDialogueDataTableByTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag) const
{
	if(!InDialogueTag.IsValid()){return nullptr;}

	TArray<FSI_PrimaryDialogue*> PrimaryDialogueArray;
	PrimaryDialogueDataTable->GetAllRows(nullptr, PrimaryDialogueArray);
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

void FSI_PartDialogueData::SetEmbeddedDialogueDataTableByTypeTag(const FGameplayTag& InStructType, const FSI_DialogueTag& InDialogueTag, const UDataTable* InDataTable)
{
	if(!InDialogueTag.IsValid()){return;}

	TArray<FSI_PrimaryDialogue*> PrimaryDialogueArray;
	PrimaryDialogueDataTable->GetAllRows(nullptr, PrimaryDialogueArray);
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

FString FSI_CaseDialogueInfo::GetCaseNameNoSpace() const
{
	if(!IsValid(CaseReference)) {return "NONE";}

	FString CaseNameNoSpace = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(CaseReference->CaseTag);
	return CaseNameNoSpace;
}

FSI_CaseDialogueData::FSI_CaseDialogueData(const USI_CaseData* InCaseReference)
{
	CaseReference = InCaseReference;
}

FSI_CaseDialogueDataTableRow::FSI_CaseDialogueDataTableRow(const FSI_CaseDialogueData& InCaseDialogueDataAsset) : CaseDialogueData(InCaseDialogueDataAsset)
{
}

FSI_CaseDialogueDataTableRow::FSI_CaseDialogueDataTableRow(const USI_CaseData* InCaseData)
{
	CaseDialogueData = FSI_CaseDialogueData(InCaseData);
}

FSI_DialogueState::FSI_DialogueState(const UDataTable* InActivePartDialogueTable, const UDataTable* InActiveCorrectedDialogueTable, const UDataTable* InActiveDefaultResponseTable) :
	ActivePrimaryDialogueTable(InActivePartDialogueTable),
	ActiveCorrectedDialogueTable(InActiveCorrectedDialogueTable),
	ActiveDefaultResponseTable(InActiveDefaultResponseTable)
{
	TArray<FSI_PrimaryDialogue*> PrimaryDialogueArray;
	InActivePartDialogueTable->GetAllRows<FSI_PrimaryDialogue>(nullptr, PrimaryDialogueArray);

	for(const FSI_PrimaryDialogue* CurrentPrimaryDialogue : PrimaryDialogueArray)
	{
		CurrentPrimaryDialogueArray.Add(*CurrentPrimaryDialogue);
	}

	TArray<FSI_CorrectedDialogue*> CorrectedDialogueArray;
	InActiveCorrectedDialogueTable->GetAllRows<FSI_CorrectedDialogue>(nullptr, CorrectedDialogueArray);

	for(const FSI_CorrectedDialogue* CurrentCorrectedDialogue : CorrectedDialogueArray)
	{
		CurrentCorrectedDialogueArray.Add(*CurrentCorrectedDialogue);
	}

	TArray<FSI_DefaultResponse*> DefaultResponseArray;
	InActiveDefaultResponseTable->GetAllRows<FSI_DefaultResponse>(nullptr, DefaultResponseArray);

	for(const FSI_DefaultResponse* CurrentDefaultResponse : DefaultResponseArray)
	{
		CurrentDefaultResponseArray.Add(*CurrentDefaultResponse);
	}
}

