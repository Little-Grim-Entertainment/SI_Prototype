// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"

// Subsystems
#include "UI/AoS_UIManager.h"
#include "Data/Cases/AoS_CaseManager.h"
#include "Levels/AoS_LevelManager.h"
#include "World/AoS_WorldManager.h"
#include "GameModes/AoS_GameMode.h"


UAoS_GameInstance::UAoS_GameInstance()
{	
	GameMode = nullptr;
}

void UAoS_GameInstance::Init()
{
	Super::Init();
	
	CaseManager = GetSubsystem<UAoS_CaseManager>();
	UIManager = GetSubsystem<UAoS_UIManager>();
	LevelManager = GetSubsystem<UAoS_LevelManager>();
	WorldManager = GetSubsystem<UAoS_WorldManager>();
	
	OnSubsystemBindingsComplete.Broadcast();
	OnGameInstanceInit.Broadcast();
}

EPlayerMode UAoS_GameInstance::GetPlayerMode() const
{
	return PlayerMode;
}

AAoS_GameMode* UAoS_GameInstance::GetGameMode() const
{
	return GameMode;
}

void UAoS_GameInstance::SetGameMode(AAoS_GameMode* InGameMode)
{
	GameMode = InGameMode;
}

void UAoS_GameInstance::SetPlayerMode(EPlayerMode InPlayerMode)
{
	if(InPlayerMode == PlayerMode){return;}
	
	PlayerMode = InPlayerMode;
	OnPlayerModeChanged.Broadcast(InPlayerMode);
}
