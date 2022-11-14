// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/AoS_WorldSubsystem.h"
#include "AoS_GameInstance.h"


void UAoS_WorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)){return;}

	GameInstance->OnPlayerModeChanged.AddDynamic(this, &ThisClass::OnPlayerModeChanged);
}

void UAoS_WorldSubsystem::OnPlayerModeChanged(EPlayerMode NewPlayerMode)
{

}
