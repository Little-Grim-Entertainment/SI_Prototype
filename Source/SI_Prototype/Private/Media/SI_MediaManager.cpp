// Fill out your copyright notice in the Description page of Project Settings.


#include "Media/SI_MediaManager.h"

#include "SI_GameInstance.h"
#include "GameplayTag/SI_GameplayTagManager.h"
#include "SI_PlayerManager.h"
#include "GameplayTagContainer.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Debug/SI_DebugManager.h"
#include "Controllers/SI_PlayerController.h"
#include "Data/Media/SI_CinematicDataAsset.h"
#include "Levels/SI_LevelManager.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "Data/Media/SI_VideoDataAsset.h"

void USI_MediaManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag, FSITagPayload* InTagPayload)
{
	Super::OnGameplayTagAdded(InAddedTag);
	
	if(!SITagManager->HasParentTag(InAddedTag, SITag_Media)) {return;}

	if(InAddedTag == SITag_Media_Video)
	{
		
	}
	if(InAddedTag == SITag_Media_Cinematic)
	{
		
	}
	if(InAddedTag == SITag_Media_TitleCard)
	{
		
	}
}

void USI_MediaManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag, FSITagPayload* InTagPayload)
{
	Super::OnGameplayTagRemoved(InRemovedTag);
	
	if(!SITagManager->HasParentTag(InRemovedTag, SITag_Media)) {return;}

	if(InRemovedTag == SITag_Media_Video)
	{
		
	}
	if(InRemovedTag == SITag_Media_Cinematic)
	{
		
	}
	if(InRemovedTag == SITag_Media_TitleCard)
	{
		
	}
}

void USI_MediaManager::PlayMedia(USI_MediaDataAsset* InMediaToPlay, FSI_MediaSettings& InMediaSettings)
{
	if(ShouldDisableMedia()) {return;}
	
	USI_CinematicDataAsset* CinematicDataAsset = Cast<USI_CinematicDataAsset>(InMediaToPlay);
		
	if (IsValid(CinematicDataAsset))
	{
		if (FSI_CinematicSettings* CinematicSettings = static_cast<FSI_CinematicSettings*>(&InMediaSettings))
		{
			PlayCinematic(CinematicDataAsset, *CinematicSettings);
		}
		else
		{
			PlayCinematic(CinematicDataAsset);
		}
		
		SITagManager->AddNewGameplayTag(SITag_Audio_Music_Pause);
		return;
	}

	USI_VideoDataAsset* VideoDataAsset = Cast<USI_VideoDataAsset>(InMediaToPlay);
	
	if (IsValid(VideoDataAsset))
	{
		if (const FSI_VideoSettings* VideoSettings = static_cast<FSI_VideoSettings*>(&InMediaSettings))
		{
			PlayVideo(VideoDataAsset, *VideoSettings);
		}
		else
		{
			PlayVideo(VideoDataAsset);
		}

		SITagManager->AddNewGameplayTag(SITag_Audio_Music_Pause);
	}
}

void USI_MediaManager::PlayCinematic(USI_CinematicDataAsset* InCinematicToPlay, FSI_CinematicSettings InCinematicSettings)
{
	if (!IsValid(InCinematicToPlay)) {return;}
	if (HasMediaPlayed(InCinematicToPlay) && !InCinematicToPlay->bCanRepeat) {return;}
	
	InCinematicToPlay->CinematicPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, InCinematicToPlay->LevelSequence, InCinematicToPlay->PlaybackSettings, InCinematicToPlay->LevelSequenceActor);
	LoadedCinematic = InCinematicToPlay;

	if(!IsValid(GameInstance) || !IsValid(InCinematicToPlay->CinematicPlayer)){return;}

	USI_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_LevelManager>();
	if (!IsValid(LevelManager)) {return;}
	
	if (!LevelManager->GetLevelHasLoaded())
	{
		if (DelayedCinematicDelegate.IsBound()){DelayedCinematicDelegate.Unbind();}
		
		DelayedCinematicDelegate.BindUObject(this, &ThisClass::PlayCinematic, InCinematicToPlay, InCinematicSettings);
		LevelManager->OnLevelLoaded().AddDynamic(this, &ThisClass::DelayedCinematicPlay);
		return;
	}

	LoadedCinematic->CinematicPlayer->OnFinished.AddDynamic(this, &ThisClass::OnCinematicEnded);
	LoadedCinematic->CinematicPlayer->OnPause.AddDynamic(this, &ThisClass::OnCinematicSkipped);
	LoadedCinematic->CinematicPlayer->Play();

	SITagManager->ReplaceTagWithSameParent(SITag_Media_Cinematic, SITag_Media);
	OnCinematicBeginPlay.Broadcast(LoadedCinematic);
}

