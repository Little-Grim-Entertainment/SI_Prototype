// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "HorizonUIModule.h"

#include "HorizonUIPrivate.h"
#define LOCTEXT_NAMESPACE "FHorizonUIModule"

class FHorizonUIModule : public IHorizonUIModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};


void FHorizonUIModule::StartupModule()
{

	
}

void FHorizonUIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

}

DEFINE_LOG_CATEGORY(LogHorizonUI);

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHorizonUIModule, HorizonUI)


