// Fill out your copyright notice in the Description page of Project Settings.

#include "SI_CsvDataTypes.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "LGBlueprintFunctionLibrary.h"

void FSI_DialogueArrayData::AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload, const FName& InDialogueTag)
{
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		FSI_PrimaryDialogueArray* NewPrimaryDialogueArray = new FSI_PrimaryDialogueArray(InDialogueTag, InStructTypeTag);
		DialogueArrays.Add(NewPrimaryDialogueArray);
		OutPayload.DialogueArrayID = NewPrimaryDialogueArray->DialogueArrayID;
		return;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		FSI_CorrectedDialogueArray* NewCorrectedDialogueArray = new FSI_CorrectedDialogueArray(InDialogueTag, InStructTypeTag);
		DialogueArrays.Add(NewCorrectedDialogueArray);
		OutPayload.DialogueArrayID = NewCorrectedDialogueArray->DialogueArrayID;
		return;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		FSI_DefaultResponseArray* NewDefaultResponseArray = new FSI_DefaultResponseArray(InDialogueTag, InStructTypeTag);
		DialogueArrays.Add(NewDefaultResponseArray);
		OutPayload.DialogueArrayID = NewDefaultResponseArray->DialogueArrayID;
		return;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		FSI_PressDialogueArray* NewPressDialogueArray = new FSI_PressDialogueArray(InDialogueTag, InStructTypeTag);
		DialogueArrays.Add(NewPressDialogueArray);
		OutPayload.DialogueArrayID = NewPressDialogueArray->DialogueArrayID;
		return;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		FSI_ResponseDialogueArray* NewResponseDialogueArray = new FSI_ResponseDialogueArray(InDialogueTag, InStructTypeTag);
		DialogueArrays.Add(NewResponseDialogueArray);
		OutPayload.DialogueArrayID = NewResponseDialogueArray->DialogueArrayID;
		return;
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		FSI_BubbleDialogueArray* NewBubbleDialogueArray = new FSI_BubbleDialogueArray(InDialogueTag, InStructTypeTag);
		DialogueArrays.Add(NewBubbleDialogueArray);
		OutPayload.DialogueArrayID = NewBubbleDialogueArray->DialogueArrayID;
	}	
}

FLGDialogueArray* FSI_DialogueArrayData::GetDialogueArrayByID(const FGuid& InDialogueArrayID)
{
	for(FLGDialogueArray* CurrentDialogueArray : DialogueArrays)
	{
		if(CurrentDialogueArray && CurrentDialogueArray->DialogueArrayID == InDialogueArrayID)
		{
			return CurrentDialogueArray;
		}
	}
	return nullptr;
}

FName FSI_DialogueArrayData::ConvertFileNameToEmbeddedTag(const FGameplayTag& InCaseTag, const FString& InFileName)
{
	const FString CaseName = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(InCaseTag);
	const int32 CaseNameIndex = InFileName.Find(CaseName);

	const FString ChoppedFileName = InFileName.RightChop(CaseNameIndex + CaseName.Len());
	FString CombinedTag = InCaseTag.ToString() + ChoppedFileName;

	const FString Underscore = "_";
	const FString Period = ".";
	CombinedTag = CombinedTag.Replace(*Underscore, *Period);
	
	return FName(CombinedTag);
}

FSI_PrimaryDialogueArray::FSI_PrimaryDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
	PropertyName = "PrimaryDialogueArray";
}

FSI_PrimaryDialogueArray::FSI_PrimaryDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType)
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
	PropertyName = "PrimaryDialogueArray";
	
	DialogueTag = InDialogueTag.GetName();
	GenerateDialogueTagFromTypeName(DialogueTag, InStructType);
}

