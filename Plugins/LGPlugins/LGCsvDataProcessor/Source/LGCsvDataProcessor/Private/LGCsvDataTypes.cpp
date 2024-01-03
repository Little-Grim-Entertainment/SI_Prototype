// Fill out your copyright notice in the Description page of Project Settings.

#include "LGCsvDataTypes.h"
#include "Data/LGDialogueDataAsset.h"

DEFINE_LOG_CATEGORY(LogCsvDataProcessor);


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

void FLGDialogueArrayData::AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload)
{
}

FLGDialogueArray* FLGDialogueArrayData::GetDialogueArrayByID(const FGuid& InDialogueArrayID)
{
	return nullptr;
}