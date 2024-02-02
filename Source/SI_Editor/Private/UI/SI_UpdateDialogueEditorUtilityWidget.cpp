// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_UpdateDialogueEditorUtilityWidget.h"
#include "LGBlueprintFunctionLibrary.h"
#include "Dialogue/Data/SI_DialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GameplayTags/SI_NativeGameplayTagLibrary.h"
#include "Cases/Data/SI_PartData.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/SavePackage.h"

DEFINE_LOG_CATEGORY(LogCsvDataProcessor);

void USI_UpdateDialogueEditorUtilityWidget::UpdateDialogue()
{
	if(!IsValid(DialogueData)) {return;}
	
	UpdateDefaultDialogue();
	UpdateBubbleDialogue();
	UpdateCaseDialogue();
}

FString USI_UpdateDialogueEditorUtilityWidget::GetFilePath()
{
	FString DialogueDirectory = UKismetSystemLibrary::GetProjectDirectory();
	
	FString FilePath = UKismetSystemLibrary::GetPathName(DialogueData);
	int32 LastIndex;
	FilePath.FindLastChar('/', LastIndex);
	const int32 ChopNum = FilePath.Len() - (LastIndex + 1);
	FilePath = FilePath.LeftChop(ChopNum);

	int32 RightChopIndex = FilePath.Find("Dialogue");
	FilePath = FilePath.RightChop(RightChopIndex);

	return DialogueDirectory + FilePath;
}

FString USI_UpdateDialogueEditorUtilityWidget::GetContentPath()
{
	FString FilePath = UKismetSystemLibrary::GetPathName(DialogueData);
	int32 LastIndex;
	FilePath.FindLastChar('/', LastIndex);
	const int32 ChopNum = FilePath.Len() - (LastIndex + 1);
	FilePath = FilePath.LeftChop(ChopNum);

	return FilePath;
}

void USI_UpdateDialogueEditorUtilityWidget::UpdateDefaultDialogue()
{
	FString FilePath = GetFilePath();
	FilePath.Append("DefaultDialogue/");

	const FString CharacterName = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(DialogueData->CharacterTag);
	FString FileName = CharacterName;
	FileName.Append("_DefaultDialogue");
	
	for(FLGDialogueURL CurrentDialogueURL : DialogueData->DefaultDialogue.DefaultDialogueURLs)
	{
		BeginCsvImport(FilePath, CurrentDialogueURL, FileName);
	}
}

void USI_UpdateDialogueEditorUtilityWidget::UpdateBubbleDialogue()
{
	FString FilePath = GetFilePath();
	FilePath.Append("BubbleDialogue/");

	const FString CharacterName = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(DialogueData->CharacterTag);

	FString FileName = CharacterName;
	FileName.Append("_");
		
	FLGDialogueURL CurrentDialogueURL = DialogueData->DefaultBubbleDialogue.RandomBubbleDialogueURL;
	FString FirstFileName = FileName;
	FirstFileName.Append("RandomBubbleDialogue");
	
	BeginCsvImport(FilePath, CurrentDialogueURL, FirstFileName);

	CurrentDialogueURL = DialogueData->DefaultBubbleDialogue.SeeNickBubbleDialogueURL;
	FString SecondFileName = FileName;
	SecondFileName.Append("SeeNickBubbleDialogue");
			
	BeginCsvImport(FilePath, CurrentDialogueURL, SecondFileName);
}

