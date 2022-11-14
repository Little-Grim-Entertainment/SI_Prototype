// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_GameInstance.h"

void UAoS_GameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnGameInstanceInit.AddDynamic(this, &ThisClass::OnGameInstanceInit);
}

void UAoS_GameInstanceSubsystem::OnGameInstanceInit()
{
	GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
}

void UAoS_GameInstanceSubsystem::OnPlayerModeChanged(EPlayerMode NewPlayerMode)
{
	
}
