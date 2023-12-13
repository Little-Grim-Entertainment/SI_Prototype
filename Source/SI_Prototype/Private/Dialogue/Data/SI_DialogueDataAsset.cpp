// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

FSI_DialogueArrays::FSI_DialogueArrays() : DialogueDataID(FGuid::NewGuid())
{
}

FLGDialogue* FSI_DialogueArrays::GetDialogueByID(const FGuid& InDialogueID)
{
	for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : PrimaryDialogueArray)
	{
		if(CurrentPrimaryDialogue.DialogueID == InDialogueID)
		{
			return &CurrentPrimaryDialogue;
		}
	}
	for(FSI_CorrectedDialogue& CurrentCorrectedDialogue : CorrectedDialogueArray)
	{
		if(CurrentCorrectedDialogue.DialogueID == InDialogueID)
		{
			return &CurrentCorrectedDialogue;
		}
	}
	for(FSI_DefaultResponse& CurrentDefaultResponse : DefaultResponseArray)
	{
		if(CurrentDefaultResponse.DialogueID == InDialogueID)
		{
			return &CurrentDefaultResponse;
		}
	}
	return nullptr;
}

void USI_DialogueDataAsset::InitializeDialogueLabels()
{
	for(FSI_CaseDialogue& CurrentCase : CaseDialogue)
	{
		const FString DialogueLabel = "C" +  FString::FromInt(CurrentCase.CaseNumber);
	
		for (FSI_PartDialogue& CurrentPart : CurrentCase.PartDialogue)
		{
			FString UpdatedDialogueLabel = DialogueLabel + ("P" + FString::FromInt(CurrentPart.PartNumber));
			CurrentPart.DialogueData.DialogueLabel = UpdatedDialogueLabel;
		}
	}
}

void USI_DialogueDataAsset::InitializeFileNames()
{
	const FString InitialFileName = FolderName + "_";
	
	for (FSI_CaseDialogue& CurrentCase : CaseDialogue)
	{
		for (FSI_PartDialogue& CurrentPart : CurrentCase.PartDialogue)
		{
			FString DialogueID = CurrentPart.DialogueData.DialogueLabel;
			FString FileNameWithID = InitialFileName + DialogueID;
			
			for (FLGDialogueURL& CurrentURL : CurrentPart.DialogueURLs)
			{
				CurrentURL.FileName = FileNameWithID + "_" + GetStructTypeNameByTag(CurrentURL.DialogueStructType).ToString();
			}
		}
	}
}

USI_DialogueDataAsset::USI_DialogueDataAsset()
{
	InitializeDialogueLabels();
	InitializeFileNames();
}

void USI_DialogueDataAsset::UpdateDialogue_Internal()
{
	for (FSI_CaseDialogue& CurrentCase : CaseDialogue)
	{
		for (FSI_PartDialogue& CurrentPart : CurrentCase.PartDialogue)
		{
			for (FLGDialogueURL& CurrentURL : CurrentPart.DialogueURLs)
			{
				FString FilePath = UKismetSystemLibrary::GetProjectSavedDirectory();
				FilePath.Append(FolderPath + "/");
				
				FString DialogueLabel = CurrentPart.DialogueData.DialogueLabel;
				
				FLGCsvInfoImportPayload ImportPayload;
				ImportPayload.DialogueStructID = CurrentPart.DialogueData.DialogueDataID;
				ImportPayload.DialogueLabel = DialogueLabel;
				ImportPayload.Caller = this;
				ImportPayload.FolderName = FolderName;
				ImportPayload.FilePath = FilePath;
				ImportPayload.FileName = CurrentURL.FileName;
				ImportPayload.URL = CurrentURL.URL;
				ImportPayload.CsvArrayTypeTag = CurrentURL.DialogueStructType;
		
				OnPayLoadReadyForImport(ImportPayload);
			}
		}
	}
}

void USI_DialogueDataAsset::OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath,  const FString& InDialogueLabel, const FGuid& InDialogueID)
{
	if(InStructType != SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue) {return;}
	
	FSI_DialogueArrays* DialogueDataPtr = GetDialogueDataByID(InDialogueID);
	if(!DialogueDataPtr) {return;}
	
	for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : DialogueDataPtr->PrimaryDialogueArray)
	{
		if(!CurrentPrimaryDialogue.PressURL.IsEmpty())
		{
			FString LineString = "L" + FString::FromInt(CurrentPrimaryDialogue.Line);
			FString DialogueLabel = InDialogueLabel + LineString;
				
			FLGCsvInfoImportPayload ImportPayload;
			ImportPayload.DialogueStructID = CurrentPrimaryDialogue.DialogueID;
			ImportPayload.DialogueLabel = DialogueLabel;
			ImportPayload.Caller = this;
			ImportPayload.FolderName = "PressDialogue";
			ImportPayload.FilePath = InSavePath + "/";
			ImportPayload.FileName = FolderName + "_" + DialogueLabel + "_PressDialogue";
			ImportPayload.URL = CurrentPrimaryDialogue.PressURL;
			ImportPayload.CsvArrayTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
		
			OnPayLoadReadyForImport(ImportPayload);
		}
		if(!CurrentPrimaryDialogue.ResponseURL.IsEmpty())
		{
			FString LineString = "L" + FString::FromInt(CurrentPrimaryDialogue.Line);
			FString DialogueLabel = InDialogueLabel + LineString;
				
			FLGCsvInfoImportPayload ImportPayload;
			ImportPayload.DialogueStructID = CurrentPrimaryDialogue.DialogueID;
			ImportPayload.Caller = this;
			ImportPayload.FolderName = "ResponseDialogue";
			ImportPayload.FilePath = InSavePath + "/";
			ImportPayload.FileName = FolderName + "_" + DialogueLabel + "_ResponseDialogue";
			ImportPayload.URL = CurrentPrimaryDialogue.PressURL;
			ImportPayload.CsvArrayTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
		
			OnPayLoadReadyForImport(ImportPayload);
		}
	}
}

