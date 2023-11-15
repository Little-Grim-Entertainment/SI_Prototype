// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LGDialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ULGDialogueDataAsset::UpdateDialogue_Internal()
{
	UpdateDialogue();
}

void ULGDialogueDataAsset::UpdateDialogue()
{
	for(const FLGDialogueURL& CurrentURL : DialogueURLs)
	{
		FString FilePath = UKismetSystemLibrary::GetProjectSavedDirectory();
		FilePath.Append(FolderPath + "/" + CsvName + ".csv");

		FOnImportComplete OnImportCompleteDelegate;

		FLGCsvInfoImportPayload ImportPayload;
		ImportPayload.Caller(this);
		ImportPayload.FileName = CsvName;
		ImportPayload.FilePath = FilePath;
		ImportPayload.URL = CurrentURL.URL;
		ImportPayload.OnImportCompleteDelegate = OnImportCompleteDelegate;
		
		ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(ImportPayload);
	}
}