void USI_MediaManager::PlayVideo(USI_VideoDataAsset* InVideoToPlay, FSI_VideoSettings InVideoSettings)
{
	if (!IsValid(InVideoToPlay)){return;}
	if (HasMediaPlayed(InVideoToPlay) && !InVideoSettings.bShouldRepeat) {return;}
	
	LoadedVideo = InVideoToPlay;

	if (!IsValid(GameInstance)/* || !IsValid(LoadedVideo)*/){return;}

	LoadedVideo->bCanRepeat = InVideoSettings.bShouldRepeat;
	LoadedVideo->MediaPlayer->SetNativeVolume(InVideoSettings.Volume);

	USI_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_LevelManager>();
	if (!IsValid(LevelManager)) {return;}
	
	if (!LevelManager->GetLevelHasLoaded())
	{
		if (DelayedVideoDelegate.IsBound()){DelayedVideoDelegate.Unbind();}
		
		DelayedVideoDelegate.BindUObject(this, &ThisClass::PlayVideo, InVideoToPlay, InVideoSettings);
		LevelManager->OnLevelLoaded().AddDynamic(this, &ThisClass::DelayedVideoPlay);
		return;
	}
	
	if (LoadedVideo->MediaPlayer->OnEndReached.IsBound())
	{
		LoadedVideo->MediaPlayer->OnEndReached.RemoveAll(this);
	}

	const ASI_PlayerController* PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (IsValid(PlayerController))
	{
		PlayerController->GetMediaSoundComponent()->SetMediaPlayer(LoadedVideo->MediaPlayer);
	}

	LoadedVideo->MediaPlayer->OnEndReached.AddDynamic(this, &ThisClass::USI_MediaManager::OnVideoEnded);
	LoadedVideo->MediaPlayer->OnMediaClosed.AddDynamic(this, &ThisClass::USI_MediaManager::OnVideoSkipped);
	
	// Note: Playing the actual video file happens in the widget blueprint
	//LoadedVideo->MediaPlayer->Play();
	
	SITagManager->ReplaceTagWithSameParent(SITag_Media_Video, SITag_Media);
	OnVideoBeginPlay.Broadcast(LoadedVideo);
}

void USI_MediaManager::SkipMedia(USI_MediaDataAsset* InMediaToSkip)
{
	if(const USI_CinematicDataAsset* CinematicDataAsset = Cast<USI_CinematicDataAsset>(InMediaToSkip))
	{
		CinematicDataAsset->CinematicPlayer->Stop();
		OnCinematicSkipped();
	}
	if(const USI_VideoDataAsset* VideoDataAsset = Cast<USI_VideoDataAsset>(InMediaToSkip))
	{
		VideoDataAsset->MediaPlayer->Close();
		OnVideoSkipped();
	}
}

void USI_MediaManager::ResetCinematicByTag(FGameplayTag InCinematicTag)
{
	if (GetWatchedCinematics().Num() <= 0){return;}
	for (USI_CinematicDataAsset* CurrentCinematic : WatchedCinematics)
	{
		if(IsValid(CurrentCinematic) && CurrentCinematic->MediaTag == InCinematicTag)
		{
			RemoveFromWatchedCinematics(CurrentCinematic);
		}
	}
}

void USI_MediaManager::ResetAllCinematics()
{
	if (GetWatchedCinematics().Num() <= 0){return;}

	GetWatchedCinematics().Empty();
}

void USI_MediaManager::ResetVideoByTag(FGameplayTag InVideoTag)
{
	if (GetWatchedVideos().Num() <= 0){return;}
	for (USI_VideoDataAsset* CurrentVideo : GetWatchedVideos())
	{
		if(IsValid(CurrentVideo) && CurrentVideo->MediaTag == InVideoTag)
		{
			RemoveFromWatchedVideos(CurrentVideo);
		}
	}
}

void USI_MediaManager::ResetAllVideos()
{
	if (GetWatchedVideos().Num() <= 0){return;}

	GetWatchedVideos().Empty();
}

void USI_MediaManager::AddToWatchedVideos(USI_VideoDataAsset* InVideoToAdd)
{
	if (!InVideoToAdd) {return;}
	
	WatchedVideos.AddUnique(InVideoToAdd);
}

void USI_MediaManager::AddToWatchedCinematics(USI_CinematicDataAsset* InCinematicToAdd)
{
	if (!InCinematicToAdd) {return;}
	
	WatchedCinematics.AddUnique(InCinematicToAdd);
}

void USI_MediaManager::RemoveFromWatchedVideos(USI_VideoDataAsset* InVideoToRemove)
{
	if (!InVideoToRemove) {return;}

	if (WatchedVideos.Contains(InVideoToRemove))
	{
		WatchedVideos.Remove(InVideoToRemove);
	}
}

