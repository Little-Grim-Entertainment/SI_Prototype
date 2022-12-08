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

TArray<UAoS_VideoDataAsset*>& UAoS_WatchedMedia::GetWatchedVideos()
{
	return WatchedVideos;
}

TArray<UAoS_CinematicDataAsset*>& UAoS_WatchedMedia::GetWatchedCinematics()
{
	return WatchedCinematics;
}
