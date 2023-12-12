// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"

FSI_DialogueArrays::FSI_DialogueArrays()
{
}

USI_DialogueDataAsset::USI_DialogueDataAsset()
{
}

UScriptStruct* USI_DialogueDataAsset::GetUStructContainer()
{
	const FSI_DialogueArrays* DialogueDataPtr = &DialogueData;
	UScriptStruct* DialogueScriptStruct = DialogueDataPtr->StaticStruct();
	return DialogueScriptStruct;
}

void* USI_DialogueDataAsset::GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag)
{
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		return &DialogueData.PrimaryDialogueArray;		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		return &DialogueData.CorrectedDialogueArray;		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		return &DialogueData.DefaultResponseArray;		
	}

	return Super::GetDialogueStructArrayByTag(InGameplayTag);
}

FName USI_DialogueDataAsset::GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag)
{
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		return FName("PrimaryDialogueArray");		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		return FName("CorrectedDialogueArray");		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		return FName("DefaultResponseArray");		
	}

	return Super::GetStructPropertyNameByTag(InGameplayTag);
}
