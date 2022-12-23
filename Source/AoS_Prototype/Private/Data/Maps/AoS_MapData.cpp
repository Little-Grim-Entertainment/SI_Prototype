// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Maps/AoS_MapData.h"

#include "Audio/AoS_MusicManager.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Data/Media/AoS_VideoDataAsset.h"


void UAoS_MapData::PlayLevelBackgroundMusic(UAoS_MusicManager* InMusicManager)
{
	if (!IsValid(InMusicManager)) {return;}
	
	if (BackgroundMusicSettings.bHasIntro)
	{
		InMusicManager->PlayBackgroundMusicLoopWithIntro(BackgroundMusicSettings);
	}
	else
	{
		InMusicManager->PlayBackgroundMusic(BackgroundMusicSettings);
	}
}

void UAoS_MapData::SetIntroVideo(UAoS_VideoDataAsset* InIntroVideo)
{
	IntroVideo = InIntroVideo;
	IntroVideo->bIsOpeningMedia = true;
}

void UAoS_MapData::ClearIntroVideo()
{
	IntroVideo = nullptr;
}

UAoS_VideoDataAsset* UAoS_MapData::GetIntroVideo() const
{
	return IntroVideo;
}

bool UAoS_MapData::HasIntroVideo() const
{
	return IsValid(IntroVideo);
}

bool UAoS_MapData::IntroVideoHasPlayed() const
{
	if (!IsValid(IntroVideo)){return false;}

	return IntroVideo->GetMediaHasPlayed();
}

void UAoS_MapData::SetOutroVideo(UAoS_VideoDataAsset* InOutroVideo)
{
	OutroVideo = InOutroVideo;
	OutroVideo->bIsOpeningMedia = false;
}

void UAoS_MapData::ClearOutroVideo()
{
	OutroVideo = nullptr;
}

UAoS_VideoDataAsset* UAoS_MapData::GetOutroVideo() const
{
	return OutroVideo;
}

bool UAoS_MapData::HasOutroVideo() const
{
	return IsValid(OutroVideo);
}

bool UAoS_MapData::OutroVideoHasPlayed() const
{
	if (!IsValid(OutroVideo)){return false;}

	return OutroVideo->GetMediaHasPlayed();
}

void UAoS_MapData::SetIntroCinematic(UAoS_CinematicDataAsset* InIntroCinematic)
{
	IntroCinematic = InIntroCinematic;
	IntroCinematic->bIsOpeningMedia = true;
}

void UAoS_MapData::ClearIntroCinematic()
{
	IntroCinematic = nullptr;
}

UAoS_CinematicDataAsset* UAoS_MapData::GetIntroCinematic() const
{
	return IntroCinematic;
}

bool UAoS_MapData::HasIntroCinematic() const
{
	return IsValid(IntroCinematic);
}

bool UAoS_MapData::IntroCinematicHasPlayed() const
{
	if (!IsValid(IntroCinematic)){return false;}

	return IntroCinematic->GetMediaHasPlayed();
}

void UAoS_MapData::SetOutroCinematic(UAoS_CinematicDataAsset* InOutroCinematic)
{
	OutroCinematic = InOutroCinematic;
	IntroCinematic->bIsOpeningMedia = false;
}

void UAoS_MapData::ClearOutroCinematic()
{
	OutroCinematic = nullptr;
}

UAoS_CinematicDataAsset* UAoS_MapData::GetOutroCinematic() const
{
	return OutroCinematic;
}

bool UAoS_MapData::HasOutroCinematic() const
{
	return IsValid(OutroCinematic);
}

bool UAoS_MapData::OutroCinematicHasPlayed() const
{
	if (!IsValid(OutroCinematic)){return false;}

	return OutroCinematic->GetMediaHasPlayed();
}

void UAoS_MapData::SetStreamingLevelRef(ULevelStreaming* StreamingLevelToSet)
{
	StreamingLevelRef = StreamingLevelToSet;
}
