// Fill out your copyright notice in the Description page of Project Settings.


#include "Media/AoS_MediaManager.h"

#include "AoS_GameInstance.h"
#include "GameplayTagContainer.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Controllers/AoS_PlayerController.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Levels/AoS_LevelManager.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "Data/Media/AoS_VideoDataAsset.h"

void UAoS_MediaManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	
}

void UAoS_MediaManager::PlayMedia(UAoS_MediaDataAsset* InMediaToPlay, FAoS_MediaSettings& InMediaSettings)
{
	UAoS_CinematicDataAsset* CinematicDataAsset = Cast<UAoS_CinematicDataAsset>(InMediaToPlay);
		
	if (IsValid(CinematicDataAsset))
	{
		if (FAoS_CinematicSettings* CinematicSettings = static_cast<FAoS_CinematicSettings*>(&InMediaSettings))
		{
			PlayCinematic(CinematicDataAsset, *CinematicSettings);
		}
		else
		{
			PlayCinematic(CinematicDataAsset);
		}
		return;
	}

	UAoS_VideoDataAsset* VideoDataAsset = Cast<UAoS_VideoDataAsset>(InMediaToPlay);
	
	if (IsValid(VideoDataAsset))
	{
		if (const FAoS_VideoSettings* VideoSettings = static_cast<FAoS_VideoSettings*>(&InMediaSettings))
		{
			PlayVideo(VideoDataAsset, *VideoSettings);
		}
		else
		{
			PlayVideo(VideoDataAsset);
		}
	}
}

void UAoS_MediaManager::PlayCinematic(UAoS_CinematicDataAsset* InCinematicToPlay, FAoS_CinematicSettings InCinematicSettings)
{
	if (!IsValid(InCinematicToPlay)) {return;}
	if (HasMediaPlayed(InCinematicToPlay) && !InCinematicToPlay->bCanRepeat) {return;}
	
	InCinematicToPlay->CinematicPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, InCinematicToPlay->LevelSequence, InCinematicToPlay->PlaybackSettings, InCinematicToPlay->LevelSequenceActor);
	LoadedCinematic = InCinematicToPlay;

	if(!IsValid(GameInstance) || !IsValid(InCinematicToPlay->CinematicPlayer)){return;}

	if (!GameInstance->GetLevelManager()->GetLevelHasLoaded())
	{
		if (DelayedCinematicDelegate.IsBound()){DelayedCinematicDelegate.Unbind();}
		
		DelayedCinematicDelegate.BindUObject(this, &ThisClass::PlayCinematic, InCinematicToPlay, InCinematicSettings);
		GameInstance->GetLevelManager()->OnLevelLoaded.AddDynamic(this, &ThisClass::DelayedCinematicPlay);
		return;
	}

	LoadedCinematic->CinematicPlayer->OnFinished.AddDynamic(this, &ThisClass::OnCinematicEnded);
	LoadedCinematic->CinematicPlayer->OnPause.AddDynamic(this, &ThisClass::OnCinematicSkipped);
	LoadedCinematic->CinematicPlayer->Play();
	
	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_CinematicMode);
	OnCinematicBeginPlay.Broadcast(LoadedCinematic);
}

void UAoS_MediaManager::PlayVideo(UAoS_VideoDataAsset* InVideoToPlay, FAoS_VideoSettings InVideoSettings)
{
	if (!IsValid(InVideoToPlay)){return;}
	if (HasMediaPlayed(InVideoToPlay) && !InVideoSettings.bShouldRepeat) {return;}
	
	LoadedVideo = InVideoToPlay;

	if (!IsValid(GameInstance) || !IsValid(LoadedVideo)){return;}

	LoadedVideo->bCanRepeat = InVideoSettings.bShouldRepeat;
	LoadedVideo->MediaPlayer->SetNativeVolume(InVideoSettings.Volume);
	
	if (!GameInstance->GetLevelManager()->GetLevelHasLoaded())
	{
		if (DelayedVideoDelegate.IsBound()){DelayedVideoDelegate.Unbind();}
		
		DelayedVideoDelegate.BindUObject(this, &ThisClass::PlayVideo, InVideoToPlay, InVideoSettings);
		GameInstance->GetLevelManager()->OnLevelLoaded.AddDynamic(this, &ThisClass::DelayedVideoPlay);
		return;
	}
	
	if (LoadedVideo->MediaPlayer->OnEndReached.IsBound())
	{
		LoadedVideo->MediaPlayer->OnEndReached.RemoveAll(this);
	}

	const AAoS_PlayerController* PlayerController = Cast<AAoS_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(PlayerController))
	{
		PlayerController->GetMediaSoundComponent()->SetMediaPlayer(LoadedVideo->MediaPlayer);
	}

	LoadedVideo->MediaPlayer->OnEndReached.AddDynamic(this, &ThisClass::UAoS_MediaManager::OnVideoEnded);
	LoadedVideo->MediaPlayer->OnMediaClosed.AddDynamic(this, &ThisClass::UAoS_MediaManager::OnVideoSkipped);

	GameInstance->RequestNewPlayerMode(EPlayerMode::PM_VideoMode);

	// Note: Playing the actual video file happens in the widget blueprint
	LoadedVideo->MediaPlayer->Play();
	OnVideoBeginPlay.Broadcast(LoadedVideo);
}

void UAoS_MediaManager::SkipMedia(UAoS_MediaDataAsset* InMediaToSkip)
{
	if(const UAoS_CinematicDataAsset* CinematicDataAsset = Cast<UAoS_CinematicDataAsset>(InMediaToSkip))
	{
		CinematicDataAsset->CinematicPlayer->Stop();
	}
	if(const UAoS_VideoDataAsset* VideoDataAsset = Cast<UAoS_VideoDataAsset>(InMediaToSkip))
	{
		VideoDataAsset->MediaPlayer->Close();
	}
}

