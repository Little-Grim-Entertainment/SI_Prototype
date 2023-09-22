// Copyright 2023, PROTOWLF, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#define PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS 1

DECLARE_LOG_CATEGORY_EXTERN(LogProtoAnimatedText, Log, All);

class FProtoAnimatedTextModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