void USI_UpdateDialogueEditorUtilityWidget::UpdateCaseDialogue()
{
	FString FilePath = GetFilePath();
	FilePath.Append("CaseDialogue/");

	FString ContentPath = GetContentPath();
	ContentPath.Append("CaseDialogue/");

	const FString FileName = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(DialogueData->CharacterTag);

	USI_CaseDialogueDataTable* CaseDialogueDataTable = DialogueData->CaseDialogueDataTable;
	if(!IsValid(CaseDialogueDataTable))
	{
		CaseDialogueDataTable = GenerateNewCaseDataTable(ContentPath, FileName);
		DialogueData->CaseDialogueDataTable = CaseDialogueDataTable;
		if(!IsValid(CaseDialogueDataTable))
		{
			return;
		}
	}
	
	for(FSI_CaseDialogueInfo& CurrentCaseInfo : DialogueData->CaseDialogue)
	{
		const USI_CaseData* CurrentCaseDataPtr = CurrentCaseInfo.CaseReference;
		if(!IsValid(CurrentCaseDataPtr)) {continue;}
				
		if(!IsCaseInTable(CurrentCaseDataPtr->CaseTag, CaseDialogueDataTable))
		{
			CaseDialogueDataTable->AddNewCaseToTable(CurrentCaseDataPtr);
			CaseDialogueDataTable->MarkPackageDirty();
		}

		FString NameWithCase = FileName + "_" + ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(CurrentCaseDataPtr->CaseTag);
		
		for(FSI_PartDialogueInfo& CurrentPartInfo : CurrentCaseInfo.PartDialogue)
		{
			const USI_PartData* CurrentPartDataPtr = CurrentPartInfo.PartReference;
			if(!IsValid(CurrentPartDataPtr)) {continue;}

			FString CaseName = ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(CurrentCaseDataPtr->CaseTag);
			FString PartFilePath = FilePath + CaseName + "/" + CurrentPartDataPtr->GetPartNameNoSpace() + "/";
			
			FSI_PartDialogueData* PartDialogueData;
			
			if(!IsPartInTable(CurrentCaseDataPtr->CaseTag, CurrentPartDataPtr->PartTag, CaseDialogueDataTable))
			{
				PartDialogueData = new FSI_PartDialogueData(CurrentPartDataPtr);
				AddNewPartToTable(CaseDialogueDataTable, CurrentCaseDataPtr->CaseTag, PartDialogueData);
			}
			else
			{
				PartDialogueData = GetPartDialogueDataByTag(CurrentPartDataPtr->PartTag);
			}

			if(!PartDialogueData) {continue;}
			FString NameWithPart = NameWithCase + "_" + CurrentPartDataPtr->GetPartNameTruncated();
			
			for(FLGDialogueURL CurrentDialogueURL : CurrentPartInfo.DialogueURLs)
			{
				BeginCsvImport(PartFilePath, CurrentDialogueURL, NameWithPart, PartDialogueData->DialogueDataID);
			}
		}
	}
}

USI_CaseDialogueDataTable* USI_UpdateDialogueEditorUtilityWidget::GenerateNewCaseDataTable(const FString& InPackagePath, const FString& InFileName)
{
	const FString FileName = "DT_" + InFileName + "_CaseDataTable";
	const FString FilePath = InPackagePath + FileName;
	UPackage* Package = CreatePackage(*FilePath);
	Package->FullyLoad();

	const EObjectFlags Flags = RF_Public | RF_Standalone;

	USI_CaseDialogueDataTable* NewDataTable = NewObject<USI_CaseDialogueDataTable>(Package->GetOutermost(), USI_CaseDialogueDataTable::StaticClass(), *FileName, Flags);
	if(!IsValid(NewDataTable)) {UE_LOG(LogCsvDataProcessor, Error, TEXT("Unable to create new data table object for file: %s."), *FileName); return nullptr;}
	
	FAssetRegistryModule::AssetCreated(NewDataTable);
	NewDataTable->MarkPackageDirty();

	FSavePackageArgs SavePackageArgs;
	SavePackageArgs.TopLevelFlags = Flags;
	
	const FString PackageName = FPackageName::LongPackageNameToFilename(FilePath, FPackageName::GetAssetPackageExtension());
	const bool SaveSuccess = UPackage::SavePackage(Package->GetOutermost(), NewDataTable, *PackageName, SavePackageArgs);
	if(!SaveSuccess)
	{
		UE_LOG(LogCsvDataProcessor, Error, TEXT("Unable to save new data table: %s."), *PackageName);
		return nullptr;
	}

	UE_LOG(LogCsvDataProcessor, Warning, TEXT("Successfully saved new data table: %s."), *PackageName);
	return NewDataTable;
}

