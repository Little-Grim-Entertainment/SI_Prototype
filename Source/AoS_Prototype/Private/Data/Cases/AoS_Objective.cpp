// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cases/AoS_Objective.h"

#include "AoS_GameInstance.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "AoS_Types.h"
#include "Levels/AoS_LevelManager.h"
#include "Media/AoS_MediaManager.h"

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
	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager)) {return;}
	
	for (const FLevelMediaAssignment CurrentMediaAssignment : LevelMediaAssignments)
	{
		FAoS_MapState& CurrentMapState = LevelManager->GetMapStateByTag(CurrentMediaAssignment.AssociatedLevelTag);
		if  (!CurrentMapState.IsStateValid()) {continue;}
		
		if (CurrentMediaAssignment.bHasVideos)
		{
			if (IsValid(CurrentMediaAssignment.IntroVideo))
			{
				CurrentMapState.LoadIntroMedia(CurrentMediaAssignment.IntroVideo);
			}
			if (IsValid(CurrentMediaAssignment.OutroVideo))
			{
				CurrentMapState.LoadOutroMedia(CurrentMediaAssignment.OutroVideo);
			}
		}
		else if (CurrentMediaAssignment.bHasCinematics)
		{
			if (IsValid(CurrentMediaAssignment.IntroCinematic))
			{
				CurrentMapState.LoadIntroMedia(CurrentMediaAssignment.IntroCinematic);
			}
			if (IsValid(CurrentMediaAssignment.OutroCinematic))
			{
				CurrentMapState.LoadOutroMedia(CurrentMediaAssignment.OutroCinematic);
			}
		}
	}
}

void UAoS_Objective::ClearMediaLevelAssignments()
{
	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager)) {return;}
	
	for (const FLevelMediaAssignment CurrentMediaAssignment : LevelMediaAssignments)
	{
		FAoS_MapState& CurrentMapState = LevelManager->GetMapStateByTag(CurrentMediaAssignment.AssociatedLevelTag);

		CurrentMapState.UnLoadIntroMedia();
		CurrentMapState.UnLoadOutroMedia();
	}
}

void UAoS_Objective::ResetMediaLevelAssignments()
{
	UAoS_MediaManager* MediaManager = GetWorld()->GetSubsystem<UAoS_MediaManager>();
	if (!IsValid(MediaManager)) {return;}
	
	for (const FLevelMediaAssignment CurrentMediaAssignment : LevelMediaAssignments)
	{
		if (CurrentMediaAssignment.bHasVideos)
		{
			if (IsValid(CurrentMediaAssignment.IntroVideo))
			{
				MediaManager->RemoveFromWatchedVideos(CurrentMediaAssignment.IntroVideo);
			}
			if (IsValid(CurrentMediaAssignment.OutroVideo))
			{
				MediaManager->RemoveFromWatchedVideos(CurrentMediaAssignment.OutroVideo);
			}
		}
		else if (CurrentMediaAssignment.bHasCinematics)
		{
			if (IsValid(CurrentMediaAssignment.IntroCinematic))
			{
				MediaManager->RemoveFromWatchedCinematics(CurrentMediaAssignment.IntroCinematic);
			}
			if (IsValid(CurrentMediaAssignment.OutroCinematic))
			{
				MediaManager->RemoveFromWatchedCinematics(CurrentMediaAssignment.OutroCinematic);
			}
		}
	}
}