void FSI_PrimaryDialogueArray::UpdateDataTableStructValues(TArray<FSI_PrimaryDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != PrimaryDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < PrimaryDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->Line = PrimaryDialogueArray[ArrayIndex].Line;
		OutDataTableStructArray[ArrayIndex]->PressURL = PrimaryDialogueArray[ArrayIndex].PressURL;
		OutDataTableStructArray[ArrayIndex]->ResponseURL = PrimaryDialogueArray[ArrayIndex].ResponseURL;
		OutDataTableStructArray[ArrayIndex]->IsTrueStatement = PrimaryDialogueArray[ArrayIndex].IsTrueStatement;
		OutDataTableStructArray[ArrayIndex]->SpeakerTag = PrimaryDialogueArray[ArrayIndex].SpeakerTag;
		OutDataTableStructArray[ArrayIndex]->Dialogue = PrimaryDialogueArray[ArrayIndex].Dialogue;
		OutDataTableStructArray[ArrayIndex]->EmphasizedWordsString = PrimaryDialogueArray[ArrayIndex].EmphasizedWordsString;
		OutDataTableStructArray[ArrayIndex]->EmphasizedColorsString = PrimaryDialogueArray[ArrayIndex].EmphasizedColorsString;
		OutDataTableStructArray[ArrayIndex]->DialogueID = PrimaryDialogueArray[ArrayIndex].DialogueID;
	}
}

void FSI_PrimaryDialogueArray::SetEmbeddedDialogueTableByTag(const UDataTable* InDataTable, const FGameplayTag& InStructType)
{
	if(InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		//TODO:: @jeff Set this table to the correct struct
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

UDataTable* FSI_PrimaryDialogueArray::GetDialogueDataTable()
{
	return PrimaryDialogueDataTable;
}

void FSI_PrimaryDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < PrimaryDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(PrimaryDialogueArray[CurrentIndex].DialogueTag, PrimaryDialogueArray[CurrentIndex]);
	}
}

void FSI_PrimaryDialogueArray::SetDataTable(UDataTable* InDataTable)
{
	PrimaryDialogueDataTable = InDataTable;
}

void FSI_PrimaryDialogueArray::InitializeContainedDialogueTags()
{
	for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : PrimaryDialogueArray)
	{
		FString DialogueTagString = DialogueTag.ToString();
		DialogueTagString.Append(".L");
		DialogueTagString.Append(FString::FromInt(CurrentPrimaryDialogue.Line));

		CurrentPrimaryDialogue.DialogueTag = FName(DialogueTagString);
	}
}

FSI_CorrectedDialogueArray::FSI_CorrectedDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue;
	PropertyName = "CorrectedDialogueArray";
}

FSI_CorrectedDialogueArray::FSI_CorrectedDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType)
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue;
	PropertyName = "CorrectedDialogueArray";
	
	DialogueTag = InDialogueTag.GetName();
	GenerateDialogueTagFromTypeName(DialogueTag, InStructType);
}

void FSI_CorrectedDialogueArray::UpdateDataTableStructValues(TArray<FSI_CorrectedDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != CorrectedDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < CorrectedDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->CorrectedLine = CorrectedDialogueArray[ArrayIndex].CorrectedLine;
		OutDataTableStructArray[ArrayIndex]->SpeakerLine = CorrectedDialogueArray[ArrayIndex].SpeakerLine;
		OutDataTableStructArray[ArrayIndex]->SpeakerTag = CorrectedDialogueArray[ArrayIndex].SpeakerTag;
		OutDataTableStructArray[ArrayIndex]->Dialogue = CorrectedDialogueArray[ArrayIndex].Dialogue;
		OutDataTableStructArray[ArrayIndex]->EmphasizedWordsString = CorrectedDialogueArray[ArrayIndex].EmphasizedWordsString;
		OutDataTableStructArray[ArrayIndex]->EmphasizedColorsString = CorrectedDialogueArray[ArrayIndex].EmphasizedColorsString;
		OutDataTableStructArray[ArrayIndex]->DialogueID = CorrectedDialogueArray[ArrayIndex].DialogueID;
	}
}

TArray<FSI_CorrectedDialogue>* FSI_CorrectedDialogueArray::GetDialogueArray()
{
	return &CorrectedDialogueArray;
}

UScriptStruct* FSI_CorrectedDialogueArray::GetStructContainer()
{
	return StaticStruct();
}

UDataTable* FSI_CorrectedDialogueArray::GetDialogueDataTable()
{
	return CorrectedDialogueDataTable;
}

void FSI_CorrectedDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < CorrectedDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(CorrectedDialogueArray[CurrentIndex].DialogueTag, CorrectedDialogueArray[CurrentIndex]);
	}
}

void FSI_CorrectedDialogueArray::SetDataTable(UDataTable* InDataTable)
{
	CorrectedDialogueDataTable = InDataTable; 
}

