// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_UnrealEdEngine.h"

#include "SI_EditorSettings.h"

FString USI_UnrealEdEngine::BuildPlayWorldURL(const TCHAR* MapName, bool bSpectatorMode, FString AdditionalURLOptions)
{
	FString URL = Super::BuildPlayWorldURL(MapName, bSpectatorMode, AdditionalURLOptions);

	const USI_EditorSettings* EditorSettings = GetDefault<USI_EditorSettings>();

	if (EditorSettings->bSkipPIEMedia)
	{
		URL += TEXT("?bShouldDisableMedia=1");
	}
	
	return URL;
}
