// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AoS_LevelTransition.h"

#include "Cinematics/AoS_CinematicsManager.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Kismet/KismetStringLibrary.h"
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
	
	if (!IsValid(MapToLoad)){return;}

	if (IsValid(OutroVideo) && (IsValid(OutroCinematic)))
	{
		// print error
		return;
	}

	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager)) {return;}

	FString NickPlayerStartTag = LevelManager->GetCurrentMap()->GetName();
	NickPlayerStartTag = UKismetStringLibrary::Replace(NickPlayerStartTag, "DA_", "Nick_");

	UAoS_CinematicsManager* CinematicsManager = GetWorld()->GetSubsystem<UAoS_CinematicsManager>();
	if(IsValid(CinematicsManager))
	{
		if (IsValid(OutroVideo))
		{
			if (OutroVideo->bCanRepeat)
			{
				CinematicsManager->PlayVideo(OutroVideo);
				CinematicsManager->LoadLevelOnVideoComplete(MapToLoad, NickPlayerStartTag);
				return;
			}
			if (!OutroVideo->bCanRepeat && !OutroVideo->GetMediaHasPlayed())
			{
				CinematicsManager->PlayVideo(OutroVideo);
				CinematicsManager->LoadLevelOnVideoComplete(MapToLoad, NickPlayerStartTag);
				return;
			}
			LevelManager->LoadLevel(MapToLoad, NickPlayerStartTag);	
			return;
		}
		if (IsValid(OutroCinematic))
		{
			if (OutroCinematic->bCanRepeat)
			{
				CinematicsManager->PlayCinematic(OutroCinematic);
				CinematicsManager->LoadLevelOnCinematicComplete(MapToLoad, NickPlayerStartTag);
				return;
			}
			if (!OutroCinematic->bCanRepeat && !OutroCinematic->GetMediaHasPlayed())
			{
				CinematicsManager->PlayCinematic(OutroCinematic);
				CinematicsManager->LoadLevelOnCinematicComplete(MapToLoad, NickPlayerStartTag);
				return;
			}
			LevelManager->LoadLevel(MapToLoad, NickPlayerStartTag);
			return;
		}

		LevelManager->LoadLevel(MapToLoad, NickPlayerStartTag);	
	}
}
