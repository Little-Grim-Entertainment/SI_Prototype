// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogATPC, Log, All);

/**
* The public interface to this module
*/
class ADVANCEDTHIRDPERSONCAMERA_API FAdvancedThirdPersonCameraModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};