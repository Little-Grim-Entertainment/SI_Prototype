// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/SI_AbilityTask_Gizbo_ConstructGadget.h"


USI_AbilityTask* USI_AbilityTask_Gizbo_ConstructGadget::CreateAbilityTask(UGameplayAbility* InOwningAbility, AActor* InActor)
{
	USI_AbilityTask* MyObj = NewAbilityTask<USI_AbilityTask>(InOwningAbility);
	//MyObj->Actor= Cast<AActor*>(InActor);
       
	return MyObj;
}