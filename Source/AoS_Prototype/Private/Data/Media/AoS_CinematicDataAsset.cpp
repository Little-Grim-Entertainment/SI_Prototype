// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Media/AoS_CinematicDataAsset.h"

#include "LevelSequencePlayer.h"

void UAoS_CinematicDataAsset::StartMedia()
{
	Super::StartMedia();

	if (bIsPlaying) {return;}

	CinematicPlayer->Play();
	
	CinematicPlayer->OnFinished.AddDynamic(this, &ThisClass::OnCinematicEnd);
	bIsPlaying = true;
	bHasPlayed = false;
	bWasSkipped = false;

}

void UAoS_CinematicDataAsset::SkipMedia()
{
	Super::SkipMedia();

	if (!bIsPlaying) {return;}
	bIsPlaying = false;
	bHasPlayed = false;
	bWasSkipped = true;
	
	CinematicPlayer->Pause();
	CinematicPlayer->Stop();
		
	ClearDelegates();
}

void UAoS_CinematicDataAsset::ClearDelegates()
{
	Super::ClearDelegates();

	CinematicPlayer->OnPlay.Clear();
	CinematicPlayer->OnFinished.Clear();
	CinematicPlayer->OnStop.Clear();
}

void UAoS_CinematicDataAsset::OnCinematicEnd()
{
	bIsPlaying = false;
	bHasPlayed = true;
	bWasSkipped = false;	

	ClearDelegates();
}
