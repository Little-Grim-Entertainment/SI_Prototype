// Copyright 2024 Alexander Shumeyko. All Rights Reserved.

#include "ATPCLockOnTargetLocationComponent.h"

FVector UATPCLockOnTargetLocationComponent::GetTargetLocation()
{
	return GetComponentLocation();
}
