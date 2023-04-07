// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"
#include "GameModes/AoS_GameMode.h"

UAoS_GameInstance::UAoS_GameInstance()
{	
	GameMode = nullptr;
}

void UAoS_GameInstance::Init()
{
	Super::Init();
	
	OnGameInstanceInit.Broadcast();
}

AAoS_GameMode* UAoS_GameInstance::GetGameMode()
{
	return Cast<AAoS_GameMode>(GetWorld()->GetAuthGameMode());
}
