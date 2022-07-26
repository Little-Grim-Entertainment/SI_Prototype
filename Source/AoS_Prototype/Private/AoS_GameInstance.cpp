// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"
#include "Cases/AoS_CaseManager.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

UAoS_GameInstance::UAoS_GameInstance()
{
	
}

void UAoS_GameInstance::ResetCase(FString CaseToResetName)
{
	if (CaseManager)
	{
		if (CaseToResetName == "All")
		{
			CaseManager->ResetAllCases();
		}
		else
		{
			CaseManager->ResetCase(CaseToResetName);
		}
	}
}

void UAoS_GameInstance::SpawnPlayer()
{
	if (GetWorld())
	{
		// Get player start and spawn at location
		//TArray<APlayerStart*> PlayerStarts = UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	}
}

EPlayerMode UAoS_GameInstance::GetPlayerMode() const
{
	return PlayerMode;
}

void UAoS_GameInstance::SetPlayerMode(EPlayerMode InPlayerMode)
{
	PlayerMode = InPlayerMode;
	OnPlayerModeChanged.Broadcast(InPlayerMode);
}

void UAoS_GameInstance::Init()
{
	Super::Init();

	CaseManager = GetSubsystem<UAoS_CaseManager>();
}
