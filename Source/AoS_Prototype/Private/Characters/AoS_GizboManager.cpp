// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_GizboManager.h"

#include "AoS_GameInstance.h"
#include "Characters/AoS_Character.h"
#include "Characters/AoS_Gizbo.h"
#include "Controllers/AoS_GizboController.h"
#include "Data/Characters/AoS_CharacterData.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/AoS_GameMode.h"


void UAoS_GizboManager::SpawnGizbo()
{
	if (!GameInstance->GetGameMode()->GizboCDA) {return;}
	if (!GameInstance->GetGameMode()->GizboCDA->CharacterClass){return;}
	
	if (const APlayerStart* GizboStart = GameInstance->GetGameMode()->GetPlayerStart("GizboSpawn"))
	{
		FVector GizboLocation = FVector(GizboStart->GetActorLocation().X, GizboStart->GetActorLocation().Y, GizboStart->GetActorLocation().Z - 50);
		
		if (!GizboCharacter)
		{
			const FActorSpawnParameters PlayerSpawnParameters;
			GizboCharacter = GetWorld()->SpawnActor<AAoS_Gizbo>(GameInstance->GetGameMode()->GizboCDA->CharacterClass, GizboLocation, GizboStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			GizboCharacter->SetActorLocation(GizboLocation);
			GizboCharacter->SetActorRotation(GizboStart->GetActorRotation());
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
