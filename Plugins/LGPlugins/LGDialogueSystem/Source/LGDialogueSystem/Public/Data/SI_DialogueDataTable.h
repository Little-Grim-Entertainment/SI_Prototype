// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SI_DialogueDataTable.generated.h"

/**
 * 
 */
UCLASS()
class LGDIALOGUESYSTEM_API USI_DialogueDataTable : public UDataTable
{
	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag CharacterTag;
};
