// Fill out your copyright notice in the Description page of Project Settings.


#include "Cameras/AoS_PlayerCameraManager.h"

#include "Camera/CameraComponent.h"
#include "Characters/AoS_Nick.h"

void AAoS_PlayerCameraManager::SetPlayerCharacter(AAoS_Nick* CharacterToSet)
{
	PlayerCharacter = CharacterToSet;
}


FTransform AAoS_PlayerCameraManager::GetFollowCamTransform()
{
	const FRotator CameraRotation(0.0f, 0.0f, 0.0f);
	const FVector CameraLocation(0.0f, 0.0f, 0.0f);
	const FVector CameraScale(1.0f, 1.0f, 1.0f);
	FTransform CameraTransform(CameraRotation, CameraLocation, CameraScale);
	if (PlayerCharacter)
	{
		CameraTransform = PlayerCharacter->GetFollowCamera()->GetComponentTransform();
	}
	return CameraTransform;
}

