#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(SI_Editor, Log, All);

class FSI_EditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
    static FORCEINLINE FSI_EditorModule& Get()
    {
        return FModuleManager::GetModuleChecked<FSI_EditorModule>("SI_Editor");
    }
};
