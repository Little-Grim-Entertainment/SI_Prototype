#include "SI_Editor.h"
#include "ShowFlags.h"
#include "Extensions/SI_UnrealEdExtensions.h"

#define LOCTEXT_NAMESPACE "FSI_EditorModule"

DEFINE_LOG_CATEGORY(SI_Editor);
IMPLEMENT_MODULE(FSI_EditorModule, SI_Editor)

void FSI_EditorModule::StartupModule()
{
    SI_UnrealEdExtensions::InstallExtensions();
}

void FSI_EditorModule::ShutdownModule()
{
    SI_UnrealEdExtensions::RemoveExtensions();
}

#undef LOCTEXT_NAMESPACE
    
