// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "Data/Characters/SI_CharacterData.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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
			if(!CurrentPart.DialogueData.DialogueArrays.IsEmpty())
			{
				CurrentPart.DialogueData.DialogueArrays.Empty();
			}
			
			for (FLGDialogueURL& CurrentURL : CurrentPart.DialogueURLs)
			{
				FString FilePath = UKismetSystemLibrary::GetProjectDirectory();
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
			
				CurrentPart.DialogueData.AddNewArrayByTag(CurrentURL.DialogueStructType);
				OnPayLoadReadyForImport(ImportPayload);
			}
		}
	}
}

void USI_DialogueDataAsset::OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath,  const FString& InDialogueLabel, const FGuid& InDialogueDataID)
{
	FSI_DialogueArrayData* DialogueDataPtr = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueDataPtr) {return;}

	FLGDialogueArray* DialogueArrayPtr = DialogueDataPtr->GetDialogueArrayByTag(SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue);
	FSI_PrimaryDialogueArray* PrimaryDialogueArrayPtr = static_cast<FSI_PrimaryDialogueArray*>(DialogueArrayPtr);
	if(!PrimaryDialogueArrayPtr) {return;}
	
	for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : PrimaryDialogueArrayPtr->PrimaryDialogueArray)
	{
		if(!CurrentPrimaryDialogue.PressURL.IsEmpty())
		{
			FString LineString = "L" + FString::FromInt(CurrentPrimaryDialogue.Line);
			FString DialogueLabel = InDialogueLabel + LineString;
				
			FLGCsvInfoImportPayload ImportPayload;
			ImportPayload.DialogueStructID = InDialogueDataID;
			ImportPayload.DialogueLabel = DialogueLabel;
			ImportPayload.Caller = this;
			ImportPayload.FolderName = "PressDialogue";
			ImportPayload.FilePath = InSavePath + "/";
			ImportPayload.FileName = FolderName + "_" + DialogueLabel + "_PressDialogue";
			ImportPayload.URL = CurrentPrimaryDialogue.PressURL;
			ImportPayload.CsvArrayTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;

			DialogueDataPtr->AddNewArrayByTag(ImportPayload.CsvArrayTypeTag);
			OnPayLoadReadyForImport(ImportPayload);
		}
		if(!CurrentPrimaryDialogue.ResponseURL.IsEmpty())
		{
			FString LineString = "L" + FString::FromInt(CurrentPrimaryDialogue.Line);
			FString DialogueLabel = InDialogueLabel + LineString;
				
			FLGCsvInfoImportPayload ImportPayload;
			ImportPayload.DialogueStructID = InDialogueDataID;
			ImportPayload.DialogueLabel = DialogueLabel;
			ImportPayload.Caller = this;
			ImportPayload.FolderName = "ResponseDialogue";
			ImportPayload.FilePath = InSavePath + "/";
			ImportPayload.FileName = FolderName + "_" + DialogueLabel + "_ResponseDialogue";
			ImportPayload.URL = CurrentPrimaryDialogue.PressURL;
			ImportPayload.CsvArrayTypeTag = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;

			DialogueDataPtr->AddNewArrayByTag(ImportPayload.CsvArrayTypeTag);
			OnPayLoadReadyForImport(ImportPayload);
		}
	}
}

bool USI_DialogueDataAsset::StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType)
{
	return InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
}

FArrayProperty* USI_DialogueDataAsset::GetArrayPropertyByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueDataID)
{
	FSI_DialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueData) {return nullptr;}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByTag(InGameplayTag);
	if(!DialogueArrayPtr) {return nullptr;}
	
	return DialogueArrayPtr->GetArrayProperty();
}

void* USI_DialogueDataAsset::GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag, const FGuid& InDialogueDataID, bool bReturnUScriptContainer)
{
	FSI_DialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueData) {return Super::GetDialogueStructArrayByTag(InGameplayTag, InDialogueDataID);}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByTag(InGameplayTag);
	if(!DialogueArrayPtr) {return Super::GetDialogueStructArrayByTag(InGameplayTag, InDialogueDataID);}
	
	TArray<FSI_PrimaryDialogue>* PrimaryDialogueArray = GetDialogueArrayFromStruct<FSI_PrimaryDialogueArray, FSI_PrimaryDialogue>(DialogueArrayPtr);
	if(PrimaryDialogueArray)
	{
		return PrimaryDialogueArray;
	}
	TArray<FSI_CorrectedDialogue>* CorrectedDialogueArray = GetDialogueArrayFromStruct<FSI_CorrectedDialogueArray, FSI_CorrectedDialogue>(DialogueArrayPtr);
	if(CorrectedDialogueArray)
	{
		return CorrectedDialogueArray;
	}
	TArray<FSI_DefaultResponse>* DefaultResponseArray = GetDialogueArrayFromStruct<FSI_DefaultResponseArray, FSI_DefaultResponse>(DialogueArrayPtr);
	if(DefaultResponseArray)
	{
		return DefaultResponseArray;
	}
	TArray<FSI_PressDialogue>* PressDialogueArray = GetDialogueArrayFromStruct<FSI_PressDialogueArray, FSI_PressDialogue>(DialogueArrayPtr);
	if(PressDialogueArray)
	{
		return PressDialogueArray;
	}
	TArray<FSI_ResponseDialogue>* ResponseDialogueArray = GetDialogueArrayFromStruct<FSI_ResponseDialogueArray, FSI_ResponseDialogue>(DialogueArrayPtr);
	if(ResponseDialogueArray)
	{
		return ResponseDialogueArray;
	}

	return Super::GetDialogueStructArrayByTag(InGameplayTag, InDialogueDataID);
}

FSI_DialogueArrayData* USI_DialogueDataAsset::GetDialogueDataByID(const FGuid& InDialogueDataID)
{
	for (FSI_CaseDialogue& CurrentCase : CaseDialogue)
	{
		for (FSI_PartDialogue& CurrentPart : CurrentCase.PartDialogue)
		{
			FSI_DialogueArrayData& DialogueArrayData = CurrentPart.DialogueData;

			if(InDialogueDataID == DialogueArrayData.DialogueDataID)
			{
				return &DialogueArrayData;
			}
		}
	}
	return nullptr;
}

FLGDialogueArray* USI_DialogueDataAsset::GetDialogueStructArrayByTagAndID(const FGameplayTag& InStructTypeTag, const FGuid& InDialogueDataID)
{
	FSI_DialogueArrayData* DialogueArrayData = GetDialogueDataByID(InDialogueDataID);
	if(DialogueArrayData && DialogueArrayData->DialogueDataID == InDialogueDataID)
	{
		return DialogueArrayData->GetDialogueArrayByTag(InStructTypeTag);
	}
	return nullptr;
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
