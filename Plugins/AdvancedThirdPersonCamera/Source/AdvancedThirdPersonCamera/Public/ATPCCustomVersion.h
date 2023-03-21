// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Guid.h"

// Custom serialization version for all packages containing Advanced Third Person Camera dependent asset types
struct ADVANCEDTHIRDPERSONCAMERA_API FATPCCustomVersion
{
	enum Type
	{
		// Before any version changes were made in the plugin
		BeforeCustomVersionWasAdded = 0,

		NewInterpolationTypes,

		// -----<new versions can be added above this line>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1
	};

	// The GUID for this custom version number
	static const FGuid GUID;

private:
	FATPCCustomVersion() {}
};