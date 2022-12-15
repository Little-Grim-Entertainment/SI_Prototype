// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_LocalPlayerSubsystem.h"

#include "AoS_GameInstance.h"

void UAoS_LocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
	GameInstance->OnGameModeBeginPlay.AddDynamic(this, &ThisClass::OnGameModeBeginPlay);
}

void UAoS_LocalPlayerSubsystem::OnGameModeBeginPlay()
{
	
}

void UAoS_LocalPlayerSubsystem::OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode)
{
	
}
