// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_VideoDataAsset.h"


UAoS_VideoDataAsset* UAoS_MapData::GetOpeningVideo() const
{
	return OpeningVideo;
}

bool UAoS_MapData::HasOpeningVideo() const
{
	return IsValid(OpeningVideo);
}

bool UAoS_MapData::OpeningVideoHasPlayed() const
{
	if (!IsValid(OpeningVideo)){return false;}

	return OpeningVideo->GetMediaHasPlayed();
}

void UAoS_MapData::SetStreamingLevelRef(ULevelStreaming* StreamingLevelToSet)
{
	StreamingLevelRef = StreamingLevelToSet;
}
