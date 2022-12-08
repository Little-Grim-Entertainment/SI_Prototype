// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AoS_LevelTransition.h"

#include "Cinematics/AoS_CinematicsManager.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Levels/AoS_LevelManager.h"


void AAoS_LevelTransition::OnBeginOverlap(AAoS_Nick* InNickActor)
{
	Super::OnBeginOverlap(InNickActor);
	
}

void AAoS_LevelTransition::OnEndOverlap(AAoS_Nick* InNickActor)
{
	Super::OnEndOverlap(InNickActor);
	
}

void AAoS_LevelTransition::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);

	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (IsValid(LevelManager))
	{
		if (IsValid(OutroVideo) && (IsValid(OutroCinematic)))
		{
			// print error
			return;
		}

		UAoS_CinematicsManager* CinematicsManager = GetWorld()->GetSubsystem<UAoS_CinematicsManager>();
		if(IsValid(CinematicsManager))
		{
			if (IsValid(OutroVideo))
			{
				CinematicsManager->PlayVideo(OutroVideo);
				CinematicsManager->LoadLevelOnVideoComplete(MapToLoad, PlayerStartTag);
			}
			else if (IsValid(OutroCinematic))
			{
				CinematicsManager->PlayCinematic(OutroCinematic);
				CinematicsManager->LoadLevelOnCinematicComplete(MapToLoad, PlayerStartTag);
			}
			else
			{
				LevelManager->LoadLevel(MapToLoad, PlayerStartTag);	
			}
		}
	}
}
