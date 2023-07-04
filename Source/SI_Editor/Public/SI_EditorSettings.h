// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SI_EditorSettings.generated.h"


UCLASS(Config = EditorPerProjectUserSettings, defaultconfig)
class SI_EDITOR_API USI_EditorSettings : public UObject
{
	GENERATED_BODY()

public:

	/* Should we skip all in game Media (Cinematics/Videos/etc)? */
	UPROPERTY(EditAnywhere, Config, Category = Settings)
	bool bSkipPIEMedia = false;
	
};
