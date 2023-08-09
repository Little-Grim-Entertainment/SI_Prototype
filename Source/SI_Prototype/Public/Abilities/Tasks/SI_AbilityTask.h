// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "LG_DebugMacros.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SI_AbilityTask.generated.h"

/**
 * 
 */

using namespace SI_NativeGameplayTagLibrary;

DECLARE_LOG_CATEGORY_EXTERN(LogSI_AbilityTask, Log, All);

UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask : public UAbilityTask
{
	GENERATED_BODY()
};
