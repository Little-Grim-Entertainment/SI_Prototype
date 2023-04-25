// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCustomVersion.h"

#include "Serialization/CustomVersion.h"

const FGuid FATPCCustomVersion::GUID(0xab965195, 0x45d805fc, 0xb7d7225d, 0x78ad570e);

// Register the custom version with core
FCustomVersionRegistration GRegisterAdvancedThirdPersonCameraCustomVersion(FATPCCustomVersion::GUID, FATPCCustomVersion::LatestVersion, TEXT("ATPCVer"));