void USI_UpdateDialogueEditorUtilityWidget::AddNewCaseToTable(UDataTable* InCaseDataTable, const USI_CaseData* InCaseData)
{
	const FName RowName = FName(InCaseData->CaseTag.ToString());
	const FSI_CaseDialogueData CaseDialogueData = FSI_CaseDialogueData(InCaseData);
	const FSI_CaseDialogueDataTableRow CaseDialogueDataTableRow = FSI_CaseDialogueDataTableRow(CaseDialogueData);

	InCaseDataTable->AddRow(RowName, CaseDialogueDataTableRow);
}

bool USI_UpdateDialogueEditorUtilityWidget::IsCaseInTable(const FGameplayTag& InCaseTag, const UDataTable* InCaseDialogueDataTable) const
{
	if(!IsValid(InCaseDialogueDataTable)){return false;}

	const FName CaseName = FName(*InCaseTag.ToString());

	const FSI_CaseDialogueDataTableRow* CaseRow = InCaseDialogueDataTable->FindRow<FSI_CaseDialogueDataTableRow>(CaseName, NULL);
	if(!CaseRow) {return false;}
	
	return true;
}

bool USI_UpdateDialogueEditorUtilityWidget::IsPartInTable(const FGameplayTag& InCaseTag, const FName& InPartTag, const UDataTable* InCaseDialogueDataTable) const
{
	if(!IsValid(InCaseDialogueDataTable)){return false;}

	const FName CaseName = FName(*InCaseTag.ToString());
	const FSI_CaseDialogueDataTableRow* CaseRow = InCaseDialogueDataTable->FindRow<FSI_CaseDialogueDataTableRow>(CaseName, NULL);
	if(!CaseRow) {return false;}
	
	const FSI_CaseDialogueData& CaseDialogueData = CaseRow->CaseDialogueData;
	for(const FSI_PartDialogueData CurrentPartDialogueData : CaseDialogueData.PartDialogueData)
	{
		const USI_PartData* CurrentPartData = CurrentPartDialogueData.PartReference;
		if(!IsValid(CurrentPartData)) {continue;}
		
		if(CurrentPartData->PartTag == InPartTag)
		{
			return true;
		}
	}
	
	return false;
}

void USI_UpdateDialogueEditorUtilityWidget::AddNewPartToTable(const UDataTable* InCaseDialogueDataTable, const FGameplayTag& InCaseTag, const FSI_PartDialogueData* InPartDialogueData)
{
	const FName CaseName = FName(*InCaseTag.ToString());
	FSI_CaseDialogueDataTableRow* CaseRow = InCaseDialogueDataTable->FindRow<FSI_CaseDialogueDataTableRow>(CaseName, NULL);
	if(!CaseRow) {return;}

	FSI_CaseDialogueData& CaseDialogueData = CaseRow->CaseDialogueData;
	CaseDialogueData.PartDialogueData.Add(*InPartDialogueData);
}

FSI_PartDialogueData* USI_UpdateDialogueEditorUtilityWidget::GetPartDialogueDataByID(const FGuid& InPartID)
{
	if(!InPartID.IsValid()) {return nullptr;}
	
	const UDataTable* CaseDialogueDataTable = DialogueData->CaseDialogueDataTable;
	if(!IsValid(CaseDialogueDataTable)) {return nullptr;}
	
	for(const FSI_CaseDialogueInfo& CurrentCaseInfo : DialogueData->CaseDialogue)
	{
		const USI_CaseData* CurrentCaseDataPtr = CurrentCaseInfo.CaseReference;
		if(!IsValid(CurrentCaseDataPtr)) {continue;}

		const FName CaseName = FName(*CurrentCaseDataPtr->CaseTag.ToString());
		FSI_CaseDialogueDataTableRow* CaseRow = CaseDialogueDataTable->FindRow<FSI_CaseDialogueDataTableRow>(CaseName, NULL);
		if(!CaseRow) {continue;}

		FSI_CaseDialogueData& CaseDialogueData = CaseRow->CaseDialogueData;
		for(FSI_PartDialogueData& CurrentPartDialogueData : CaseDialogueData.PartDialogueData)
		{			
			if(CurrentPartDialogueData.DialogueDataID == InPartID)
			{
				return &CurrentPartDialogueData;
			}
		}
	}

	return nullptr;	
}

