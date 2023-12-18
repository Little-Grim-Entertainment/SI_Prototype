// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/SI_DialogueTypes.h"

FSI_DialogueArrayData::FSI_DialogueArrayData() : DialogueDataID(FGuid::NewGuid())
{
}

void FSI_DialogueArrayData::AddNewArrayByTag(const FGameplayTag& InStructTypeTag)
{
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		DialogueArrays.Add(new FSI_PrimaryDialogueArray());
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		DialogueArrays.Add(new FSI_CorrectedDialogueArray());
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		DialogueArrays.Add(new FSI_DefaultResponseArray());
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		DialogueArrays.Add(new FSI_PressDialogueArray());
	}
	if(InStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		DialogueArrays.Add(new FSI_ResponseDialogueArray());
	}	
}

void FSI_DialogueArrayData::RemoveArrayByTag(const FGameplayTag& InStructTypeTag)
{
	for(int32 CurrentIndex = 0; CurrentIndex < DialogueArrays.Num(); CurrentIndex++)
	{
		if(DialogueArrays[CurrentIndex] && DialogueArrays[CurrentIndex]->DialogueStructTypeTag == InStructTypeTag)
		{
			DialogueArrays.RemoveAt(CurrentIndex);
			return;
		}
	}
}

bool FSI_DialogueArrayData::ContainsArrayByTypeTag(const FGameplayTag& InStructTypeTag) const
{
	for(const FLGDialogueArray* CurrentDialogueArray : DialogueArrays)
	{
		if(CurrentDialogueArray && CurrentDialogueArray->DialogueStructTypeTag == InStructTypeTag)
		{
			return true;
		}
	}
	return false;
}

FLGDialogueArray* FSI_DialogueArrayData::GetDialogueArrayByTag(const FGameplayTag& InStructTypeTag)
{
	for(FLGDialogueArray* CurrentDialogueArray : DialogueArrays)
	{
		if(CurrentDialogueArray && CurrentDialogueArray->DialogueStructTypeTag == InStructTypeTag)
		{
			return CurrentDialogueArray;
		}
	}

	FLGDialogueArray* DialogueArray = GetDialogueArrayByTag(SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue);
	FSI_PrimaryDialogueArray* PrimaryDialogueArrayPtr = static_cast<FSI_PrimaryDialogueArray*>(DialogueArray);
	if(PrimaryDialogueArrayPtr)
	{
		for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : PrimaryDialogueArrayPtr->PrimaryDialogueArray)
		{
			FSI_PressDialogueArray& PressDialogue = CurrentPrimaryDialogue.PressDialogue;
			if(PressDialogue.DialogueStructTypeTag == InStructTypeTag)
			{
				return &PressDialogue;
			}
			
			FSI_ResponseDialogueArray& ResponseDialogue = CurrentPrimaryDialogue.ResponseDialogue;
			if(ResponseDialogue.DialogueStructTypeTag == InStructTypeTag)
			{
				return &ResponseDialogue;
			}
		}
	}

	return nullptr;
}

FSI_PrimaryDialogueArray::FSI_PrimaryDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
	PropertyName = "PrimaryDialogueArray";
}

TArray<FSI_PrimaryDialogue>* FSI_PrimaryDialogueArray::GetDialogueArray()
{
	return &PrimaryDialogueArray;
}

FArrayProperty* FSI_PrimaryDialogueArray::GetArrayProperty()
{
	const UScriptStruct* ScriptStruct = StaticStruct();
	FArrayProperty* FoundProperty = FindFProperty<FArrayProperty>(ScriptStruct, PropertyName);
	return FoundProperty;
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

FArrayProperty* FSI_CorrectedDialogueArray::GetArrayProperty()
{
	const UScriptStruct* ScriptStruct = StaticStruct();
	FArrayProperty* FoundProperty = FindFProperty<FArrayProperty>(ScriptStruct, PropertyName);
	return FoundProperty;
}

FSI_DefaultResponseArray::FSI_DefaultResponseArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse;
	PropertyName = "DefaultResponseArray";
}

TArray<FSI_DefaultResponse>* FSI_DefaultResponseArray::GetDialogueArray()
{
	return &DefaultResponseArray;
}

FArrayProperty* FSI_DefaultResponseArray::GetArrayProperty()
{
	const UScriptStruct* ScriptStruct = StaticStruct();
	FArrayProperty* FoundProperty = FindFProperty<FArrayProperty>(ScriptStruct, PropertyName);
	return FoundProperty;
}

FSI_PressDialogueArray::FSI_PressDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
	PropertyName = "PressDialogueArray";
}

TArray<FSI_PressDialogue>* FSI_PressDialogueArray::GetDialogueArray()
{
	return &PressDialogueArray;
}

FArrayProperty* FSI_PressDialogueArray::GetArrayProperty()
{
	const UScriptStruct* ScriptStruct = StaticStruct();
	FArrayProperty* FoundProperty = FindFProperty<FArrayProperty>(ScriptStruct, PropertyName);
	return FoundProperty;
}

FSI_ResponseDialogueArray::FSI_ResponseDialogueArray()
{
	DialogueStructTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
	PropertyName = "ResponseDialogueArray";
}


TArray<FSI_ResponseDialogue>* FSI_ResponseDialogueArray::GetDialogueArray()
{
	return &ResponseDialogueArray;
}

FArrayProperty* FSI_ResponseDialogueArray::GetArrayProperty()
{
	const UScriptStruct* ScriptStruct = StaticStruct();
	FArrayProperty* FoundProperty = FindFProperty<FArrayProperty>(ScriptStruct, PropertyName);
	return FoundProperty;
}

