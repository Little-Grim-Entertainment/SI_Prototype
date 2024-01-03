// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_UpdateDialogueUtilityWidget.h"
#include "LGBlueprintFunctionLibrary.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/SavePackage.h"

DEFINE_LOG_CATEGORY(LogCsvDataProcessor);

void USI_UpdateDialogueUtilityWidget::UpdateDialogue()
{
	UpdateDefaultDialogue();
	UpdateBubbleDialogue();
	UpdateDefaultDialogue();
}

void USI_UpdateDialogueUtilityWidget::UpdateDefaultDialogue()
{
	/*FLGDialogueArrayData* DialogueDataPtr = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueDataPtr) {return;}

	FLGDialogueArray* DialogueArrayPtr = DialogueDataPtr->GetDialogueArrayByID(InDialogueArrayID);
	FSI_PrimaryDialogueArray* PrimaryDialogueArrayPtr = static_cast<FSI_PrimaryDialogueArray*>(DialogueArrayPtr);
	if(!PrimaryDialogueArrayPtr) {return;}
	
	for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : PrimaryDialogueArrayPtr->PrimaryDialogueArray)
	{
		FString FileName = InFileName;
		FileName.Append("L" + FString::FromInt(CurrentPrimaryDialogue.Line));
		
		if(!CurrentPrimaryDialogue.PressURL.IsEmpty())
		{
			FString FilePath = InSavePath + "PressDialogue/";

			FLGDialogueURL DialogueURL;
			DialogueURL.URL = CurrentPrimaryDialogue.PressURL;
			DialogueURL.DialogueStructType = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
			
			BeginCsvImport(FilePath, DialogueURL, FileName);
		}
		if(!CurrentPrimaryDialogue.ResponseURL.IsEmpty())
		{
			FString FilePath = InSavePath + "ResponseDialogue/";

			FLGDialogueURL DialogueURL;
			DialogueURL.URL = CurrentPrimaryDialogue.ResponseURL;
			DialogueURL.DialogueStructType = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
			
			BeginCsvImport(FilePath, DialogueURL, FileName);
		}
	}*/
}

void USI_UpdateDialogueUtilityWidget::UpdateBubbleDialogue()
{
}

void USI_UpdateDialogueUtilityWidget::UpdateCaseDialogue()
{
}

void USI_UpdateDialogueUtilityWidget::OnRequestCheckForEmbeddedCsv_Implementation(const FGameplayTag& InStructType, const FString& InSavePath, const FString& InFileName, FGuid& InDialogueDataID, FGuid& InDialogueArrayID)
{
	FLGDialogueArrayData* DialogueDataPtr = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueDataPtr) {return;}

	FLGDialogueArray* DialogueArrayPtr = DialogueDataPtr->GetDialogueArrayByID(InDialogueArrayID);
	FSI_PrimaryDialogueArray* PrimaryDialogueArrayPtr = static_cast<FSI_PrimaryDialogueArray*>(DialogueArrayPtr);
	if(!PrimaryDialogueArrayPtr) {return;}
	
	for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : PrimaryDialogueArrayPtr->PrimaryDialogueArray)
	{
		FString FileName = InFileName;
		FileName.Append("L" + FString::FromInt(CurrentPrimaryDialogue.Line));
		
		if(!CurrentPrimaryDialogue.PressURL.IsEmpty())
		{
			FString FilePath = InSavePath + "PressDialogue/";
			
			FString DialogueURL = CurrentPrimaryDialogue.PressURL;
			FGameplayTag DialogueStructType = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
			
			BeginCsvImport(FilePath, DialogueURL, DialogueStructType, FileName);
		}
		if(!CurrentPrimaryDialogue.ResponseURL.IsEmpty())
		{
			FString FilePath = InSavePath + "ResponseDialogue/";

			FString DialogueURL = CurrentPrimaryDialogue.ResponseURL;
			FGameplayTag DialogueStructType = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
			
			BeginCsvImport(FilePath, DialogueURL, DialogueStructType, FileName);
		}
	}
}

bool USI_UpdateDialogueUtilityWidget::StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType)
{
	return InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
}

UScriptStruct* USI_UpdateDialogueUtilityWidget::GetStructContainerByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FLGDialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueData) {return nullptr;}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByID(InDialogueArrayID);
	if(!DialogueArrayPtr) {return nullptr;}
	
	return DialogueArrayPtr->GetStructContainer();
}

UScriptStruct* USI_UpdateDialogueUtilityWidget::GetStructTypeByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FLGDialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
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

void* USI_UpdateDialogueUtilityWidget::GetDialogueStructArrayByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{ 
	FLGDialogueArrayData* DialogueData = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueData) {return nullptr;}

	FLGDialogueArray* DialogueArrayPtr = DialogueData->GetDialogueArrayByID(InDialogueArrayID);
	if(!DialogueArrayPtr) {return nullptr;}
	
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

	return nullptr;
}

FName USI_UpdateDialogueUtilityWidget::GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag)
{
	FString PropertyName = GetStructTypeNameByTag(InGameplayTag).ToString();
	PropertyName.Append("Array");

	return  FName(PropertyName);
}

