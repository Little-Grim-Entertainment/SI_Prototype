// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "Data/Characters/SI_CharacterData.h"
#include "DataTableEditorUtils.h"
#include "LGDialogueTypes.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/SavePackage.h"

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
			if(!CurrentPart.DialogueData.DialogueArrayPtrs.IsEmpty())
			{
				CurrentPart.DialogueData.DialogueArrayPtrs.Empty();
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
			
				CurrentPart.DialogueData.AddNewArrayByTag(CurrentURL.DialogueStructType, ImportPayload);
				OnPayLoadReadyForImport(ImportPayload);
			}
		}
	}
}

void USI_DialogueDataAsset::OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath, const FString& InDialogueLabel, FGuid& InDialogueDataID, FGuid& InDialogueArrayID)
{
	FSI_DialogueArrayData* DialogueDataPtr = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueDataPtr) {return;}

	FLGDialogueArray* DialogueArrayPtr = DialogueDataPtr->GetDialogueArrayByID(InDialogueArrayID);
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

			DialogueDataPtr->AddNewArrayByTag(ImportPayload.CsvArrayTypeTag, ImportPayload);
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

			DialogueDataPtr->AddNewArrayByTag(ImportPayload.CsvArrayTypeTag, ImportPayload);
			OnPayLoadReadyForImport(ImportPayload);
		}
	}
}

bool USI_DialogueDataAsset::StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType)
{
	return InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
}

UScriptStruct* USI_DialogueDataAsset::GetStructContainerByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FSI_DialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueData) {return nullptr;}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByID(InDialogueArrayID);
	if(!DialogueArrayPtr) {return nullptr;}
	
	return DialogueArrayPtr->GetStructContainer();
}

UScriptStruct* USI_DialogueDataAsset::GetStructTypeByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FSI_DialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueData) {return nullptr;}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByID(InDialogueArrayID);
	if(!DialogueArrayPtr) {return nullptr;}

	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		FSI_PrimaryDialogueArray* PrimaryDialogueArray = static_cast<FSI_PrimaryDialogueArray*>(DialogueArrayPtr);
		if(PrimaryDialogueArray)
		{
			return FSI_PrimaryDialogue::StaticStruct();
		}
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		FSI_CorrectedDialogueArray* CorrectedDialogueArray = static_cast<FSI_CorrectedDialogueArray*>(DialogueArrayPtr);;
		if(CorrectedDialogueArray)
		{
			return FSI_CorrectedDialogue::StaticStruct();
		}
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		FSI_DefaultResponseArray* DefaultResponseArray = static_cast<FSI_DefaultResponseArray*>(DialogueArrayPtr);;
		if(DefaultResponseArray)
		{
			return FSI_DefaultResponse::StaticStruct();
		}
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		FSI_PressDialogueArray* PressDialogueArray = static_cast<FSI_PressDialogueArray*>(DialogueArrayPtr);;
		if(PressDialogueArray)
		{
			return FSI_PressDialogue::StaticStruct();
		}
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		FSI_ResponseDialogueArray* ResponseDialogueArray = static_cast<FSI_ResponseDialogueArray*>(DialogueArrayPtr);;
		if(ResponseDialogueArray)
		{
			return FSI_ResponseDialogue::StaticStruct();
		}
	}
	return nullptr;
}

void* USI_DialogueDataAsset::GetDialogueStructArrayByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FSI_DialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueData) {return Super::GetDialogueStructArrayByIDs(InDialogueDataID, InDialogueArrayID);}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByID(InDialogueArrayID);
	if(!DialogueArrayPtr) {return Super::GetDialogueStructArrayByIDs(InDialogueDataID, InDialogueArrayID);}
	
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

	return Super::GetDialogueStructArrayByIDs(InDialogueDataID, InDialogueArrayID);
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

FLGDialogueArray* USI_DialogueDataAsset::GetDialogueArrayStructByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FSI_DialogueArrayData* DialogueArrayData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueArrayData || DialogueArrayData->DialogueDataID != InDialogueDataID) {return nullptr;}

	return DialogueArrayData->GetDialogueArrayByID(InDialogueArrayID);
}

FName USI_DialogueDataAsset::GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag)
{
	FString PropertyName = GetStructTypeNameByTag(InGameplayTag).ToString();
	PropertyName.Append("Array");

	return  FName(PropertyName);
}

FName USI_DialogueDataAsset::GetStructTypeNameByTag(const FGameplayTag& InGameplayTag)
{
	FString TagString = InGameplayTag.ToString();
	
	int32 StartingIndex;
	TagString.FindLastChar(TEXT('.'), StartingIndex);

	if(StartingIndex == INDEX_NONE) {return Super::GetStructTypeNameByTag(InGameplayTag);}
	
	return FName(TagString.RightChop(StartingIndex + 1));
}

UDataTable* USI_DialogueDataAsset::GenerateNewDataTable(UScriptStruct* InStructPtr,  FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	FGuid DialogueDataGuidPtr = InCallbackInfo.DialogueStructID;
	FGuid DialogueArrayGuidPtr = InCallbackInfo.DialogueArrayID;
	
	FString PackagePath = "/Game/SI/Data/Dialogue/" + InCallbackInfo.FolderName + "/" + InCallbackInfo.FileName;
	UPackage* Package = CreatePackage(*PackagePath);
	Package->FullyLoad();

	EObjectFlags Flags = RF_Public | RF_Standalone;

	UDataTable* NewDataTable = NewObject<UDataTable>(Package->GetOutermost(), UDataTable::StaticClass(), *InCallbackInfo.FileName, Flags);
	NewDataTable->RowStruct = GetStructTypeByIDs(DialogueDataGuidPtr, DialogueArrayGuidPtr);

	InitializeDialogueDataTableByIDs(NewDataTable, DialogueDataGuidPtr, DialogueArrayGuidPtr);

	FAssetRegistryModule::AssetCreated(NewDataTable);
	NewDataTable->MarkPackageDirty();

	FSavePackageArgs SavePackageArgs;
	SavePackageArgs.TopLevelFlags = Flags;
	SavePackageArgs.SaveFlags = SAVE_NoError;
	
	FString PackageName = FPackageName::LongPackageNameToFilename(PackagePath, FPackageName::GetAssetPackageExtension());
	UPackage::SavePackage(Package, NewDataTable, *PackageName, SavePackageArgs);

	return NewDataTable;
}

void USI_DialogueDataAsset::UpdateDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr)
{
	FString FileName = "DT_" + InCallbackInfo.FileName;

	FString FilePath = UKismetSystemLibrary::GetProjectContentDirectory();
	FilePath.Append("/SI/Data/Dialogue/");
	FilePath.Append(InCallbackInfo.FolderName + "/");
	FilePath.Append(FileName);
	
	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, *FilePath);
	if(!IsValid(DataTable))
	{
		DataTable = GenerateNewDataTable(InStructPtr, InCallbackInfo);
		if(!IsValid(DataTable))
		{
			UE_LOG(LogSI_Dialogue, Warning, TEXT("Unable to generate new %s type data table."), *GetStructTypeNameByTag(InCallbackInfo.CsvArrayTypeTag).ToString());
			return;
		}
	}
}

void USI_DialogueDataAsset::InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FSI_DialogueArrayData* DialogueDataPtr = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueDataPtr) {return;}

	FLGDialogueArray* DialogueArray = DialogueDataPtr->GetDialogueArrayByID(InDialogueArrayID);
	if(!DialogueArray) {return;}
	
	DialogueArray->InitializeDialogueDataTable(InDataTable);
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
