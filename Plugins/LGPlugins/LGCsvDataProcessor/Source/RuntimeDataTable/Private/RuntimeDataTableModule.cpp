// Copyright Jared Therriault 2019, 2022

#include "RuntimeDataTableModule.h"

#include "RuntimeDataTableProjectSettings.h"

#include "Misc/CoreDelegates.h"
#include "UnrealEngine.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FRuntimeDataTableModule, RuntimeDataTable);

void FRuntimeDataTableModule::StartupModule()
{
	UE_LOG(LogRuntimeDataTable, Log, TEXT("Module Startup"));

	FCoreDelegates::OnFEngineLoopInitComplete.AddRaw(this, &FRuntimeDataTableModule::OnFEngineLoopInitComplete);
}

void FRuntimeDataTableModule::ShutdownModule()
{	
	UnregisterProjectSettings();
	
	UE_LOG(LogRuntimeDataTable, Log, TEXT("Module Shutdown"));
}

void FRuntimeDataTableModule::RegisterProjectSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		const TSharedPtr<ISettingsSection> ProjectSettingsSectionPtr = SettingsModule->RegisterSettings(
		   "Project", "Plugins", "Runtime DataTable",
		   NSLOCTEXT("RuntimeDataTable", "RuntimeDataTableSettingsCategoryDisplayName", "Runtime DataTable"),
		   NSLOCTEXT("RuntimeDataTable", "RuntimeDataTableSettingsDescription",
					 "Configure the Runtime DataTable user settings"),
		   GetMutableDefault<URuntimeDataTableProjectSettings>());
	}
}

void FRuntimeDataTableModule::UnregisterProjectSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Runtime DataTable");
	}
}

void FRuntimeDataTableModule::Print(FString InMessage, const ELogType InLogType)
{
	const URuntimeDataTableProjectSettings* ProjectSettings = GetDefault<URuntimeDataTableProjectSettings>();
	check(ProjectSettings);

	const int32 Limit = ProjectSettings->LogCharacterLimit;
	if (Limit > -1 && InMessage.Len() > Limit)
	{
		InMessage.LeftInline(Limit);
	}
	
	if (GEngine)
	{
		switch (InLogType)
		{
		case ELogType::Display:
			if (ProjectSettings->bPrintDisplayMessagesToScreen)
			{
				const FString Message = "Info: " + InMessage;
				GEngine->AddOnScreenDebugMessage(
					INDEX_NONE, ProjectSettings->DisplayMessagesOnScreenLifetime, FColor::White, Message);
			}
			break;

		case ELogType::Warning:
			if (ProjectSettings->bPrintWarningMessagesToScreen)
			{
				const FString Message = "Warning: " + InMessage;
				GEngine->AddOnScreenDebugMessage(
					INDEX_NONE, ProjectSettings->WarningMessagesOnScreenLifetime, FColor::Yellow, Message);
			}
			break;

		case ELogType::Error:
			if (ProjectSettings->bPrintErrorMessagesToScreen)
			{
				const FString Message = "Error: " + InMessage;
				GEngine->AddOnScreenDebugMessage(
					INDEX_NONE, ProjectSettings->ErrorMessagesOnScreenLifetime, FColor::Red, Message);
			}
			break;

		default:
			break;
		}
	}
	

	if (InLogType == ELogType::Display)
	{
		FRuntimeDataTableModule::PrintToLog(InMessage);
	}
	else if (InLogType == ELogType::Warning)
	{
		FRuntimeDataTableModule::PrintWarningToLog(InMessage);
	}
	else if (InLogType == ELogType::Error)
	{
		FRuntimeDataTableModule::PrintErrorToLog(InMessage);
	}
}

void FRuntimeDataTableModule::OnFEngineLoopInitComplete()
{
	RegisterProjectSettings();
}

void FRuntimeDataTableModule::PrintToLog(const FString& LogMessage)
{
	UE_LOG(LogRuntimeDataTable, Log, TEXT("%s"), *LogMessage);
}

void FRuntimeDataTableModule::PrintWarningToLog(const FString& LogMessage)
{
	UE_LOG(LogRuntimeDataTable, Warning, TEXT("%s"), *LogMessage);
}

void FRuntimeDataTableModule::PrintErrorToLog(const FString& LogMessage)
{
	UE_LOG(LogRuntimeDataTable, Error, TEXT("%s"), *LogMessage);
}
