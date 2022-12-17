// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Media/AoS_VideoDataAsset.h"

#include "MediaPlayer.h"

void UAoS_VideoDataAsset::StartMedia()
{
	Super::StartMedia();

	if (bIsPlaying) {return;}
	MediaPlayer->OnEndReached.AddDynamic(this, &ThisClass::OnVideoEnd);
	bIsPlaying = true;
	bHasPlayed = false;
	bWasSkipped = false;
	OnVideoStarted.Broadcast();
}

void UAoS_VideoDataAsset::SkipMedia()
{
	Super::SkipMedia();

 	if (!bIsPlaying) {return;}
	bIsPlaying = false;
	bHasPlayed = true;
	bWasSkipped = true;
	
	MediaPlayer->Close();
			
	OnVideoSkipped.Broadcast();
	
	ClearDelegates();
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
	Super::ClearDelegates();

	MediaPlayer->OnMediaOpened.Clear();
	MediaPlayer->OnEndReached.Clear();
	MediaPlayer->OnMediaClosed.Clear();

	OnVideoStarted.Clear();
	OnVideoSkipped.Clear();
	OnVideoEnded.Clear();
}

