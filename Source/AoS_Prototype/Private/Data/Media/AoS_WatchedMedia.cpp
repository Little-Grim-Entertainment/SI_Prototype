// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Media/AoS_WatchedMedia.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Data/Media/AoS_CinematicDataAsset.h"


void UAoS_WatchedMedia::AddToWatchedVideos(UAoS_VideoDataAsset* InVideoToAdd)
{
	if (!InVideoToAdd) {return;}
	
	WatchedVideos.AddUnique(InVideoToAdd);
}

void UAoS_WatchedMedia::AddToWatchedCinematics(UAoS_CinematicDataAsset* InCinematicToAdd)
{
	if (!InCinematicToAdd) {return;}
	
	WatchedCinematics.AddUnique(InCinematicToAdd);
}

void UAoS_WatchedMedia::RemoveFromWatchedVideos(UAoS_VideoDataAsset* InVideoToRemove)
{
	if (!InVideoToRemove) {return;}

	if (WatchedVideos.Contains(InVideoToRemove))
	{
		WatchedVideos.Remove(InVideoToRemove);
	}
}

void UAoS_WatchedMedia::RemoveFromWatchedCinematics(UAoS_CinematicDataAsset* InCinematicToRemove)
{
	if (!InCinematicToRemove) {return;}

	if (WatchedCinematics.Contains(InCinematicToRemove))
	{
		WatchedCinematics.Remove(InCinematicToRemove);
	}
}

TArray<UAoS_VideoDataAsset*>& UAoS_WatchedMedia::GetWatchedVideos()
{
	return WatchedVideos;
}

TArray<UAoS_CinematicDataAsset*>& UAoS_WatchedMedia::GetWatchedCinematics()
{
	return WatchedCinematics;
}
