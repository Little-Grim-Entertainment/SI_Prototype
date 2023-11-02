// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_GizboManager.h"

#include "SI_GameInstance.h"
#include "Characters/SI_Character.h"
#include "Characters/SI_Gizbo.h"
#include "Data/Characters/SI_CharacterData.h"
#include "GameFramework/PlayerStart.h"
#include "GameModes/SI_GameMode.h"
#include "SI_GameplayTagManager.h"

DEFINE_LOG_CATEGORY(LogSI_GizboManager);

void USI_GizboManager::SpawnGizbo()
{
	if (!GameInstance->GetGameMode()->GizboCDA)
		{UE_LOG(LogSI_GizboManager, Error, TEXT("GizboCDA is null unable to spawn gizbo!"));	return;}
	
	if (!GameInstance->GetGameMode()->GizboCDA->CharacterClass)
		{UE_LOG(LogSI_GizboManager, Error, TEXT("GizboCDA->CharacterClass is null unable to spawn gizbo!"));return;}

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
	if(GizboCharacter)
	{
		GizboAbilitySystemComponent = GizboCharacter->GetSIAbilitySystemComponent();
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

void USI_GizboManager::ShowGizbo(bool bShouldHide)
{
	if (!IsValid(GizboCharacter))
		{UE_LOG(LogSI_GizboManager, Error, TEXT("GizboCharacter is null unable to show gizbo!")); return;}
	
	GizboCharacter->SetActorHiddenInGame(bShouldHide);
}

void USI_GizboManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{
	Super::OnGameplayTagAdded(InAddedTag);

	if(SITagManager->HasParentTag(InAddedTag, SITag_Behavior))
	{
		SITagManager->ReplaceTagWithSameParent(InAddedTag, SITag_Behavior);
		return;
	}
}

void USI_GizboManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();

	SpawnGizbo();
}
