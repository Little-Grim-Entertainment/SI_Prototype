// Copyright Little Grim Entertainment LLC

#include "Extensions/SI_UnrealEdExtensions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Input/SSpinBox.h"
#include "LevelEditor.h"
#include "SI_EditorSettings.h"

FLevelEditorModule::FLevelEditorMenuExtender PIEMenuExtensions;
FDelegateHandle PIEMenuExtensionsDelegateHandle;

TArray<IConsoleObject*> ConsoleObjects;

void SI_UnrealEdExtensions::InstallExtensions()
{
	if (!GIsEditor)
	{
		return;
	}

	// load level editor module
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		PIEMenuExtensions = FLevelEditorModule::FLevelEditorMenuExtender::CreateStatic(&SI_UnrealEdExtensions::ExtendPIEMenu);
		TArray<FLevelEditorModule::FLevelEditorMenuExtender>& MenuExtenders = LevelEditorModule.GetAllLevelEditorToolbarPlayMenuExtenders();
		MenuExtenders.Add(PIEMenuExtensions);
		PIEMenuExtensionsDelegateHandle = MenuExtenders.Last().GetHandle();
	}
}

void SI_UnrealEdExtensions::RemoveExtensions()
{
	ConsoleObjects.Empty();

	if (!FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		return;
	}

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetAllLevelEditorToolbarPlayMenuExtenders().RemoveAllSwap([&](const FLevelEditorModule::FLevelEditorMenuExtender& Delegate)
	{ return Delegate.GetHandle() == PIEMenuExtensionsDelegateHandle; });
}

TSharedRef<FExtender> SI_UnrealEdExtensions::ExtendPIEMenu(const TSharedRef<FUICommandList> CommandList)
{
	TSharedPtr<FExtender> Extender = MakeShareable(new FExtender);
	Extender->AddMenuExtension("LevelEditorPlayPlayerStart", EExtensionHook::After, CommandList, FMenuExtensionDelegate::CreateStatic(&SI_UnrealEdExtensions::CreateExtendedPIEMenu));
	return Extender.ToSharedRef();
}

void SI_UnrealEdExtensions::CreateExtendedPIEMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("SpadeInvestigations", FText::FromString(TEXT("Spade Investigations")));
	{
		AddMediaToggleOptionPIEMenu(MenuBuilder);
	}
	MenuBuilder.EndSection();
}

void SI_UnrealEdExtensions::AddMediaToggleOptionPIEMenu(FMenuBuilder& MenuBuilder)
{
	FUIAction Action(
	FExecuteAction::CreateLambda([]()
	{
		USI_EditorSettings* EditorSettings = GetMutableDefault<USI_EditorSettings>();
		if (EditorSettings)
		{
			EditorSettings->bSkipPIEMedia = !EditorSettings->bSkipPIEMedia;
			EditorSettings->SaveConfig();
		}
	}),
	FCanExecuteAction(), FIsActionChecked::CreateLambda([] () -> bool
	{
		return GetDefault<USI_EditorSettings>()->bSkipPIEMedia;
	})
);
	
	MenuBuilder.AddMenuEntry(NSLOCTEXT("SI_Editor", "SkipMedia", "Skip All Media"), FText(), FSlateIcon(), Action, NAME_None, EUserInterfaceActionType::ToggleButton);
}
