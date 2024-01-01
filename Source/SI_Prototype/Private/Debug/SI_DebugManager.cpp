// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/SI_DebugManager.h"
#include "GameplayTag/SI_GameplayTagManager.h"
#include "GameplayTag/SI_NativeGameplayTagLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Debug/SI_GameplayTagViewer.h"

using namespace SI_NativeGameplayTagLibrary;

USI_DebugManager::USI_DebugManager()
{
	bDebugCommandsInitialized = false;
}

void USI_DebugManager::InitializeDebugCommands(const FString& Options)
{
	if(bDebugCommandsInitialized) {return;}
	
	static const FString ShouldDisableMedia = FString("bShouldDisableMedia");
	const bool InitOptionDisableMedia = UGameplayStatics::GetIntOption(Options, ShouldDisableMedia, 0) != 0;
	CreateDebugBoolType(ShouldDisableMedia, InitOptionDisableMedia, SITag_Debug_DisableAllMedia);
	
	bDebugCommandsInitialized = true;
}

void USI_DebugManager::Deinitialize()
{
	DebugVariables.Empty();
	
	Super::Deinitialize();
}

bool USI_DebugManager::DebugCommandsHaveInitialized() const
{
	return bDebugCommandsInitialized;
}

void USI_DebugManager::CreateDebugBoolType(const FString& InDebugString, const bool bInValue,  const FGameplayTag& InAssociatedTag)
{
	static FSI_DebugBool DebugBool = FSI_DebugBool(InDebugString, bInValue);
	DebugVariables.Add(InAssociatedTag, &DebugBool);
}

FSI_DebugBool* USI_DebugManager::GetDebugBoolByTag(const FGameplayTag& InAssociatedTag)
{
	FSI_DebugVariable* DebugVariable = *DebugVariables.Find(InAssociatedTag);
	FSI_DebugBool* DebugBool = static_cast<FSI_DebugBool*>(DebugVariable);
	
	return DebugBool;
}
