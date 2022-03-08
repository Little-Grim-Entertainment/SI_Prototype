// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum ECaseType
{
	CT_None     UMETA(DisplayName = "None"),
	CT_MainStory      UMETA(DisplayName = "Main Story"),
	CT_SideCase   UMETA(DisplayName = "Side Case"),
};

USTRUCT(BlueprintType)
struct FCaseData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Case Info")
	TEnumAsByte<ECaseType> CaseType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Case Info")
	FName CaseName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Case Info")
	int TotalParts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Case Info")
	int CurrentPart = 1;
};


class AOS_PROTOTYPE_API AoS_Cases
{
public:
	AoS_Cases();
};
