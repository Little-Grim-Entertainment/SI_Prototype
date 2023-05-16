// Fill out your copyright notice in the Description page of Project Settings.


#include "Cameras/SI_PlayerCameraManager.h"

#include "Camera/CameraComponent.h"
#include "Characters/SI_Nick.h"

void ASI_PlayerCameraManager::SetPlayerCharacter(ASI_Nick* CharacterToSet)
{
	PlayerCharacter = CharacterToSet;
}


FTransform ASI_PlayerCameraManager::GetFollowCamTransform()
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