UScriptStruct* USI_DialogueDataAsset::GetUStructContainerByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueStructID)
{
	UScriptStruct* DialogueScriptStruct = nullptr;
	if(IsMainStructType(InGameplayTag))
	{
		const FSI_DialogueArrays* DialogueDataPtr = GetDialogueDataByID(InDialogueStructID);
		if(!DialogueDataPtr){return nullptr;}

		DialogueScriptStruct = DialogueDataPtr->StaticStruct();
	}
	else
	{
		if(const FSI_PrimaryDialogue* PrimaryDialogue = static_cast<FSI_PrimaryDialogue*>(GetDialogueStructByID(InDialogueStructID)))
		{
			DialogueScriptStruct = PrimaryDialogue->StaticStruct();
		}
	}
		
	return DialogueScriptStruct;
}

void* USI_DialogueDataAsset::GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueID)
{
	if(IsMainStructType(InGameplayTag))
	{
		FSI_DialogueArrays* DialogueData = GetDialogueDataByID(InDialogueID);
		if(!DialogueData) {return Super::GetDialogueStructArrayByTag(InGameplayTag, InDialogueID);}

		if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
		{
			return &DialogueData->PrimaryDialogueArray;	
		}
		if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
		{
			return &DialogueData->CorrectedDialogueArray;		
		}
		if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
		{
			return &DialogueData->DefaultResponseArray;
		}
	}	
	
	FSI_PrimaryDialogue* PrimaryDialogue = static_cast<FSI_PrimaryDialogue*>(GetDialogueStructByID(InDialogueID));
	if(PrimaryDialogue)
	{
		if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
		{
			return &PrimaryDialogue->PressDialogueArray;
		}
		if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
		{
			return &PrimaryDialogue->ResponseDialogue;
		}
	}

	return Super::GetDialogueStructArrayByTag(InGameplayTag, InDialogueID);
}

bool USI_DialogueDataAsset::IsMainStructType(const FGameplayTag& InGameplayTag) const
{
	return	InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue ||
			InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue ||
			InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse;
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
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		return FName("PressDialogueArray");		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		return FName("ResponseDialogueArray");		
	}

	return Super::GetStructPropertyNameByTag(InGameplayTag);
}

FName USI_DialogueDataAsset::GetStructTypeNameByTag(const FGameplayTag& InGameplayTag)
{
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		return FName("PrimaryDialogue");		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		return FName("CorrectedDialogue");		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		return FName("DefaultResponse");	
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		return FName("PressDialogue");		
	}
	if(InGameplayTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		return FName("ResponseDialogue");		
	}

	return Super::GetStructPropertyNameByTag(InGameplayTag);
}

FLGDialogue* USI_DialogueDataAsset::GetDialogueStructByID(const FGuid& InDialogueStructID)
{
	FLGDialogue* FoundDialogue = nullptr;
	
	for (FSI_CaseDialogue& CurrentCase : CaseDialogue)
	{
		for(FSI_PartDialogue& CurrentPart : CurrentCase.PartDialogue)
		{
			FoundDialogue = CurrentPart.DialogueData.GetDialogueByID(InDialogueStructID);
			if(FoundDialogue)
			{
				return FoundDialogue;
			}
		}
	}
	
	return FoundDialogue;
}

FSI_DialogueArrays* USI_DialogueDataAsset::GetDialogueDataByID(const FGuid& InDialogueDataID)
{
	FSI_DialogueArrays* FoundDialogue = nullptr;
	
	for (FSI_CaseDialogue& CurrentCase : CaseDialogue)
	{
		for(FSI_PartDialogue& CurrentPart : CurrentCase.PartDialogue)
		{
			if(CurrentPart.DialogueData.DialogueDataID == InDialogueDataID)
			{
				FoundDialogue = &CurrentPart.DialogueData;
				return FoundDialogue;
			}
		}
	}

	return FoundDialogue;
}


#if WITH_EDITOR

// Called when a property is changed in the editor
void USI_DialogueDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName MemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr) ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;

	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(USI_DialogueDataAsset, CaseDialogue))
	{
		InitializeDialogueLabels();
		InitializeFileNames();
	}
}
#endif
