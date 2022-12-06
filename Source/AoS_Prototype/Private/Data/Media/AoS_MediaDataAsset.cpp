// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Media/AoS_MediaDataAsset.h"

bool UAoS_MediaDataAsset::GetMediaIsPlaying() const
{
	return bIsPlaying;
}

bool UAoS_MediaDataAsset::GetMediaHasPlayed() const
{
	return bHasPlayed;
}

bool UAoS_MediaDataAsset::GetMediaWasSkipped() const
{
	return bWasSkipped;
}

void UAoS_MediaDataAsset::StartMedia()
{
}

void UAoS_MediaDataAsset::SkipMedia()
{
}

void UAoS_MediaDataAsset::ResetMediaDefaults()
{
	bIsPlaying = false;
	bHasPlayed = false;
	bWasSkipped = false;	
}
