// Fill out your copyright notice in the Description page of Project Settings.


#include "Media/AoS_MediaManager.h"

#include "AoS_GameInstance.h"
#include "AoS_GameplayTagManager.h"
#include "AoS_PlayerManager.h"
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

void UAoS_MediaManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	Super::OnGameplayTagAdded(InAddedTag);
	
	if(!AoSTagManager->HasParentTag(InAddedTag, AOSTag_Media)) {return;}

	if(InAddedTag == AOSTag_Media_Video)
	{
		
	}
	if(InAddedTag == AOSTag_Media_Cinematic)
	{
		
	}
	if(InAddedTag == AOSTag_Media_TitleCard)
	{
		
	}
}

void UAoS_MediaManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	Super::OnGameplayTagRemoved(InRemovedTag);
	
	if(!AoSTagManager->HasParentTag(InRemovedTag, AOSTag_Media)) {return;}

	if(InRemovedTag == AOSTag_Media_Video)
	{
		
	}
	if(InRemovedTag == AOSTag_Media_Cinematic)
	{
		
	}
	if(InRemovedTag == AOSTag_Media_TitleCard)
	{
		
	}
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

	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager)) {return;}
	
	if (!LevelManager->GetLevelHasLoaded())
	{
		if (DelayedCinematicDelegate.IsBound()){DelayedCinematicDelegate.Unbind();}
		
		DelayedCinematicDelegate.BindUObject(this, &ThisClass::PlayCinematic, InCinematicToPlay, InCinematicSettings);
		LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::DelayedCinematicPlay);
		return;
	}

	LoadedCinematic->CinematicPlayer->OnFinished.AddDynamic(this, &ThisClass::OnCinematicEnded);
	LoadedCinematic->CinematicPlayer->OnPause.AddDynamic(this, &ThisClass::OnCinematicSkipped);
	LoadedCinematic->CinematicPlayer->Play();

	AoSTagManager->ReplaceTagWithSameParent(AOSTag_Media_Cinematic, AOSTag_Media);
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

	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager)) {return;}
	
	if (!LevelManager->GetLevelHasLoaded())
	{
		if (DelayedVideoDelegate.IsBound()){DelayedVideoDelegate.Unbind();}
		
		DelayedVideoDelegate.BindUObject(this, &ThisClass::PlayVideo, InVideoToPlay, InVideoSettings);
		LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::DelayedVideoPlay);
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
	
	// Note: Playing the actual video file happens in the widget blueprint
	LoadedVideo->MediaPlayer->Play();
	
	AoSTagManager->ReplaceTagWithSameParent(AOSTag_Media_Video, AOSTag_Media);
	OnVideoBeginPlay.Broadcast(LoadedVideo);
}

void UAoS_MediaManager::SkipMedia(UAoS_MediaDataAsset* InMediaToSkip)
{
	if(const UAoS_CinematicDataAsset* CinematicDataAsset = Cast<UAoS_CinematicDataAsset>(InMediaToSkip))
	{
		CinematicDataAsset->CinematicPlayer->Stop();
		OnCinematicSkipped();
	}
	if(const UAoS_VideoDataAsset* VideoDataAsset = Cast<UAoS_VideoDataAsset>(InMediaToSkip))
	{
		VideoDataAsset->MediaPlayer->Close();
		OnVideoSkipped();
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
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_Player_State_Exploration, AOSTag_Player_State);
	}
	else
	{
		const UAoS_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UAoS_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			AoSTagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), AOSTag_Player_State);
		}
	}
	
	AoSTagManager->RemoveTag(AOSTag_Media_Cinematic);
	OnCinematicEndPlay.Broadcast(LoadedCinematic);
}

void UAoS_MediaManager::OnCinematicEnded()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedCinematics(LoadedCinematic);
	if (LoadedCinematic->bIsOpeningMedia)
	{
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_Player_State_Exploration, AOSTag_Player_State);
	}
	else
	{
		const UAoS_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UAoS_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			AoSTagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), AOSTag_Player_State);
		}
	}
	
	AoSTagManager->RemoveTag(AOSTag_Media_Cinematic);
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
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_Player_State_Exploration, AOSTag_Player_State);
	}
	else
	{
		const UAoS_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UAoS_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			AoSTagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), AOSTag_Player_State);
		}
	}
	
	AoSTagManager->RemoveTag(AOSTag_Media_Video);
	OnVideoEndPlay.Broadcast(LoadedVideo);
}

void UAoS_MediaManager::OnVideoSkipped()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedVideos(LoadedVideo);
	if(LoadedVideo->bIsOpeningMedia)
	{
		AoSTagManager->ReplaceTagWithSameParent(AOSTag_Player_State_Exploration, AOSTag_Player_State);
	}
	else
	{
		const UAoS_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UAoS_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			AoSTagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), AOSTag_Player_State);
		}
	}
	
	AoSTagManager->RemoveTag(AOSTag_Media_Video);
	OnVideoEndPlay.Broadcast(LoadedVideo);
}
	
