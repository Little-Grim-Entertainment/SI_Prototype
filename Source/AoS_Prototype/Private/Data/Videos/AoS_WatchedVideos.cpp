// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Videos/AoS_WatchedVideos.h"

void UAoS_WatchedVideos::AddToWatchedVideos(UAoS_VideoDataAsset* InVideoToAdd)
{
	if (!InVideoToAdd) {return;}
	
	WatchedVideos.AddUnique(InVideoToAdd);
}

TArray<UAoS_VideoDataAsset*>& UAoS_WatchedVideos::GetWatchedVideos()
{
	return WatchedVideos;
}