FSI_PartDialogueData* USI_UpdateDialogueEditorUtilityWidget::GetPartDialogueDataByTag(const FName& InPartTag)
{
	if(!InPartTag.IsValid()) {return nullptr;}
	
	const UDataTable* CaseDialogueDataTable = DialogueData->CaseDialogueDataTable;
	if(!IsValid(CaseDialogueDataTable)) {return nullptr;}
	
	for(const FSI_CaseDialogueInfo& CurrentCaseInfo : DialogueData->CaseDialogue)
	{
		const USI_CaseData* CurrentCaseDataPtr = CurrentCaseInfo.CaseReference;
		if(!IsValid(CurrentCaseDataPtr)) {continue;}

		const FName CaseName = FName(*CurrentCaseDataPtr->CaseTag.ToString());
		FSI_CaseDialogueDataTableRow* CaseRow = CaseDialogueDataTable->FindRow<FSI_CaseDialogueDataTableRow>(CaseName, NULL);
		if(!CaseRow) {continue;}

		FSI_CaseDialogueData& CaseDialogueData = CaseRow->CaseDialogueData;
		for(FSI_PartDialogueData& CurrentPartDialogueData : CaseDialogueData.PartDialogueData)
		{
			const USI_PartData* CurrentPartData = CurrentPartDialogueData.PartReference;
			if(!IsValid(CurrentPartData)) {continue;}
			
			if(CurrentPartData->PartTag == InPartTag)
			{
				return &CurrentPartDialogueData;
			}
		}
	}

	return nullptr;	
}

void USI_UpdateDialogueEditorUtilityWidget::BeginCsvImport(const FString& InFilePath, const FLGDialogueURL& InUrl, const FString& InFileName, const FGuid& InDataTableOwnerID)
{
	FSI_DialogueArrayData* NewDialogueArrayData = new FSI_DialogueArrayData();

	FSI_DialogueTag DialogueTag = ULGBlueprintFunctionLibrary::ConvertFileNameToTagName(InFileName);
	FString FileName = InFileName + "_" + ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(InUrl.DialogueStructType);
	
	FLGCsvInfoImportPayload ImportPayload;
	ImportPayload.Caller = this;
	ImportPayload.FilePath = InFilePath;
	ImportPayload.FileName = FileName;
	ImportPayload.URL = InUrl.URL;
	ImportPayload.CsvArrayTypeTag = InUrl.DialogueStructType;
	ImportPayload.DialogueTag = DialogueTag.GetName();
	ImportPayload.DialogueStructID = NewDialogueArrayData->DialogueDataID;
	ImportPayload.DataTableOwnerID = InDataTableOwnerID;

	NewDialogueArrayData->AddNewArrayByTag(InUrl.DialogueStructType, ImportPayload, DialogueTag.GetName());
	DialogueDataArray.Add(NewDialogueArrayData);
	
	FRDTGetStringDelegate CallbackDelegate;
	CallbackDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USI_UpdateDialogueEditorUtilityWidget, OnSheetStructsDownloaded));

	if(!CallbackDelegate.IsBound()) {UE_LOG(LogCsvDataProcessor, Warning, TEXT("Initial Delegate is not bound."));}
		
	ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(ImportPayload, CallbackDelegate);
}

void USI_UpdateDialogueEditorUtilityWidget::InitializedDialogueArrayTag(const FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	FLGDialogueArray* DialogueArray = GetDialogueArrayTypeByID<FLGDialogueArray>(InCallbackInfo.DialogueArrayID);
	if(!DialogueArray) {return;}

	DialogueArray->InitializeContainedDialogueTags();
}

void USI_UpdateDialogueEditorUtilityWidget::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo)
{
	const FGuid& DialogueArrayGuid = InCallbackInfo.DialogueArrayID;
	
	const FGameplayTag& CsvArrayType = InCallbackInfo.CsvArrayTypeTag;
	const FName& PropertyName = GetStructPropertyNameByTag(CsvArrayType);
	void* DialogueStructArray = GetDialogueStructArrayByID(DialogueArrayGuid);
	
	ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(InCallbackInfo, DialogueStructArray, GetStructContainerByID(DialogueArrayGuid), PropertyName);
}

