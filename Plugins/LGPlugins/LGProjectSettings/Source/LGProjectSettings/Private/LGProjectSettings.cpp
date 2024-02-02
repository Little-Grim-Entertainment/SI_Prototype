// Copyright Epic Games, Inc. All Rights Reserved.

#include "LGProjectSettings.h"
#include "LGProjectSettingsObject.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FLGProjectSettingsModule"

void FLGProjectSettingsModule::StartupModule()
{
	if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "LG Project Settings",
			LOCTEXT("RuntimeSettingsName", "LG Project Settings"), LOCTEXT("RuntimeSettingsDescription", "Configure my setting"),
			GetMutableDefault<ULGProjectSettingsObject>());
	}
}

void FLGProjectSettingsModule::ShutdownModule()
{
	if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "LG Project Settings");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLGProjectSettingsModule, LGProjectSettings)