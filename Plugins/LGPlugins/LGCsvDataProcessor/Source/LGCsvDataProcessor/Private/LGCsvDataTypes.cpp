// Fill out your copyright notice in the Description page of Project Settings.

#include "LGCsvDataTypes.h"
#include "LGBlueprintFunctionLibrary.h"

DEFINE_LOG_CATEGORY(LogCsvDataProcessor);


FLGDialogueArray::FLGDialogueArray() : DialogueArrayID(FGuid::NewGuid())
{
	
}

void FLGDialogueArray::GenerateDialogueTagFromTypeName(FName& OutDialogueTag, const FGameplayTag& InStructType)
{
	if(!OutDialogueTag.IsValid() || !InStructType.IsValid()) {return;}

	FString StructType = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(InStructType);
	
	FString DialogueTagString = OutDialogueTag.ToString();
	DialogueTagString.Append(".");
	DialogueTagString.Append(StructType);

	OutDialogueTag = FName(DialogueTagString);	
}

void FLGDialogueArray::SetDataTable(UDataTable* InDataTable)
{
}

UScriptStruct* FLGDialogueArray::GetStructContainer()
{
	return nullptr;
}

UDataTable* FLGDialogueArray::GetDialogueDataTable()
{
	return nullptr;
}

void FLGDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
}

void FLGDialogueArray::InitializeContainedDialogueTags()
{
}

bool FLGDialogueArray::operator==(const FLGDialogueArray& OtherDialogue) const
{
	return OtherDialogue.DialogueStructTypeTag == DialogueStructTypeTag;
}

bool FLGDialogueArray::operator!=(const FLGDialogueArray& OtherDialogue) const
{
	return OtherDialogue.DialogueStructTypeTag != DialogueStructTypeTag;
}

FLGDialogueArrayData::FLGDialogueArrayData() : DialogueDataID(FGuid::NewGuid())
{
}

void FLGDialogueArrayData::AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload, const FName& InDialogueTag)
{
}

FLGDialogueArray* FLGDialogueArrayData::GetDialogueArrayByID(const FGuid& InDialogueArrayID)
{
	return nullptr;
}