void FSI_CorrectedDialogueArray::InitializeContainedDialogueTags()
{
	for(FSI_CorrectedDialogue& CurrentCorrectedDialogue : CorrectedDialogueArray)
	{
		FString DialogueTagString = DialogueTag.ToString();
		DialogueTagString.Append(".CL");
		DialogueTagString.Append(FString::FromInt(CurrentCorrectedDialogue.CorrectedLine));

		CurrentCorrectedDialogue.DialogueTag = FName(DialogueTagString);
	}
}

FSI_DefaultResponseArray::FSI_DefaultResponseArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse;
	PropertyName = "DefaultResponseArray";
}

FSI_DefaultResponseArray::FSI_DefaultResponseArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType)
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse;
	PropertyName = "DefaultResponseArray";
	
	DialogueTag = InDialogueTag.GetName();
	GenerateDialogueTagFromTypeName(DialogueTag, InStructType);
}

void FSI_DefaultResponseArray::UpdateDataTableStructValues(TArray<FSI_DefaultResponse*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != DefaultResponseArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < DefaultResponseArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->ResponseLine = DefaultResponseArray[ArrayIndex].ResponseLine;
		OutDataTableStructArray[ArrayIndex]->SpeakerTag = DefaultResponseArray[ArrayIndex].SpeakerTag;
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

UDataTable* FSI_DefaultResponseArray::GetDialogueDataTable()
{
	return DefaultResponseDataTable;
}

void FSI_DefaultResponseArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < DefaultResponseArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(DefaultResponseArray[CurrentIndex].DialogueTag, DefaultResponseArray[CurrentIndex]);
	}
}

void FSI_DefaultResponseArray::SetDataTable(UDataTable* InDataTable)
{
	DefaultResponseDataTable = InDataTable;
}

void FSI_DefaultResponseArray::InitializeContainedDialogueTags()
{
	for(FSI_DefaultResponse& CurrentDefaultResponse : DefaultResponseArray)
	{
		FString DialogueTagString = DialogueTag.ToString();
		DialogueTagString.Append(".DRL");
		DialogueTagString.Append(FString::FromInt(CurrentDefaultResponse.ResponseLine));

		CurrentDefaultResponse.DialogueTag = FName(DialogueTagString);
	}
}

FSI_BubbleDialogueArray::FSI_BubbleDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue;
	PropertyName = "BubbleDialogueArray";
}

FSI_BubbleDialogueArray::FSI_BubbleDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType)
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue;
	PropertyName = "BubbleDialogueArray";
	
	DialogueTag = InDialogueTag.GetName();
	GenerateDialogueTagFromTypeName(DialogueTag, InStructType);
}

void FSI_BubbleDialogueArray::UpdateDataTableStructValues(TArray<FSI_BubbleDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != BubbleDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < BubbleDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->DialogueID = BubbleDialogueArray[ArrayIndex].DialogueID;
	}
}

TArray<FSI_BubbleDialogue>* FSI_BubbleDialogueArray::GetDialogueArray()
{
	return &BubbleDialogueArray;
}

UScriptStruct* FSI_BubbleDialogueArray::GetStructContainer()
{
	return StaticStruct();
}

UDataTable* FSI_BubbleDialogueArray::GetDialogueDataTable()
{
	return BubbleDialogueDataTable;
}

void FSI_BubbleDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < BubbleDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(BubbleDialogueArray[CurrentIndex].DialogueTag, BubbleDialogueArray[CurrentIndex]);
	}
}

void FSI_BubbleDialogueArray::SetDataTable(UDataTable* InDataTable)
{
	BubbleDialogueDataTable = InDataTable;
}

void FSI_BubbleDialogueArray::InitializeContainedDialogueTags()
{
	for(int32 CurrentIndex = 0; CurrentIndex < BubbleDialogueArray.Num(); CurrentIndex++)
	{
		FSI_BubbleDialogue& CurrentBubbleDialogue = BubbleDialogueArray[CurrentIndex];
		
		FString DialogueTagString = DialogueTag.ToString();
		DialogueTagString.Append(".RB");
		DialogueTagString.Append(FString::FromInt(CurrentIndex));

		CurrentBubbleDialogue.DialogueTag = FName(DialogueTagString);
	}
}


