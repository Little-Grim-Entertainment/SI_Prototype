// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_AssetManager.h"
#include "AbilitySystemGlobals.h"

void USI_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	UAbilitySystemGlobals::Get().InitGlobalData();
}