void UAoS_MediaManager::ResetCinematicByTag(FGameplayTag InCinematicTag)
{
	if (GetWatchedCinematics().Num() <= 0){return;}
	for (UAoS_CinematicDataAsset* CurrentCinematic : WatchedCinematics)
	{
		if(IsValid(CurrentCinematic) && CurrentCinematic->MediaTag == InCinematicTag)
		{
			RemoveFromWatchedCinematics(CurrentCinematic);
		}
	}
}

void UAoS_MediaManager::ResetAllCinematics()
{
	if (GetWatchedCinematics().Num() <= 0){return;}

	GetWatchedCinematics().Empty();
}

void UAoS_MediaManager::ResetVideoByTag(FGameplayTag InVideoTag)
{
	if (GetWatchedVideos().Num() <= 0){return;}
	for (UAoS_VideoDataAsset* CurrentVideo : GetWatchedVideos())
	{
		if(IsValid(CurrentVideo) && CurrentVideo->MediaTag == InVideoTag)
		{
			RemoveFromWatchedVideos(CurrentVideo);
		}
	}
}

void UAoS_MediaManager::ResetAllVideos()
{
	if (GetWatchedVideos().Num() <= 0){return;}

	GetWatchedVideos().Empty();
}

void UAoS_MediaManager::AddToWatchedVideos(UAoS_VideoDataAsset* InVideoToAdd)
{
	if (!InVideoToAdd) {return;}
	
	WatchedVideos.AddUnique(InVideoToAdd);
}

void UAoS_MediaManager::AddToWatchedCinematics(UAoS_CinematicDataAsset* InCinematicToAdd)
{
	if (!InCinematicToAdd) {return;}
	
	WatchedCinematics.AddUnique(InCinematicToAdd);
}

void UAoS_MediaManager::RemoveFromWatchedVideos(UAoS_VideoDataAsset* InVideoToRemove)
{
	if (!InVideoToRemove) {return;}

	if (WatchedVideos.Contains(InVideoToRemove))
	{
		WatchedVideos.Remove(InVideoToRemove);
	}
}

void UAoS_MediaManager::RemoveFromWatchedCinematics(UAoS_CinematicDataAsset* InCinematicToRemove)
{
	if (!InCinematicToRemove) {return;}

	if (WatchedCinematics.Contains(InCinematicToRemove))
	{
		WatchedCinematics.Remove(InCinematicToRemove);
	}
}

bool UAoS_MediaManager::HasMediaPlayed(UAoS_MediaDataAsset* InMediaDataAsset)
{
	if (const UAoS_CinematicDataAsset* CinematicDataAsset = Cast<UAoS_CinematicDataAsset>(InMediaDataAsset))
	{
		for (const UAoS_CinematicDataAsset* CurrentWatchedCinematic : WatchedCinematics)
		{
			if (CurrentWatchedCinematic == CinematicDataAsset)
			{
				return true;
			}
		}
	}
	else if (const UAoS_VideoDataAsset* VideoDataAsset = Cast<UAoS_VideoDataAsset>(InMediaDataAsset))
	{
		for (const UAoS_VideoDataAsset* CurrentWatchedVideo : WatchedVideos)
		{
			if (CurrentWatchedVideo == VideoDataAsset)
			{
				return true;
			}
		}
	}

	return false;
}

TArray<UAoS_CinematicDataAsset*> UAoS_MediaManager::GetWatchedCinematics()
{
	return WatchedCinematics;
}

UAoS_CinematicDataAsset* UAoS_MediaManager::GetLoadedCinematic() const
{
	return LoadedCinematic;
}

UAoS_VideoDataAsset* UAoS_MediaManager::GetLoadedVideo() const
{
	return LoadedVideo;
}

TArray<UAoS_VideoDataAsset*> UAoS_MediaManager::GetWatchedVideos()
{
	return WatchedVideos;
}

void UAoS_MediaManager::OnCinematicSkipped()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedCinematics(LoadedCinematic);
	if(LoadedCinematic->bIsOpeningMedia)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);	
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
	OnCinematicEndPlay.Broadcast(LoadedCinematic);
}

void UAoS_MediaManager::OnCinematicEnded()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedCinematics(LoadedCinematic);
	if (LoadedCinematic->bIsOpeningMedia)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
	OnCinematicEndPlay.Broadcast(LoadedCinematic);
}

void UAoS_MediaManager::DelayedCinematicPlay(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	if(!IsValid(LoadedCinematic)){return;}
	
	DelayedCinematicDelegate.Execute();
}

void UAoS_MediaManager::DelayedVideoPlay(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	if(!IsValid(LoadedVideo)){return;}
	
	PlayVideo(LoadedVideo);
}

void UAoS_MediaManager::OnVideoEnded()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedVideos(LoadedVideo);
	if (LoadedVideo->bIsOpeningMedia)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
	OnVideoEndPlay.Broadcast(LoadedVideo);
}

void UAoS_MediaManager::OnVideoSkipped()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedVideos(LoadedVideo);
	if(LoadedVideo->bIsOpeningMedia)
	{
		GameInstance->RequestNewPlayerMode(EPlayerMode::PM_ExplorationMode);	
	}
	else
	{
		GameInstance->RequestNewPlayerMode(GameInstance->GetPreviousPlayerMode());	
	}
	OnVideoEndPlay.Broadcast(LoadedVideo);
}
	
