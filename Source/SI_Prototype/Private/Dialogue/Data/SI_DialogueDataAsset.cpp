// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "LGBlueprintFunctionLibrary.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "LGDialogueTypes.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Cases/Data/SI_PartData.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/SavePackage.h"

void USI_DialogueDataAsset::InitializeDialogueLabels(const ESI_MainDialogueTypes& InMainDialogueType)
{
	switch (InMainDialogueType)
	{
		case MD_CaseDialogue:
		{
			for(FSI_CaseDialogueData& CurrentCase : CaseDialogue)
			{
				FString DialogueLabel = "InvalidCase";
				FString CaseNameNoSpace = CurrentCase.GetCaseNameNoSpace();

				DialogueLabel = CaseNameNoSpace;
				DialogueLabel.Append("_");

				for (FSI_PartDialogueData& CurrentPart : CurrentCase.PartDialogue)
				{
					const USI_PartData* PartData = CurrentPart.PartReference;
					if(!IsValid(PartData)) {continue;}
					
					DialogueLabel.Append("P" + PartData->PartNumber.ToString());
					CurrentPart.DialogueData.DialogueLabel = DialogueLabel;
				}
			}
		}
		case MD_DefaultDialogue:
		{
			DefaultDialogue.DefaultDialogueData.DialogueLabel = "DefaultDialogue";
		}
		case MD_BubbleDialogue:
		{
			DefaultBubbleDialogue.BubbleDialogueData.DialogueLabel = "";
		}
		default:
		{
			break;
		}
	}
}

void USI_DialogueDataAsset::InitializeFileNames(const ESI_MainDialogueTypes& InMainDialogueType)
{
	FolderName = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(CharacterTag);
	const FString InitialFileName = FolderName + "_";

	switch (InMainDialogueType)
	{
		case MD_CaseDialogue:
		{
			for (FSI_CaseDialogueData& CurrentCase : CaseDialogue)
			{
				for (FSI_PartDialogueData& CurrentPart : CurrentCase.PartDialogue)
				{
					FString DialogueLabel = CurrentPart.DialogueData.DialogueLabel;
					FString FileNameWithID = InitialFileName + DialogueLabel;
			
					for (FLGDialogueURL& CurrentURL : CurrentPart.DialogueURLs)
					{
						CurrentURL.FileName = FileNameWithID + "_" + GetStructTypeNameByTag(CurrentURL.DialogueStructType).ToString();
					}
				}
			}
		}
		case MD_DefaultDialogue:
		{
			FString DialogueLabel = DefaultDialogue.DefaultDialogueData.DialogueLabel;
			FString FileNameWithID = InitialFileName + DialogueLabel;
			for (FLGDialogueURL& CurrentURL : DefaultDialogue.DefaultDialogueURLs)
			{
				CurrentURL.FileName = FileNameWithID + "_" + GetStructTypeNameByTag(CurrentURL.DialogueStructType).ToString();
			}
		}
		case MD_BubbleDialogue:
		{	
			DefaultBubbleDialogue.RandomBubbleDialogueURL.FileName = InitialFileName + "Default" + GetStructTypeNameByTag(DefaultBubbleDialogue.RandomBubbleDialogueURL.DialogueStructType).ToString();
			DefaultBubbleDialogue.SeeNickBubbleDialogueURL.FileName = InitialFileName + "SeeNick" + GetStructTypeNameByTag(DefaultBubbleDialogue.RandomBubbleDialogueURL.DialogueStructType).ToString();
		}
		default:
		{
			break;
		}
	}
}

USI_DialogueDataAsset::USI_DialogueDataAsset()
{
}

void USI_DialogueDataAsset::UpdateDialogue_Internal()
{
	UpdateDefaultDialogue();
	UpdateBubbleDialogue();
	UpdateCaseDialogue();
}

