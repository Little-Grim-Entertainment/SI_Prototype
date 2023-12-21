// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueTypes.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"

DEFINE_LOG_CATEGORY(LogSI_Dialogue);

FSI_DialogueArrayData::FSI_DialogueArrayData() : DialogueDataID(FGuid::NewGuid())
{
}

void FSI_DialogueArrayData::AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload)
{
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		FSI_PrimaryDialogueArray* NewPrimaryDialogueArray = new FSI_PrimaryDialogueArray();
		DialogueArrayPtrs.Add(NewPrimaryDialogueArray);
		DialogueArrays.Add(*NewPrimaryDialogueArray);
		OutPayload.DialogueArrayID = NewPrimaryDialogueArray->DialogueArrayID;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		FSI_CorrectedDialogueArray* NewCorrectedDialogueArray = new FSI_CorrectedDialogueArray();
		DialogueArrayPtrs.Add(NewCorrectedDialogueArray);
		DialogueArrays.Add(*NewCorrectedDialogueArray);
		OutPayload.DialogueArrayID = NewCorrectedDialogueArray->DialogueArrayID;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		FSI_DefaultResponseArray* NewDefaultResponseArray = new FSI_DefaultResponseArray();
		DialogueArrayPtrs.Add(NewDefaultResponseArray);
		DialogueArrays.Add(*NewDefaultResponseArray);
		OutPayload.DialogueArrayID = NewDefaultResponseArray->DialogueArrayID;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		FSI_PressDialogueArray* NewPressDialogueArray = new FSI_PressDialogueArray();
		DialogueArrayPtrs.Add(NewPressDialogueArray);
		DialogueArrays.Add(*NewPressDialogueArray);
		OutPayload.DialogueArrayID = NewPressDialogueArray->DialogueArrayID;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		FSI_ResponseDialogueArray* NewResponseDialogueArray = new FSI_ResponseDialogueArray();
		DialogueArrayPtrs.Add(NewResponseDialogueArray);
		DialogueArrays.Add(*NewResponseDialogueArray);
		OutPayload.DialogueArrayID = NewResponseDialogueArray->DialogueArrayID;
	}	
}

FLGDialogueArray* FSI_DialogueArrayData::GetDialogueArrayByID(const FGuid& InDialogueArrayID)
{
	for(FLGDialogueArray* CurrentDialogueArray : DialogueArrayPtrs)
	{
		if(CurrentDialogueArray && CurrentDialogueArray->DialogueArrayID == InDialogueArrayID)
		{
			return CurrentDialogueArray;
		}
	}
	return nullptr;
}

FSI_PrimaryDialogueArray::FSI_PrimaryDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
	PropertyName = "PrimaryDialogueArray";
}

void FSI_PrimaryDialogueArray::UpdateDataTableStructValues(TArray<FSI_PrimaryDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != PrimaryDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < PrimaryDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->Line = PrimaryDialogueArray[ArrayIndex].Line;
		OutDataTableStructArray[ArrayIndex]->PressURL = PrimaryDialogueArray[ArrayIndex].PressURL;
		OutDataTableStructArray[ArrayIndex]->PressDialogue = PrimaryDialogueArray[ArrayIndex].PressDialogue;
		OutDataTableStructArray[ArrayIndex]->ResponseURL = PrimaryDialogueArray[ArrayIndex].ResponseURL;
		OutDataTableStructArray[ArrayIndex]->ResponseDialogue = PrimaryDialogueArray[ArrayIndex].ResponseDialogue;
		OutDataTableStructArray[ArrayIndex]->IsTrueStatement = PrimaryDialogueArray[ArrayIndex].IsTrueStatement;
		OutDataTableStructArray[ArrayIndex]->SpeakerName = PrimaryDialogueArray[ArrayIndex].SpeakerName;
		OutDataTableStructArray[ArrayIndex]->Dialogue = PrimaryDialogueArray[ArrayIndex].Dialogue;
		OutDataTableStructArray[ArrayIndex]->EmphasizedWordsString = PrimaryDialogueArray[ArrayIndex].EmphasizedWordsString;
		OutDataTableStructArray[ArrayIndex]->EmphasizedColorsString = PrimaryDialogueArray[ArrayIndex].EmphasizedColorsString;
		OutDataTableStructArray[ArrayIndex]->DialogueID = PrimaryDialogueArray[ArrayIndex].DialogueID;
	}
}

void FSI_CorrectedDialogueArray::UpdateDataTableStructValues(TArray<FSI_CorrectedDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != CorrectedDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < CorrectedDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->CorrectedLine = CorrectedDialogueArray[ArrayIndex].CorrectedLine;
		OutDataTableStructArray[ArrayIndex]->SpeakerLine = CorrectedDialogueArray[ArrayIndex].SpeakerLine;
		OutDataTableStructArray[ArrayIndex]->SpeakerName = CorrectedDialogueArray[ArrayIndex].SpeakerName;
		OutDataTableStructArray[ArrayIndex]->Dialogue = CorrectedDialogueArray[ArrayIndex].Dialogue;
		OutDataTableStructArray[ArrayIndex]->EmphasizedWordsString = CorrectedDialogueArray[ArrayIndex].EmphasizedWordsString;
		OutDataTableStructArray[ArrayIndex]->EmphasizedColorsString = CorrectedDialogueArray[ArrayIndex].EmphasizedColorsString;
		OutDataTableStructArray[ArrayIndex]->DialogueID = CorrectedDialogueArray[ArrayIndex].DialogueID;
	}
}

TArray<FSI_PrimaryDialogue>* FSI_PrimaryDialogueArray::GetDialogueArray()
{
	return &PrimaryDialogueArray;
}

