// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SI_AbilityTask.h"
#include "SI_AbilityTask_Gizbo_ConstructGadget.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_AbilityTask_Gizbo_ConstructGadget : public USI_AbilityTask
{
	GENERATED_BODY()

protected:
	USI_AbilityTask* CreateAbilityTask(UGameplayAbility* InOwningAbility, AActor* InActor);
	
};