void USI_DialogueDataAsset::UpdateDefaultDialogue()
{
	FSI_DialogueArrayData& DefaultDialogueArrayData = DefaultDialogue.DefaultDialogueData;
	if(!DefaultDialogueArrayData.DialogueArrayPtrs.IsEmpty())
	{
		DefaultDialogueArrayData.DialogueArrayPtrs.Empty();
	}
	if(!DefaultDialogueArrayData.DialogueArrays.IsEmpty())
	{
		DefaultDialogueArrayData.DialogueArrays.Empty();
	}
	
	for (FLGDialogueURL& CurrentURL : DefaultDialogue.DefaultDialogueURLs)
	{
		FString FilePath = UKismetSystemLibrary::GetProjectDirectory();
		FilePath.Append(FolderPath + "/");
		FilePath.Append(FolderName + "/");
		FilePath.Append("DefaultDialogue/");

		FString DialogueLabel = DefaultDialogueArrayData.DialogueLabel;
		const FGuid DialogueDataID = DefaultDialogueArrayData.DialogueDataID;
		
		FLGCsvInfoImportPayload ImportPayload;
		ImportPayload.DialogueStructID = DialogueDataID;
		ImportPayload.DialogueLabel = DialogueLabel;
		ImportPayload.Caller = this;
		ImportPayload.FolderName = FolderName;
		ImportPayload.FilePath = FilePath;
		ImportPayload.FileName = CurrentURL.FileName;
		ImportPayload.URL = CurrentURL.URL;
		ImportPayload.CsvArrayTypeTag = CurrentURL.DialogueStructType;
			
		DefaultDialogue.DefaultDialogueData.AddNewArrayByTag(CurrentURL.DialogueStructType, ImportPayload);
		OnPayLoadReadyForImport(ImportPayload);
	}
}

void USI_DialogueDataAsset::UpdateBubbleDialogue()
{
	FSI_DialogueArrayData& BubbleDialogueArrayData = DefaultBubbleDialogue.BubbleDialogueData;
	if(!BubbleDialogueArrayData.DialogueArrayPtrs.IsEmpty())
	{
		BubbleDialogueArrayData.DialogueArrayPtrs.Empty();
	}
	if(!BubbleDialogueArrayData.DialogueArrays.IsEmpty())
	{
		BubbleDialogueArrayData.DialogueArrays.Empty();
	}
	
	FString FilePath = UKismetSystemLibrary::GetProjectDirectory();
	FilePath.Append(FolderPath + "/");
	FilePath.Append(FolderName + "/");
	FilePath.Append("BubbleDialogue/");

	FLGDialogueURL DialogueURL = DefaultBubbleDialogue.RandomBubbleDialogueURL;

	FString DialogueLabel = BubbleDialogueArrayData.DialogueLabel;
	FGuid DialogueDataID = BubbleDialogueArrayData.DialogueDataID;
								
	FLGCsvInfoImportPayload RandomBubbleImportPayload;
	RandomBubbleImportPayload.DialogueStructID = DialogueDataID;
	RandomBubbleImportPayload.DialogueLabel = DialogueLabel;
	RandomBubbleImportPayload.Caller = this;
	RandomBubbleImportPayload.FolderName = FolderName;
	RandomBubbleImportPayload.FilePath = FilePath;
	RandomBubbleImportPayload.FileName = DialogueURL.FileName;
	RandomBubbleImportPayload.URL = DialogueURL.URL;
	RandomBubbleImportPayload.CsvArrayTypeTag = DialogueURL.DialogueStructType;
			
	DefaultBubbleDialogue.BubbleDialogueData.AddNewArrayByTag(DialogueURL.DialogueStructType, RandomBubbleImportPayload);
	OnPayLoadReadyForImport(RandomBubbleImportPayload);

	DialogueURL = DefaultBubbleDialogue.SeeNickBubbleDialogueURL;
	
	FLGCsvInfoImportPayload SeeNickBubbleImportPayload;
	SeeNickBubbleImportPayload.DialogueStructID = DialogueDataID;
	SeeNickBubbleImportPayload.DialogueLabel = "";
	SeeNickBubbleImportPayload.Caller = this;
	SeeNickBubbleImportPayload.FolderName = FolderName;
	SeeNickBubbleImportPayload.FilePath = FilePath;
	SeeNickBubbleImportPayload.FileName = DialogueURL.FileName;
	SeeNickBubbleImportPayload.URL = DialogueURL.URL;
	SeeNickBubbleImportPayload.CsvArrayTypeTag = DialogueURL.DialogueStructType;
			
	DefaultBubbleDialogue.BubbleDialogueData.AddNewArrayByTag(DialogueURL.DialogueStructType, SeeNickBubbleImportPayload);
	OnPayLoadReadyForImport(SeeNickBubbleImportPayload);
}