UScriptStruct* FSI_PrimaryDialogueArray::GetStructContainer()
{
	return StaticStruct();
}

void FSI_PrimaryDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < PrimaryDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(FName(FString::FromInt(CurrentIndex + 1)), PrimaryDialogueArray[CurrentIndex]);
	}
}

FSI_CorrectedDialogueArray::FSI_CorrectedDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue;
	PropertyName = "CorrectedDialogueArray";
}

TArray<FSI_CorrectedDialogue>* FSI_CorrectedDialogueArray::GetDialogueArray()
{
	return &CorrectedDialogueArray;
}

UScriptStruct* FSI_CorrectedDialogueArray::GetStructContainer()
{
	return StaticStruct();
}

void FSI_CorrectedDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < CorrectedDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(FName(FString::FromInt(CurrentIndex + 1)), CorrectedDialogueArray[CurrentIndex]);
	}
}

FSI_DefaultResponseArray::FSI_DefaultResponseArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse;
	PropertyName = "DefaultResponseArray";
}

void FSI_DefaultResponseArray::UpdateDataTableStructValues(TArray<FSI_DefaultResponse*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != DefaultResponseArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < DefaultResponseArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->ResponseLine = DefaultResponseArray[ArrayIndex].ResponseLine;
		OutDataTableStructArray[ArrayIndex]->SpeakerName = DefaultResponseArray[ArrayIndex].SpeakerName;
		OutDataTableStructArray[ArrayIndex]->Dialogue = DefaultResponseArray[ArrayIndex].Dialogue;
		OutDataTableStructArray[ArrayIndex]->EmphasizedWordsString = DefaultResponseArray[ArrayIndex].EmphasizedWordsString;
		OutDataTableStructArray[ArrayIndex]->EmphasizedColorsString = DefaultResponseArray[ArrayIndex].EmphasizedColorsString;
		OutDataTableStructArray[ArrayIndex]->DialogueID = DefaultResponseArray[ArrayIndex].DialogueID;
	}
}

TArray<FSI_DefaultResponse>* FSI_DefaultResponseArray::GetDialogueArray()
{
	return &DefaultResponseArray;
}

UScriptStruct* FSI_DefaultResponseArray::GetStructContainer()
{
	return StaticStruct();
}

void FSI_DefaultResponseArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < DefaultResponseArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(FName(FString::FromInt(CurrentIndex + 1)), DefaultResponseArray[CurrentIndex]);
	}
}

FSI_PressDialogueArray::FSI_PressDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
	PropertyName = "PressDialogueArray";
}

void FSI_PressDialogueArray::UpdateDataTableStructValues(TArray<FSI_PressDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != PressDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < PressDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->PressLine = PressDialogueArray[ArrayIndex].PressLine;
		OutDataTableStructArray[ArrayIndex]->CanPresentEvidence = PressDialogueArray[ArrayIndex].CanPresentEvidence;
		OutDataTableStructArray[ArrayIndex]->SpeakerName = PressDialogueArray[ArrayIndex].SpeakerName;
		OutDataTableStructArray[ArrayIndex]->Dialogue = PressDialogueArray[ArrayIndex].Dialogue;
		OutDataTableStructArray[ArrayIndex]->EmphasizedWordsString = PressDialogueArray[ArrayIndex].EmphasizedWordsString;
		OutDataTableStructArray[ArrayIndex]->EmphasizedColorsString = PressDialogueArray[ArrayIndex].EmphasizedColorsString;
		OutDataTableStructArray[ArrayIndex]->DialogueID = PressDialogueArray[ArrayIndex].DialogueID;
	}
}

TArray<FSI_PressDialogue>* FSI_PressDialogueArray::GetDialogueArray()
{
	return &PressDialogueArray;
}

UScriptStruct* FSI_PressDialogueArray::GetStructContainer()
{
	return StaticStruct();
}

void FSI_PressDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < PressDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(FName(FString::FromInt(CurrentIndex + 1)), PressDialogueArray[CurrentIndex]);
	}
}

FSI_ResponseDialogueArray::FSI_ResponseDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
	PropertyName = "ResponseDialogueArray";
}


void FSI_ResponseDialogueArray::UpdateDataTableStructValues(TArray<FSI_ResponseDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != ResponseDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < ResponseDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->ResponseLine = ResponseDialogueArray[ArrayIndex].ResponseLine;
		OutDataTableStructArray[ArrayIndex]->IsEvidenceCorrect = ResponseDialogueArray[ArrayIndex].IsEvidenceCorrect;
		OutDataTableStructArray[ArrayIndex]->SpeakerName = ResponseDialogueArray[ArrayIndex].SpeakerName;
		OutDataTableStructArray[ArrayIndex]->Dialogue = ResponseDialogueArray[ArrayIndex].Dialogue;
		OutDataTableStructArray[ArrayIndex]->EmphasizedWordsString = ResponseDialogueArray[ArrayIndex].EmphasizedWordsString;
		OutDataTableStructArray[ArrayIndex]->EmphasizedColorsString = ResponseDialogueArray[ArrayIndex].EmphasizedColorsString;
		OutDataTableStructArray[ArrayIndex]->DialogueID = ResponseDialogueArray[ArrayIndex].DialogueID;
	}
}

TArray<FSI_ResponseDialogue>* FSI_ResponseDialogueArray::GetDialogueArray()
{
	return &ResponseDialogueArray;
}

UScriptStruct* FSI_ResponseDialogueArray::GetStructContainer()
{
	return StaticStruct();
}

void FSI_ResponseDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < ResponseDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(FName(FString::FromInt(CurrentIndex + 1)), ResponseDialogueArray[CurrentIndex]);
	}
}