void USI_UpdateDialogueEditorUtilityWidget::OnRequestCheckForEmbeddedCsv_Implementation(const FRuntimeDataTableCallbackInfo& InCallbackInfo, const FString& InSavePath)
{
	FSI_PrimaryDialogueArray* PrimaryDialogueArrayPtr = GetDialogueArrayTypeByID<FSI_PrimaryDialogueArray>(InCallbackInfo.DialogueArrayID);
	if(!PrimaryDialogueArrayPtr) {return;}

	FString FileName = InCallbackInfo.FileName;
	FileName.Append("_L");
	
	const int32 DoubleUnderscoreIndex = FileName.Find("__");
	if(DoubleUnderscoreIndex != INDEX_NONE)
	{
		FileName.RemoveAt(DoubleUnderscoreIndex);
	}
	
	for(FSI_PrimaryDialogue& CurrentPrimaryDialogue : PrimaryDialogueArrayPtr->PrimaryDialogueArray)
	{
		FString CurrentFileName = FileName;
		CurrentFileName.Append(FString::FromInt(CurrentPrimaryDialogue.Line));
		
		if(!CurrentPrimaryDialogue.PressURL.IsEmpty())
		{
			FString FilePath = InSavePath + "PressDialogue/";

			FLGDialogueURL DialogueURL;
			DialogueURL.URL = CurrentPrimaryDialogue.PressURL;
			DialogueURL.DialogueStructType = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue;
			
			BeginCsvImport(FilePath, DialogueURL, CurrentFileName, InCallbackInfo.DataTableOwnerID);
		}
		if(!CurrentPrimaryDialogue.ResponseURL.IsEmpty())
		{
			FString FilePath = InSavePath + "ResponseDialogue/";
			
			FLGDialogueURL DialogueURL;
			DialogueURL.URL = CurrentPrimaryDialogue.ResponseURL;
			DialogueURL.DialogueStructType = SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
			
			BeginCsvImport(FilePath, DialogueURL, CurrentFileName, InCallbackInfo.DataTableOwnerID);
		}
	}
}

bool USI_UpdateDialogueEditorUtilityWidget::StructTypeHasEmbeddedCsv_Implementation(const FGameplayTag& InStructType)
{
	return InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue;
}

bool USI_UpdateDialogueEditorUtilityWidget::IsEmbeddedStructType(const FGameplayTag& InStructType)
{
	return InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue || InStructType == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue;
}

UScriptStruct* USI_UpdateDialogueEditorUtilityWidget::GetStructContainerByID(const FGuid& InDialogueArrayID)
{
	FLGDialogueArray* DialogueArrayPtr = GetDialogueArrayTypeByID<FLGDialogueArray>(InDialogueArrayID);
	if(!DialogueArrayPtr) {return nullptr;}
	
	return DialogueArrayPtr->GetStructContainer();
}

UScriptStruct* USI_UpdateDialogueEditorUtilityWidget::GetStructTypeByID(const FGuid& InDialogueArrayID)
{
	FLGDialogueArray* DialogueArrayPtr = GetDialogueArrayTypeByID<FLGDialogueArray>(InDialogueArrayID);
	if(!DialogueArrayPtr) {return nullptr;}

	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		FSI_PrimaryDialogueArray* PrimaryDialogueArray = static_cast<FSI_PrimaryDialogueArray*>(DialogueArrayPtr);
		if(PrimaryDialogueArray)
		{
			return FSI_PrimaryDialogue::StaticStruct();
		}
		return nullptr;
	}
	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		FSI_CorrectedDialogueArray* CorrectedDialogueArray = static_cast<FSI_CorrectedDialogueArray*>(DialogueArrayPtr);;
		if(CorrectedDialogueArray)
		{
			return FSI_CorrectedDialogue::StaticStruct();
		}
		return nullptr;
	}
	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		FSI_DefaultResponseArray* DefaultResponseArray = static_cast<FSI_DefaultResponseArray*>(DialogueArrayPtr);;
		if(DefaultResponseArray)
		{
			return FSI_DefaultResponse::StaticStruct();
		}
		return nullptr;
	}
	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		FSI_PressDialogueArray* PressDialogueArray = static_cast<FSI_PressDialogueArray*>(DialogueArrayPtr);;
		if(PressDialogueArray)
		{
			return FSI_PressDialogue::StaticStruct();
		}
		return nullptr;
	}
	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		FSI_ResponseDialogueArray* ResponseDialogueArray = static_cast<FSI_ResponseDialogueArray*>(DialogueArrayPtr);;
		if(ResponseDialogueArray)
		{
			return FSI_ResponseDialogue::StaticStruct();
		}
		return nullptr;
	}
	if(DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		FSI_BubbleDialogueArray* BubbleDialogueArray = static_cast<FSI_BubbleDialogueArray*>(DialogueArrayPtr);;
		if(BubbleDialogueArray)
		{
			return FSI_BubbleDialogue::StaticStruct();
		}
		return nullptr;
	}
	return nullptr;
}

