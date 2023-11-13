// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LGDialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ULGDialogueDataAsset::UpdateDialogue()
{
	for(const FLGDialogueURL& CurrentURL : DialogueURLs)
	{
		FString FilePath = UKismetSystemLibrary::GetProjectSavedDirectory();
		FilePath.Append(FolderPath + "/" + CsvName + ".csv");
		ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(CurrentURL.URL, FilePath, CsvName);
	}
}
