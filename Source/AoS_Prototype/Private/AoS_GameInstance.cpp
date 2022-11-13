// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"

#include "Characters/AoS_Character.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "Characters/AoS_Nick.h"
#include "GameFramework/PlayerStart.h"

// Subsystems
#include "UI/AoS_UIManager.h"
#include "Data/Cases/AoS_CaseManager.h"
#include "Levels/AoS_LevelManager.h"
#include "World/AoS_WorldManager.h"

#include "Data/Maps/AoS_MapData.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

UAoS_GameInstance::UAoS_GameInstance()
{	
	bIsInMenu = false;
}

void UAoS_GameInstance::Init()
{
	Super::Init();
	
	CaseManager = GetSubsystem<UAoS_CaseManager>();
	UIManager = GetSubsystem<UAoS_UIManager>();
	LevelManager = GetSubsystem<UAoS_LevelManager>();
	WorldManager = GetSubsystem<UAoS_WorldManager>();

	LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::UAoS_GameInstance::OnLevelFinishLoad);
	
	OnSubsystemBindingsComplete.Broadcast();
	OnGameInstanceInit.Broadcast();
}

// ToDo: Maybe take this out of Game Instance at some point
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
	}
	
	if (!AoS_PlayerController)
	{
		AoS_PlayerController = Cast<AAoS_PlayerController>(GetFirstLocalPlayerController());
	}

	if (AoS_PlayerController)
	{
		AoS_PlayerController->Possess(NickSpadeCharacter);
		
		if (LevelManager->GetCurrentMapType() == EMapType::MT_Menu)
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
}

// ToDo this should eventually go in the Gizbo Manager
void UAoS_GameInstance::SpawnGizbo()
{
	if (!CDA_Gizbo) {return;}
	if (!CDA_Gizbo->CharacterClass){return;}
	
	if (const APlayerStart* PlayerStart = GetPlayerStart())
	{
		FVector GizboLocation = PlayerStart->GetActorLocation();

		// ToDo: @Liam we should probably create a scene component on Nick's blueprint that will act as a location pointer where Gizbo will spawn and try to get to if told to come back to Nick.
		// Offset behind Nick, rather than spawning in the same spot
		GizboLocation.X -= 100;
		GizboLocation.Y += 100;
		GizboLocation.Z -= 50;
		
		if (!GizboCharacter)
		{
			const FActorSpawnParameters PlayerSpawnParameters;
			GizboCharacter = GetWorld()->SpawnActor<AAoS_Gizbo>(CDA_Gizbo->CharacterClass, GizboLocation, PlayerStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			GizboCharacter->SetActorLocation(GizboLocation);
			GizboCharacter->SetActorRotation(PlayerStart->GetActorRotation());
		}
	}

	/*
	if (!AoS_GizboController)
	{
		AoS_GizboController = Cast<AAoS_GizboController>(GetFirstLocalPlayerController());
	}
	*/

	if (AoS_GizboController)
	{
		AoS_GizboController->Possess(GizboCharacter);
	}
}

EPlayerMode UAoS_GameInstance::GetPlayerMode() const
{
	return PlayerMode;
}

AAoS_PlayerController* UAoS_GameInstance::GetAOSPlayerController()
{
	return AoS_PlayerController;
}

AAoS_GizboController* UAoS_GameInstance::GetAOSGizboController()
{
	return AoS_GizboController;
}

void UAoS_GameInstance::SetPlayerMode(EPlayerMode InPlayerMode)
{
	if(InPlayerMode == PlayerMode)
	{
		return;
	}
	
	PlayerMode = InPlayerMode;
	OnPlayerModeChanged.Broadcast(InPlayerMode);
}

void UAoS_GameInstance::OnLevelFinishLoad(UAoS_MapData* LoadedLevel,  bool bShouldFade)
{
	SpawnPlayer();
	SpawnGizbo();
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