void USI_MediaManager::RemoveFromWatchedCinematics(USI_CinematicDataAsset* InCinematicToRemove)
{
	if (!InCinematicToRemove) {return;}

	if (WatchedCinematics.Contains(InCinematicToRemove))
	{
		WatchedCinematics.Remove(InCinematicToRemove);
	}
}

bool USI_MediaManager::HasMediaPlayed(USI_MediaDataAsset* InMediaDataAsset)
{
	if (const USI_CinematicDataAsset* CinematicDataAsset = Cast<USI_CinematicDataAsset>(InMediaDataAsset))
	{
		for (const USI_CinematicDataAsset* CurrentWatchedCinematic : WatchedCinematics)
		{
			if (CurrentWatchedCinematic == CinematicDataAsset)
			{
				return true;
			}
		}
	}
	else if (const USI_VideoDataAsset* VideoDataAsset = Cast<USI_VideoDataAsset>(InMediaDataAsset))
	{
		for (const USI_VideoDataAsset* CurrentWatchedVideo : WatchedVideos)
		{
			if (CurrentWatchedVideo == VideoDataAsset)
			{
				return true;
			}
		}
	}

	return false;
}

TArray<USI_CinematicDataAsset*> USI_MediaManager::GetWatchedCinematics()
{
	return WatchedCinematics;
}

USI_CinematicDataAsset* USI_MediaManager::GetLoadedCinematic() const
{
	return LoadedCinematic;
}

USI_VideoDataAsset* USI_MediaManager::GetLoadedVideo() const
{
	return LoadedVideo;
}

TArray<USI_VideoDataAsset*> USI_MediaManager::GetWatchedVideos()
{
	return WatchedVideos;
}

void USI_MediaManager::OnCinematicSkipped()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedCinematics(LoadedCinematic);
	if(LoadedCinematic->bIsOpeningMedia)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
	}
	else
	{
		const USI_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			SITagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), SITag_Player_State);
		}
	}

	SITagManager->RemoveTag(SITag_Audio_Music_Pause);
	SITagManager->RemoveTag(SITag_Media_Cinematic);
	OnCinematicEndPlay.Broadcast(LoadedCinematic);
}

void USI_MediaManager::OnCinematicEnded()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedCinematics(LoadedCinematic);
	if (LoadedCinematic->bIsOpeningMedia)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
	}
	else
	{
		const USI_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			SITagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), SITag_Player_State);
		}
	}

	SITagManager->RemoveTag(SITag_Audio_Music_Pause);
	SITagManager->RemoveTag(SITag_Media_Cinematic);
	OnCinematicEndPlay.Broadcast(LoadedCinematic);
}

bool USI_MediaManager::ShouldDisableMedia() const
{
#if !UE_BUILD_SHIPPING
	USI_DebugManager* DebugManager = GameInstance->GetSubsystem<USI_DebugManager>();
	if(!IsValid(DebugManager)) { return CvarDisableAllMedia.GetValueOnAnyThread() == 1 ? true : false; }
	
	const bool bCVarBool = CvarDisableAllMedia.GetValueOnAnyThread() == 1 ? true : false;
	const FSI_DebugBool* DebugBool = DebugManager->GetDebugBoolByTag(SITag_Debug_DisableAllMedia);
	
	return bCVarBool || DebugBool->GetDebugBool();
#endif
	return false;
}

void USI_MediaManager::DelayedCinematicPlay(USI_MapData* LoadedLevel, bool bShouldFade)
{
	if(!IsValid(LoadedCinematic)){return;}
	
	DelayedCinematicDelegate.Execute();
}

void USI_MediaManager::DelayedVideoPlay(USI_MapData* LoadedLevel, bool bShouldFade)
{
	if(!IsValid(LoadedVideo)){return;}
	
	PlayVideo(LoadedVideo);
}

void USI_MediaManager::OnVideoEnded()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedVideos(LoadedVideo);
	if (LoadedVideo->bIsOpeningMedia)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
	}
	else
	{
		const USI_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			SITagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), SITag_Player_State);
		}
	}

	SITagManager->RemoveTag(SITag_Audio_Music_Pause);
	SITagManager->RemoveTag(SITag_Media_Video);
	OnVideoEndPlay.Broadcast(LoadedVideo);
}

void USI_MediaManager::OnVideoSkipped()
{
	if(!IsValid(GameInstance)){return;}

	AddToWatchedVideos(LoadedVideo);
	if(LoadedVideo->bIsOpeningMedia)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
	}
	else
	{
		const USI_PlayerManager* PlayerManager = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
		if(IsValid(PlayerManager))
		{
			SITagManager->ReplaceTagWithSameParent(PlayerManager->GetPreviousPlayerState(), SITag_Player_State);
		}
	}

	SITagManager->RemoveTag(SITag_Audio_Music_Pause);
	SITagManager->RemoveTag(SITag_Media_Video);
	OnVideoEndPlay.Broadcast(LoadedVideo);
}
	