void USI_DialogueDataAsset::UpdateCaseDialogue()
{
	for (FSI_CaseDialogueData& CurrentCase : CaseDialogue)
	{
		for (FSI_PartDialogueData& CurrentPart : CurrentCase.PartDialogue)
		{
			if(!CurrentPart.DialogueData.DialogueArrayPtrs.IsEmpty())
			{
				CurrentPart.DialogueData.DialogueArrayPtrs.Empty();
			}
			if(!CurrentPart.DialogueData.DialogueArrays.IsEmpty())
			{
				CurrentPart.DialogueData.DialogueArrays.Empty();
			}
			
			for (FLGDialogueURL& CurrentURL : CurrentPart.DialogueURLs)
			{
				FString FilePath = UKismetSystemLibrary::GetProjectDirectory();
				FilePath.Append(FolderPath + "/");
				FilePath.Append(FolderName + "/");
				FilePath.Append(CurrentCase.GetCaseNameNoSpace() + "/");
				
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
			ImportPayload.FilePath = InSavePath + "PressDialogue" + "/";
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
			ImportPayload.FilePath = InSavePath + "ResponseDialogue" + "/";
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
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		FSI_BubbleDialogueArray* BubbleDialogueArray = static_cast<FSI_BubbleDialogueArray*>(DialogueArrayPtr);;
		if(BubbleDialogueArray)
		{
			return FSI_BubbleDialogue::StaticStruct();
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
	TArray<FSI_BubbleDialogue>* BubbleDialogueArray = GetDialogueArrayFromStruct<FSI_BubbleDialogueArray, FSI_BubbleDialogue>(DialogueArrayPtr);
	if(BubbleDialogueArray)
	{
		return BubbleDialogueArray;
	}

	return Super::GetDialogueStructArrayByIDs(InDialogueDataID, InDialogueArrayID);
}

FSI_DialogueArrayData* USI_DialogueDataAsset::GetDialogueDataByID(const FGuid& InDialogueDataID)
{
	FSI_DialogueArrayData& DefaultDialogueArrayData = DefaultDialogue.DefaultDialogueData;
	if(DefaultDialogueArrayData.DialogueDataID == InDialogueDataID)
	{
		return &DefaultDialogueArrayData;
	}

	FSI_DialogueArrayData& BubbleDialogueArrayData = DefaultBubbleDialogue.BubbleDialogueData;
	if(BubbleDialogueArrayData.DialogueDataID == InDialogueDataID)
	{
		return &BubbleDialogueArrayData;
	}
	
	for (FSI_CaseDialogueData& CurrentCase : CaseDialogue)
	{
		for (FSI_PartDialogueData& CurrentPart : CurrentCase.PartDialogue)
		{
			FSI_DialogueArrayData& CaseDialogueArrayData = CurrentPart.DialogueData;

			if(InDialogueDataID == CaseDialogueArrayData.DialogueDataID)
			{
				return &CaseDialogueArrayData;
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
	return FName(ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(InGameplayTag));
}

void USI_DialogueDataAsset::UpdateDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr)
{
	FString FileName = "DT_" + InCallbackInfo.FileName;
	int32 ChopIndex = InCallbackInfo.FilePath.Find("Dialogue/");
	const FString DialogueFolderPath = InCallbackInfo.FilePath.RightChop(ChopIndex + 9);
	
	FString FilePath = UKismetSystemLibrary::GetProjectContentDirectory();
	FilePath.Append("SI/Data/Dialogue/");
	FilePath.Append(DialogueFolderPath);
	FilePath.Append(FileName);

	FString PackagePath = "/Game/";
	ChopIndex = FilePath.Find("SI/");
	PackagePath.Append(FilePath.RightChop(ChopIndex));

	const FString PackageName = PackagePath + "." + FileName;

	UDataTable* DataTable = LoadObject<UDataTable>(NULL, *PackageName);
	if(!IsValid(DataTable))
	{
		DataTable = GenerateNewDataTable(InStructPtr, PackagePath, InCallbackInfo);
		if(!IsValid(DataTable))
		{
			UE_LOG(LogSI_Dialogue, Error, TEXT("Unable to generate new %s type data table."), *GetStructTypeNameByTag(InCallbackInfo.CsvArrayTypeTag).ToString());
			return;
		}
		return;
	}

	UE_LOG(LogSI_Dialogue, Warning, TEXT("Updating Data Table: %s."), *GetNameSafe(DataTable));
	UpdateDataTableRows(DataTable, InCallbackInfo);
}

void USI_DialogueDataAsset::UpdateDataTableRows(UDataTable* InDataTable, FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	FSI_DialogueArrayData* DialogueData = GetDialogueDataByID(InCallbackInfo.DialogueStructID);
	if(!DialogueData) {return;}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByID(InCallbackInfo.DialogueArrayID);
	if(!DialogueArrayPtr) {return;}

	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		UpdateDataTableStructByType<FSI_PrimaryDialogue, FSI_PrimaryDialogueArray>(InDataTable, DialogueArrayPtr);
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		UpdateDataTableStructByType<FSI_CorrectedDialogue, FSI_CorrectedDialogueArray>(InDataTable, DialogueArrayPtr);
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		UpdateDataTableStructByType<FSI_DefaultResponse, FSI_DefaultResponseArray>(InDataTable, DialogueArrayPtr);
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		UpdateDataTableStructByType<FSI_PressDialogue, FSI_PressDialogueArray>(InDataTable, DialogueArrayPtr);
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		UpdateDataTableStructByType<FSI_ResponseDialogue, FSI_ResponseDialogueArray>(InDataTable, DialogueArrayPtr);
	}
	else if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		UpdateDataTableStructByType<FSI_BubbleDialogue, FSI_BubbleDialogueArray>(InDataTable, DialogueArrayPtr);
	}

	InDataTable->PostEditChange();
}

UDataTable* USI_DialogueDataAsset::GenerateNewDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	const FGuid DialogueDataGuidPtr = InCallbackInfo.DialogueStructID;
	const FGuid DialogueArrayGuidPtr = InCallbackInfo.DialogueArrayID;

	UPackage* Package = CreatePackage(*InPackagePath);
	Package->FullyLoad();

	const EObjectFlags Flags = RF_Public | RF_Standalone;

	const FString FileName = "DT_" + InCallbackInfo.FileName;

	USI_DialogueDataTable* NewDataTable = NewObject<USI_DialogueDataTable>(Package->GetOutermost(), USI_DialogueDataTable::StaticClass(), *FileName, Flags);
	if(!IsValid(NewDataTable)) {UE_LOG(LogSI_Dialogue, Error, TEXT("Unable to create new data table object for file: %s."), *InCallbackInfo.FileName); return nullptr;}
	
	NewDataTable->RowStruct = GetStructTypeByIDs(DialogueDataGuidPtr, DialogueArrayGuidPtr);
	NewDataTable->CharacterTag = GetCharacterTag();

	FLGDialogueArray* DialogueArray = GetDialogueArrayStructByIDs(DialogueDataGuidPtr, DialogueArrayGuidPtr);
	if(DialogueArray)
	{
		DialogueArray->SetDataTable(NewDataTable);
	}

	InitializeDialogueDataTableByIDs(NewDataTable, DialogueDataGuidPtr, DialogueArrayGuidPtr);

	FAssetRegistryModule::AssetCreated(NewDataTable);
	NewDataTable->MarkPackageDirty();

	FSavePackageArgs SavePackageArgs;
	SavePackageArgs.TopLevelFlags = Flags;
	SavePackageArgs.SaveFlags = SAVE_NoError;
	
	const FString PackageName = FPackageName::LongPackageNameToFilename(InPackagePath, FPackageName::GetAssetPackageExtension());
	const bool SaveSuccess = UPackage::SavePackage(Package, NewDataTable, *PackageName, SavePackageArgs);
	if(!SaveSuccess)
	{
		UE_LOG(LogSI_Dialogue, Error, TEXT("Unable to save new data table: %s."), *PackageName);
		return nullptr;
	}

	UE_LOG(LogSI_Dialogue, Warning, TEXT("Successfully saved new data table: %s."), *PackageName);
	return NewDataTable;
}

const FGameplayTag& USI_DialogueDataAsset::GetCharacterTag()
{
	return CharacterTag;
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
		InitializeDialogueLabels(MD_CaseDialogue);
		InitializeFileNames(MD_CaseDialogue);
	}
	else if(MemberPropertyName == GET_MEMBER_NAME_CHECKED(USI_DialogueDataAsset, DefaultDialogue))
	{
		InitializeDialogueLabels(MD_DefaultDialogue);
		InitializeFileNames(MD_DefaultDialogue);
	}
	else if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(USI_DialogueDataAsset, DefaultBubbleDialogue))
	{
		InitializeDialogueLabels(MD_BubbleDialogue);
		InitializeFileNames(MD_BubbleDialogue);
	}
}
#endif