void* USI_UpdateDialogueEditorUtilityWidget::GetDialogueStructArrayByID(const FGuid& InDialogueArrayID)
{ 
	FLGDialogueArray* DialogueArrayPtr = GetDialogueArrayTypeByID<FLGDialogueArray>(InDialogueArrayID);
	if(!DialogueArrayPtr) {return nullptr;}
	
	TArray<FSI_PrimaryDialogue>* PrimaryDialogueArray = GetDialogueArrayFromStruct<FSI_PrimaryDialogueArray, FSI_PrimaryDialogue>(DialogueArrayPtr);
	if(PrimaryDialogueArray && DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PrimaryDialogue)
	{
		return PrimaryDialogueArray;
	}
	TArray<FSI_CorrectedDialogue>* CorrectedDialogueArray = GetDialogueArrayFromStruct<FSI_CorrectedDialogueArray, FSI_CorrectedDialogue>(DialogueArrayPtr);
	if(CorrectedDialogueArray && DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_CorrectedDialogue)
	{
		return CorrectedDialogueArray;
	}
	TArray<FSI_DefaultResponse>* DefaultResponseArray = GetDialogueArrayFromStruct<FSI_DefaultResponseArray, FSI_DefaultResponse>(DialogueArrayPtr);
	if(DefaultResponseArray && DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_DefaultResponse)
	{
		return DefaultResponseArray;
	}
	TArray<FSI_PressDialogue>* PressDialogueArray = GetDialogueArrayFromStruct<FSI_PressDialogueArray, FSI_PressDialogue>(DialogueArrayPtr);
	if(PressDialogueArray && DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_PressDialogue)
	{
		return PressDialogueArray;
	}
	TArray<FSI_ResponseDialogue>* ResponseDialogueArray = GetDialogueArrayFromStruct<FSI_ResponseDialogueArray, FSI_ResponseDialogue>(DialogueArrayPtr);
	if(ResponseDialogueArray && DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_ResponseDialogue)
	{
		return ResponseDialogueArray;
	}
	TArray<FSI_BubbleDialogue>* BubbleDialogueArray = GetDialogueArrayFromStruct<FSI_BubbleDialogueArray, FSI_BubbleDialogue>(DialogueArrayPtr);
	if(BubbleDialogueArray && DialogueArrayPtr->DialogueStructTypeTag == SI_NativeGameplayTagLibrary::SITag_Dialogue_Struct_BubbleDialogue)
	{
		return BubbleDialogueArray;
	}

	return nullptr;
}

FName USI_UpdateDialogueEditorUtilityWidget::GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag)
{
	FString PropertyName = GetStructTypeNameByTag(InGameplayTag).ToString();
	PropertyName.Append("Array");

	return  FName(*PropertyName);
}

FName USI_UpdateDialogueEditorUtilityWidget::GetStructTypeNameByTag(const FGameplayTag& InGameplayTag)
{
	return FName(*ULGBlueprintFunctionLibrary::GetLastValueInTagAsString(InGameplayTag));
}

