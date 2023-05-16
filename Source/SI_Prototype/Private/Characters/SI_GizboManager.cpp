// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_GizboManager.h"

#include "SI_GameInstance.h"
#include "Characters/SI_Character.h"
#include "Characters/SI_Gizbo.h"
#include "Controllers/SI_GizboController.h"
#include "Data/Characters/SI_CharacterData.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/SI_GameMode.h"


void USI_GizboManager::SpawnGizbo()
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
			GizboCharacter = GetWorld()->SpawnActor<ASI_Gizbo>(GameInstance->GetGameMode()->GizboCDA->CharacterClass, GizboLocation, GizboStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			GizboCharacter->SetActorLocation(GizboLocation);
			GizboCharacter->SetActorRotation(GizboStart->GetActorRotation());
		}
	}
	
	if (!GizboController && GizboCharacter)
	{
		GizboController = Cast<ASI_GizboController>(GizboCharacter->GetController());
	}

	if (GizboController)
	{
		GizboController->Possess(GizboCharacter);
	}
}

void USI_GizboManager::SetGizboStartTag(FString InStartTag)
{
	GizboStartTag = InStartTag;
}

ASI_Gizbo* USI_GizboManager::GetGizbo()
{
	return GizboCharacter;
}

ASI_GizboController* USI_GizboManager::GetGizboController()
{
	return GizboController;
}

void USI_GizboManager::ShowGizbo(bool bShouldHide)
{
	if (!IsValid(GizboCharacter)) {return;}
	GizboCharacter->SetActorHiddenInGame(bShouldHide);
}

void USI_GizboManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	SpawnGizbo();
}
