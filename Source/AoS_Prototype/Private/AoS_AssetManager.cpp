// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_AssetManager.h"
#include "AbilitySystemGlobals.h"

void UAoS_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	UAbilitySystemGlobals::Get().InitGlobalData();
}
