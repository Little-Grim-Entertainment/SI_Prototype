// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Videos/AoS_VideoDataAsset.h"

#include "MediaPlayer.h"

bool UAoS_VideoDataAsset::GetVideoIsPlaying() const
{
	return bIsPlaying;
}

bool UAoS_VideoDataAsset::GetVideoHasPlayed() const
{
	return bHasPlayed;
}

bool UAoS_VideoDataAsset::GetVideoWasSkipped() const
{
	return bWasSkipped;
}

void UAoS_VideoDataAsset::StartVideo()
{
	if (bIsPlaying) {return;}
	MediaPlayer->OnEndReached.AddDynamic(this, &ThisClass::OnVideoEnd);
	bIsPlaying = true;
	bHasPlayed = false;
	bWasSkipped = false;
	OnVideoStarted.Broadcast();
}

void UAoS_VideoDataAsset::SkipVideo()
{
	if (!bIsPlaying) {return;}
	bIsPlaying = false;
	bHasPlayed = false;
	bWasSkipped = true;
	
	MediaPlayer->Close();
			
	OnVideoSkipped.Broadcast();
	
	ClearDelegates();
}

void UAoS_VideoDataAsset::ResetVideoDefaults()
{
	bIsPlaying = false;
	bHasPlayed = false;
	bWasSkipped = false;
}

void UAoS_VideoDataAsset::OnVideoEnd()
{
	bIsPlaying = false;
	bHasPlayed = true;
	bWasSkipped = false;	
	OnVideoEnded.Broadcast();

	ClearDelegates();
}

void UAoS_VideoDataAsset::ClearDelegates()
{
	MediaPlayer->OnMediaOpened.Clear();
	MediaPlayer->OnEndReached.Clear();
	MediaPlayer->OnMediaClosed.Clear();

	OnVideoStarted.Clear();
	OnVideoSkipped.Clear();
	OnVideoEnded.Clear();
}

