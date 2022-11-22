// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_GizboManager.h"
#include "Characters/AoS_Character.h"
#include "Characters/AoS_Gizbo.h"
#include "Controllers/AoS_GizboController.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/AoS_GameMode.h"


void UAoS_GizboManager::SpawnGizbo()
{
	const AAoS_GameMode* GameMode = Cast<AAoS_GameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode->GizboCDA) {return;}
	if (!GameMode->GizboCDA->CharacterClass){return;}
	
	if (const APlayerStart* PlayerStart = GameMode->GetPlayerStart())
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
			GizboCharacter = GetWorld()->SpawnActor<AAoS_Gizbo>(GameMode->GizboCDA->CharacterClass, GizboLocation, PlayerStart->GetActorRotation(), PlayerSpawnParameters);
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

void UAoS_GizboManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	SpawnGizbo();
}
