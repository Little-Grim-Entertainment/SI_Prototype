// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/UnrealEdEngine.h"
#include "SI_UnrealEdEngine.generated.h"

/**
 * 
 */
UCLASS()
class SI_EDITOR_API USI_UnrealEdEngine : public UUnrealEdEngine
{
	GENERATED_BODY()

public:

	/* Override to give more control over PIE */
	virtual FString BuildPlayWorldURL(const TCHAR* MapName, bool bSpectatorMode = false, FString AdditionalURLOptions = FString()) override;

};
