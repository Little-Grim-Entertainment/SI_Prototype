// Copyright 2023 Alexander Shumeyko. All Rights Reserved.

#include "ATPCCameraModeScript.h"

#include "ATPCCameraComponent.h"

UATPCCameraModeScript::UATPCCameraModeScript()
{
	bHasK2TickImpl = GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(UATPCCameraModeScript, K2_Tick));
}

UWorld* UATPCCameraModeScript::GetWorld() const
{
	return OwningCamera != nullptr ? OwningCamera->GetWorld() : nullptr;
}

UATPCCameraComponent* UATPCCameraModeScript::GetCamera() const
{
	return OwningCamera;
}

void UATPCCameraModeScript::OnEnterCameraMode(UATPCCameraComponent* Camera)
{
	OwningCamera = Camera;
	K2_OnEnterCameraMode(OwningCamera);
}

void UATPCCameraModeScript::OnExitCameraMode()
{
	K2_OnExitCameraMode(OwningCamera);
}

void UATPCCameraModeScript::Tick(float DeltaSeconds)
{
	if (bHasK2TickImpl)
	{
		K2_Tick(OwningCamera, DeltaSeconds);
	}
}