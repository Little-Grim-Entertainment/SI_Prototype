// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_Objective.h"

#include "AoS_GameInstance.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Data/Media/AoS_WatchedMedia.h"

UAoS_Objective::UAoS_Objective()
{
	bIsComplete = false;
	bIsActive = false;
}

void UAoS_Objective::ResetObjective()
{
	bIsComplete = false;
	bIsActive = false;
	ResetMediaLevelAssignments();		
}

void UAoS_Objective::SetObjectiveComplete(bool bObjectiveCompleted)
{
	bIsComplete = bObjectiveCompleted;
	ClearMediaLevelAssignments();
}

void UAoS_Objective::SetObjectiveIsActive(bool bObjectiveIsActive)
{
	bIsActive = bObjectiveIsActive;
	if (bIsActive)
	{
		SetMediaLevelAssignments();
	}
	else
	{
		ClearMediaLevelAssignments();
	}
}

void UAoS_Objective::SetMediaLevelAssignments()
{
	for (const FLevelMediaAssignment CurrentMediaAssignment : LevelMediaAssignments)
	{
		if (CurrentMediaAssignment.bHasVideos)
		{
			if (CurrentMediaAssignment.IntroVideo)
			{
				CurrentMediaAssignment.AssociatedLevel->SetIntroVideo(CurrentMediaAssignment.IntroVideo);
			}
			if (CurrentMediaAssignment.OutroVideo)
			{
				CurrentMediaAssignment.AssociatedLevel->SetOutroVideo(CurrentMediaAssignment.OutroVideo);
			}
		}
		else if (CurrentMediaAssignment.bHasCinematics)
		{
			if (CurrentMediaAssignment.IntroCinematic)
			{
				CurrentMediaAssignment.AssociatedLevel->SetIntroCinematic(CurrentMediaAssignment.IntroCinematic);
			}
			if (CurrentMediaAssignment.OutroCinematic)
			{
				CurrentMediaAssignment.AssociatedLevel->SetOutroCinematic(CurrentMediaAssignment.OutroCinematic);
			}
		}
	}
}

void UAoS_Objective::ClearMediaLevelAssignments()
{
	for (const FLevelMediaAssignment CurrentMediaAssignment : LevelMediaAssignments)
	{
		if (CurrentMediaAssignment.bHasVideos)
		{
			CurrentMediaAssignment.AssociatedLevel->ClearIntroVideo();
			CurrentMediaAssignment.AssociatedLevel->ClearOutroVideo();
		}
		else if (CurrentMediaAssignment.bHasCinematics)
		{
			CurrentMediaAssignment.AssociatedLevel->ClearIntroCinematic();
			CurrentMediaAssignment.AssociatedLevel->ClearOutroCinematic();
		}
	}
}

void UAoS_Objective::ResetMediaLevelAssignments()
{
	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	
	for (const FLevelMediaAssignment CurrentMediaAssignment : LevelMediaAssignments)
	{
		if (CurrentMediaAssignment.bHasVideos)
		{
			if (CurrentMediaAssignment.IntroVideo)
			{
				CurrentMediaAssignment.IntroVideo->ResetMediaDefaults();
				if (IsValid(GameInstance) && GameInstance->WatchedMediaData)
				{
					GameInstance->WatchedMediaData->RemoveFromWatchedVideos(CurrentMediaAssignment.IntroVideo);
				}
			}
			if (CurrentMediaAssignment.OutroVideo)
			{
				CurrentMediaAssignment.OutroVideo->ResetMediaDefaults();
				if (IsValid(GameInstance) && GameInstance->WatchedMediaData)
				{
					GameInstance->WatchedMediaData->RemoveFromWatchedVideos(CurrentMediaAssignment.OutroVideo);
				}
			}
		}
		else if (CurrentMediaAssignment.bHasCinematics)
		{
			if (CurrentMediaAssignment.IntroCinematic)
			{
				CurrentMediaAssignment.IntroCinematic->ResetMediaDefaults();
				if (IsValid(GameInstance) && GameInstance->WatchedMediaData)
				{
					GameInstance->WatchedMediaData->RemoveFromWatchedCinematics(CurrentMediaAssignment.IntroCinematic);
				}
			}
			if (CurrentMediaAssignment.OutroCinematic)
			{
				CurrentMediaAssignment.OutroCinematic->ResetMediaDefaults();
				if (IsValid(GameInstance) && GameInstance->WatchedMediaData)
				{
					GameInstance->WatchedMediaData->RemoveFromWatchedCinematics(CurrentMediaAssignment.OutroCinematic);
				}
			}
		}
	}
}