FName USI_UpdateDialogueUtilityWidget::GetStructTypeNameByTag(const FGameplayTag& InGameplayTag)
{
	return FName(ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(InGameplayTag));
}

FLGDialogueArrayData* USI_UpdateDialogueUtilityWidget::GetDialogueDataByID(const FGuid& InDialogueDataID)
{
	for (FLGDialogueArrayData* CurrentDialogueArrayData : DialogueArrayData)
	{
		if(CurrentDialogueArrayData->DialogueDataID == InDialogueDataID)
		{
			return CurrentDialogueArrayData;
		}
	}
	
	return nullptr;
}

FLGDialogueArray* USI_UpdateDialogueUtilityWidget::GetDialogueArrayStructByIDs(const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FLGDialogueArrayData* CurrentDialogueArrayData = GetDialogueDataByID(InDialogueDataID);
	if(!CurrentDialogueArrayData || CurrentDialogueArrayData->DialogueDataID != InDialogueDataID) {return nullptr;}

	return CurrentDialogueArrayData->GetDialogueArrayByID(InDialogueArrayID);
}

void USI_UpdateDialogueUtilityWidget::UpdateDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr)
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
			UE_LOG(LogCsvDataProcessor, Error, TEXT("Unable to generate new %s type data table."), *GetStructTypeNameByTag(InCallbackInfo.CsvArrayTypeTag).ToString());
			return;
		}
		return;
	}

	UE_LOG(LogCsvDataProcessor, Warning, TEXT("Updating Data Table: %s."), *GetNameSafe(DataTable));
	UpdateDataTableRows(DataTable, InCallbackInfo);
}

void USI_UpdateDialogueUtilityWidget::UpdateDataTableRows(UDataTable* InDataTable, FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	FLGDialogueArrayData* DialogueData = GetDialogueDataByID(InCallbackInfo.DialogueStructID);
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

UDataTable* USI_UpdateDialogueUtilityWidget::GenerateNewDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	const FGuid DialogueDataGuidPtr = InCallbackInfo.DialogueStructID;
	const FGuid DialogueArrayGuidPtr = InCallbackInfo.DialogueArrayID;

	UPackage* Package = CreatePackage(*InPackagePath);
	Package->FullyLoad();

	const EObjectFlags Flags = RF_Public | RF_Standalone;

	const FString FileName = "DT_" + InCallbackInfo.FileName;

	UDataTable* NewDataTable = NewObject<UDataTable>(Package->GetOutermost(), UDataTable::StaticClass(), *FileName, Flags);
	if(!IsValid(NewDataTable)) {UE_LOG(LogCsvDataProcessor, Error, TEXT("Unable to create new data table object for file: %s."), *InCallbackInfo.FileName); return nullptr;}
	
	NewDataTable->RowStruct = GetStructTypeByIDs(DialogueDataGuidPtr, DialogueArrayGuidPtr);

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
		UE_LOG(LogCsvDataProcessor, Error, TEXT("Unable to save new data table: %s."), *PackageName);
		return nullptr;
	}

	UE_LOG(LogCsvDataProcessor, Warning, TEXT("Successfully saved new data table: %s."), *PackageName);
	return NewDataTable;
}

void USI_UpdateDialogueUtilityWidget::BeginCsvImport(const FString& InFilePath, const FString& InUrl, const FGameplayTag& InStructType, const FString& InFileName)
{
	FLGCsvInfoImportPayload ImportPayload;
	ImportPayload.Caller = this;
	ImportPayload.FilePath = InFilePath;
	ImportPayload.FileName = InFileName;
	ImportPayload.URL = InUrl;
	ImportPayload.CsvArrayTypeTag = InStructType;

	FLGDialogueArrayData* NewDialogueArrayData = new FLGDialogueArrayData();
	NewDialogueArrayData->AddNewArrayByTag(InStructType, ImportPayload);
	DialogueArrayData.Add(NewDialogueArrayData);
	
	FRDTGetStringDelegate CallbackDelegate;
	CallbackDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USI_UpdateDialogueUtilityWidget, OnSheetStructsDownloaded));
		
	ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(ImportPayload, CallbackDelegate);
}

void USI_UpdateDialogueUtilityWidget::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo)
{
	const FGuid& DialogueDataGuid = InCallbackInfo.DialogueStructID;
	const FGuid& DialogueArrayGuid = InCallbackInfo.DialogueArrayID;
	
	const FGameplayTag& CsvArrayType = InCallbackInfo.CsvArrayTypeTag;
	const FName& PropertyName = GetStructPropertyNameByTag(CsvArrayType);
	void* DialogueStructArray = GetDialogueStructArrayByIDs(DialogueDataGuid, DialogueArrayGuid);
	
	ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(InCallbackInfo, DialogueStructArray, GetStructContainerByIDs(DialogueDataGuid, DialogueArrayGuid), PropertyName);
}

void USI_UpdateDialogueUtilityWidget::InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FLGDialogueArrayData* DialogueDataPtr = GetDialogueDataByID(InDialogueDataID);
	if(!DialogueDataPtr) {return;}

	FLGDialogueArray* DialogueArray = DialogueDataPtr->GetDialogueArrayByID(InDialogueArrayID);
	if(!DialogueArray) {return;}
	
	DialogueArray->InitializeDialogueDataTable(InDataTable);
}