FSI_PressDialogueArray::FSI_PressDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
	PropertyName = "PressDialogueArray";
}

FSI_PressDialogueArray::FSI_PressDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType)
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
	PropertyName = "PressDialogueArray";
	
	DialogueTag = InDialogueTag.GetName();
	GenerateDialogueTagFromTypeName(DialogueTag, InStructType);
}

void FSI_PressDialogueArray::UpdateDataTableStructValues(TArray<FSI_PressDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != PressDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < PressDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->PressLine = PressDialogueArray[ArrayIndex].PressLine;
		OutDataTableStructArray[ArrayIndex]->CanPresentEvidence = PressDialogueArray[ArrayIndex].CanPresentEvidence;
		OutDataTableStructArray[ArrayIndex]->SpeakerTag = PressDialogueArray[ArrayIndex].SpeakerTag;
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

UDataTable* FSI_PressDialogueArray::GetDialogueDataTable()
{
	return PressDialogueDataTable;
}

void FSI_PressDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < PressDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(PressDialogueArray[CurrentIndex].DialogueTag, PressDialogueArray[CurrentIndex]);
	}
}

void FSI_PressDialogueArray::SetDataTable(UDataTable* InDataTable)
{
	PressDialogueDataTable = InDataTable;
}

void FSI_PressDialogueArray::InitializeContainedDialogueTags()
{
	for(FSI_PressDialogue& CurrentPressDialogue : PressDialogueArray)
	{
		FString DialogueTagString = DialogueTag.ToString();
		DialogueTagString.Append(".PL");
		DialogueTagString.Append(FString::FromInt(CurrentPressDialogue.PressLine));

		CurrentPressDialogue.DialogueTag = FName(DialogueTagString);
	}
}

FSI_ResponseDialogueArray::FSI_ResponseDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
	PropertyName = "ResponseDialogueArray";
}

FSI_ResponseDialogueArray::FSI_ResponseDialogueArray(const FSI_DialogueTag& InDialogueTag, const FGameplayTag& InStructType)
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
	PropertyName = "ResponseDialogueArray";
	
	DialogueTag = InDialogueTag.GetName();
	GenerateDialogueTagFromTypeName(DialogueTag, InStructType);
}

void FSI_ResponseDialogueArray::UpdateDataTableStructValues(TArray<FSI_ResponseDialogue*>& OutDataTableStructArray)
{
	if(OutDataTableStructArray.Num() != ResponseDialogueArray.Num()) {return;}
	
	for(int32 ArrayIndex = 0; ArrayIndex < ResponseDialogueArray.Num(); ArrayIndex++)
	{
		OutDataTableStructArray[ArrayIndex]->ResponseLine = ResponseDialogueArray[ArrayIndex].ResponseLine;
		OutDataTableStructArray[ArrayIndex]->IsEvidenceCorrect = ResponseDialogueArray[ArrayIndex].IsEvidenceCorrect;
		OutDataTableStructArray[ArrayIndex]->SpeakerTag = ResponseDialogueArray[ArrayIndex].SpeakerTag;
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

UDataTable* FSI_ResponseDialogueArray::GetDialogueDataTable()
{
	return ResponseDialogueDataTable;
}

void FSI_ResponseDialogueArray::InitializeDialogueDataTable(UDataTable* InDataTable)
{
	if(!IsValid(InDataTable)){return;}

	for (int32 CurrentIndex = 0; CurrentIndex < ResponseDialogueArray.Num(); CurrentIndex++)
	{
		InDataTable->AddRow(ResponseDialogueArray[CurrentIndex].DialogueTag, ResponseDialogueArray[CurrentIndex]);
	}
}

void FSI_ResponseDialogueArray::SetDataTable(UDataTable* InDataTable)
{
	ResponseDialogueDataTable = InDataTable;
}

void FSI_ResponseDialogueArray::InitializeContainedDialogueTags()
{
	for(FSI_ResponseDialogue& CurrentResponseDialogue : ResponseDialogueArray)
	{
		FString DialogueTagString = DialogueTag.ToString();
		DialogueTagString.Append(".RL");
		DialogueTagString.Append(FString::FromInt(CurrentResponseDialogue.ResponseLine));

		CurrentResponseDialogue.DialogueTag = FName(DialogueTagString);
	}
}