void USI_UpdateDialogueEditorUtilityWidget::OnCsvProcessComplete_Implementation(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr)
{
	UpdateDialogueDataTable(InCallbackInfo, InStructPtr);
	UE_LOG(LogCsvDataProcessor, Warning, TEXT("Dilogue Asset Interaction Complete!"));
}

void USI_UpdateDialogueEditorUtilityWidget::UpdateDialogueDataTable(FRuntimeDataTableCallbackInfo& InCallbackInfo, UScriptStruct* InStructPtr)
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

	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, *PackageName);
	if(!IsValid(DataTable))
	{
		DataTable = GenerateNewDialogueDataTable(InStructPtr, PackagePath, InCallbackInfo);
		if(!IsValid(DataTable))
		{
			UE_LOG(LogCsvDataProcessor, Error, TEXT("Unable to generate new %s type data table."), *GetStructTypeNameByTag(InCallbackInfo.CsvArrayTypeTag).ToString());
			return;
		}
		return;
	}

	UE_LOG(LogCsvDataProcessor, Warning, TEXT("Updating Data Table: %s."), *GetNameSafe(DataTable));
	UpdateDialogueDataTableRows(DataTable, InCallbackInfo);
}

void USI_UpdateDialogueEditorUtilityWidget::UpdateDialogueDataTableRows(UDataTable* InDataTable, FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	FLGDialogueArray* DialogueArrayPtr = GetDialogueArrayTypeByID<FLGDialogueArray>(InCallbackInfo.DialogueArrayID);
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

UDataTable* USI_UpdateDialogueEditorUtilityWidget::GenerateNewDialogueDataTable(UScriptStruct* InStructPtr, const FString& InPackagePath, FRuntimeDataTableCallbackInfo& InCallbackInfo)
{
	const FGuid DialogueDataGuidPtr = InCallbackInfo.DialogueStructID;
	const FGuid DialogueArrayGuidPtr = InCallbackInfo.DialogueArrayID;
	const FSI_DialogueTag DialogueTag = InCallbackInfo.DialogueTag; 

	UPackage* Package = CreatePackage(*InPackagePath);
	Package->FullyLoad();

	const EObjectFlags Flags = RF_Public | RF_Standalone;

	const FString FileName = "DT_" + InCallbackInfo.FileName;

	UDataTable* NewDataTable = NewObject<UDataTable>(Package->GetOutermost(), UDataTable::StaticClass(), *FileName, Flags);
	if(!IsValid(NewDataTable)) {UE_LOG(LogCsvDataProcessor, Error, TEXT("Unable to create new data table object for file: %s."), *InCallbackInfo.FileName); return nullptr;}
	
	NewDataTable->RowStruct = GetStructTypeByID(DialogueArrayGuidPtr);

	FLGDialogueArray* DialogueArray = GetDialogueArrayTypeByID<FLGDialogueArray>(InCallbackInfo.DialogueArrayID);
	if(DialogueArray)
	{
		DialogueArray->SetDataTable(NewDataTable);
	}
	
	InitializedDialogueArrayTag(InCallbackInfo);
	InitializeDialogueDataTableByIDs(NewDataTable, DialogueDataGuidPtr, DialogueArrayGuidPtr);

	if(DialogueTag.IsCaseDialogueTag())
	{
		FSI_PartDialogueData* CasePartDialogueData = GetPartDialogueDataByID(InCallbackInfo.DataTableOwnerID);
		if(CasePartDialogueData)
		{
			CasePartDialogueData->SetDialogueDataTableByType(NewDataTable, InCallbackInfo.CsvArrayTypeTag, DialogueTag);
		}
	}
	else
	{
		DialogueData->SetDataTableByTypeAndTag(NewDataTable, InCallbackInfo.CsvArrayTypeTag, DialogueTag);
	}


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

void USI_UpdateDialogueEditorUtilityWidget::InitializeDialogueDataTableByIDs(UDataTable* InDataTable, const FGuid& InDialogueDataID, const FGuid& InDialogueArrayID)
{
	FLGDialogueArray* DialogueArray = GetDialogueArrayTypeByID<FLGDialogueArray>(InDialogueArrayID);
	if(!DialogueArray) {return;}
	
	DialogueArray->InitializeDialogueDataTable(InDataTable);
}
