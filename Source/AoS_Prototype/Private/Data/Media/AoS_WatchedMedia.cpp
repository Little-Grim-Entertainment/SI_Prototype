// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Media/AoS_WatchedMedia.h"
#include "Data/Media/AoS_VideoDataAsset.h"


void UAoS_WatchedMedia::AddToWatchedVideos(UAoS_VideoDataAsset* InVideoToAdd)
{
	if (!InVideoToAdd) {return;}
	
	WatchedVideos.AddUnique(InVideoToAdd);
}

TArray<UAoS_VideoDataAsset*>& UAoS_WatchedMedia::GetWatchedVideos()
{
	return WatchedVideos;
}