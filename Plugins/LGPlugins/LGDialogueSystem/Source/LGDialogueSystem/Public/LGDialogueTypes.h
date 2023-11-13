// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LGDialogueTypes.generated.h"

USTRUCT()
struct LGDIALOGUESYSTEM_API FLGDialogueURL
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString URL_Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString URL;
};