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

	if (GizboStartTag == "")
	{
		GizboStartTag = "Gizbo_DefaultSpawn";
	}
	
	if (const APlayerStart* GizboStart = GameInstance->GetGameMode()->GetPlayerStart(GizboStartTag))
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

	//TODO: Check / modify this if update to NPCController does not work as intended
	if (!AoS_GizboController && GizboCharacter)
	{
		AoS_GizboController = Cast<AAoS_GizboController>(GizboCharacter->GetController());
	}

	if (AoS_GizboController)
	{
		AoS_GizboController->Possess(GizboCharacter);
	}
}

void UAoS_GizboManager::SetGizboStartTag(FString InStartTag)
{
	GizboStartTag = InStartTag;
}

void UAoS_GizboManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	SpawnGizbo();
}
