// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"

#include "Characters/AoS_Character.h"
#include "Characters/AoS_CharacterData.h"
#include "Characters/AoS_Nick.h"
#include "GameFramework/PlayerStart.h"

// Subsystems
#include "UI/AoS_UIManager.h"
#include "Cases/AoS_CaseManager.h"
#include "Levels/AoS_LevelManager.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

UAoS_GameInstance::UAoS_GameInstance()
{
	bIsInMenu = false;
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
	if (!CDA_NickSpade) {return;}
	if (!CDA_NickSpade->CharacterClass){return;}
	
	if (const APlayerStart* PlayerStart = GetPlayerStart())
	{
		if (!NickSpadeCharacter)
		{
			const FActorSpawnParameters PlayerSpawnParameters;
			NickSpadeCharacter = GetWorld()->SpawnActor<AAoS_Nick>(CDA_NickSpade->CharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			NickSpadeCharacter->SetActorLocation(PlayerStart->GetActorLocation());
			NickSpadeCharacter->SetActorRotation(PlayerStart->GetActorRotation());
		}
		bIsInMenu = false;
	}
	else
	{
		bIsInMenu = true;
	}

	GetWorld()->GetFirstPlayerController()->Possess(NickSpadeCharacter);
}

EPlayerMode UAoS_GameInstance::GetPlayerMode() const
{
	return PlayerMode;
}

AAoS_PlayerController* UAoS_GameInstance::GetAOSPlayerController()
{
	return AoS_PlayerController;
}

void UAoS_GameInstance::SetPlayerMode(EPlayerMode InPlayerMode)
{
	PlayerMode = InPlayerMode;
	OnPlayerModeChanged.Broadcast(InPlayerMode);
}

void UAoS_GameInstance::SetupLevelBindings()
{
	LevelManager->OnBeginLevelLoad.AddDynamic(this, &UAoS_GameInstance::OnLevelBeginLoad);
	LevelManager->OnLevelLoaded.AddDynamic(this, &UAoS_GameInstance::OnLevelFinishLoad);
	LevelManager->OnLevelUnloaded.AddDynamic(this, &UAoS_GameInstance::OnLevelFinishUnload);
}

void UAoS_GameInstance::SetupUIBindings()
{
	
}

void UAoS_GameInstance::SetupCaseBindings()
{
	
}

void UAoS_GameInstance::OnLevelBeginLoad(ULevelStreaming* LoadingLevel)
{
	UIManager->DisplayLoadingScreen(true);
}

void UAoS_GameInstance::OnLevelFinishLoad(ULevelStreaming* LoadedLevel)
{
	if (!AoS_PlayerController)
	{
		AoS_PlayerController = Cast<AAoS_PlayerController>(GetFirstLocalPlayerController());
	}
	SpawnPlayer();
	UIManager->DisplayLoadingScreen(false);
	if (bIsInMenu)
	{
		AoS_PlayerController->bShowMouseCursor = true;
		AoS_PlayerController->SetInputMode(FInputModeUIOnly());
	}
	else
	{
		AoS_PlayerController->bShowMouseCursor = false;
		AoS_PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void UAoS_GameInstance::OnLevelFinishUnload(ULevelStreaming* UnloadedLevel)
{
	
}

void UAoS_GameInstance::Init()
{
	Super::Init();
	
	CaseManager = GetSubsystem<UAoS_CaseManager>();
	UIManager = GetSubsystem<UAoS_UIManager>();
	LevelManager = GetSubsystem<UAoS_LevelManager>();
	if(LevelManager)
	{
		SetupLevelBindings();
	}
	
}

APlayerStart* UAoS_GameInstance::GetPlayerStart() const
{
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);

	for (AActor* CurrentActor : PlayerStartActors)
	{
		if (APlayerStart* PlayerStart = Cast<APlayerStart>(CurrentActor))
		{
			return PlayerStart;
		}
	}
	return nullptr;
}
