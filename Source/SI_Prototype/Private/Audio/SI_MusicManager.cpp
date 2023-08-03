// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/SI_MusicManager.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"
#include "AudioDevice.h"
#include "Components/AudioComponent.h"
#include "Data/Maps/SI_MapData.h"
#include "GameModes/SI_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/SI_LevelManager.h"

DEFINE_LOG_CATEGORY(LogSI_MusicManager);

USI_MusicManager::USI_MusicManager()
{
	bMusicIsPlaying = false;
	bMusicIsPaused = false;
	MusicTimeAtPause = 0.f;
	MusicVolumeAtPause = 1.f;
	MusicPitchAtPause = 1.f;
}

void USI_MusicManager::TickMusicTimecode()
{
	MusicTimeAtPause += .001;
}

void USI_MusicManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

void USI_MusicManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	Super::OnGameplayTagAdded(InAddedTag);

	if (SITagManager->HasParentTag(InAddedTag, SITag_Map_Title))
	{
		PlayLoadedLevelBackgroundMusic();
		return;
	}
	if (SITagManager->HasParentTag(InAddedTag, SITag_Game_State_Loading))
	{
		StopBackgroundMusic(true, 0.0f);
		return;
	}
	if(!SITagManager->HasParentTag(InAddedTag, SITag_Audio_Music)) {return;}
	
	if(InAddedTag == SITag_Audio_Music_Pause)
	{
		PauseMusicWithFade();
	}
}

void USI_MusicManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	Super::OnGameplayTagRemoved(InRemovedTag);

	if(!SITagManager->HasParentTag(InRemovedTag, SITag_Audio_Music)) {return;}
	
	if(InRemovedTag == SITag_Audio_Music_Pause)
	{
		ResumeMusicWithFade();
	}
}

UAudioComponent* USI_MusicManager::PlayLoadedLevelBackgroundMusic()
{
	USI_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_LevelManager>();
	
	if (!IsValid(LevelManager)){return nullptr;}
	if (!LevelManager->GetCurrentLoadedMapState()->IsStateValid()){return nullptr;}
	
	return PlayBackgroundMusic(LevelManager->GetCurrentLoadedMapState()->GetMapData()->BackgroundMusicSettings);
}

UAudioComponent* USI_MusicManager::PlayBackgroundMusic(FSI_MusicSettings InMusicSettings)
{
	BackgroundMusic = UGameplayStatics::CreateSound2D(GameInstance, InMusicSettings.MetaSoundSource, InMusicSettings.VolumeMultiplier, InMusicSettings.PitchMultiplier, InMusicSettings.StartTime, nullptr, true);	

	CurrentMusicSettings = InMusicSettings;
	
	MetaSoundSoftClassPtr = CurrentMusicSettings.MetaSoundSource;
	MusicSoftClassPtr = CurrentMusicSettings.MusicSource;
	
	if (IsValid(BackgroundMusic))
	{
		BackgroundMusic->SetObjectParameter("Wave Asset", CurrentMusicSettings.MusicSource);
		BackgroundMusic->SetFloatParameter("Start Time", CurrentMusicSettings.StartTime);
		
		if(InMusicSettings.bHasIntro && BackgroundMusic->GetSound()->IsLooping())
		{
			BackgroundMusic->SetFloatParameter("Loop Start", CurrentMusicSettings.LoopStart);
		}

		GetWorld()->GetTimerManager().SetTimer(MusicTimecode, this, &ThisClass::TickMusicTimecode, 0.001f, true);

		const ASI_GameMode* GameMode = GameInstance->GetGameMode();
		if (!IsValid(GameMode)) {return nullptr;}
		
		if (CurrentMusicSettings.bShouldFade)
		{
			const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameMode->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
			BackgroundMusic->FadeIn(FadeInDuration);
		}
		else
		{
			BackgroundMusic->Play();
		}
				
		OnBackgroundMusicStarted.Broadcast();
		bMusicIsPlaying = true;
		bMusicIsPaused = false;
		
		return BackgroundMusic;
	}
	return nullptr;
}

void USI_MusicManager::PauseMusicWithFade()
{
	if (!IsValid(BackgroundMusic))
	{
		return;
	}
	
	const ASI_GameMode* GameMode = GameInstance->GetGameMode();
	if (!IsValid(GameMode)) {return;}

	const float FadeInDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameMode->GlobalFadeInDuration : CurrentMusicSettings.FadeInDuration;
	
	MusicTimeAtPause += FadeInDuration;
	MusicVolumeAtPause = CurrentMusicSettings.VolumeMultiplier;
	MusicPitchAtPause = CurrentMusicSettings.PitchMultiplier;

	bMusicIsPaused = true;
	OnBackgroundMusicPaused.Broadcast();

	GetWorld()->GetTimerManager().PauseTimer(MusicTimecode);
	
	StopBackgroundMusic(true, 0);
}

void USI_MusicManager::ResumeMusicWithFade()
{
	CurrentMusicSettings.MetaSoundSource = MetaSoundSoftClassPtr.Get();
	CurrentMusicSettings.MusicSource = MusicSoftClassPtr.Get();
	if (IsValid(CurrentMusicSettings.MetaSoundSource) && IsValid(CurrentMusicSettings.MusicSource))
	{
		bMusicIsPaused = false;
		GetWorld()->GetTimerManager().UnPauseTimer(MusicTimecode);
		PlayBackgroundMusic(CurrentMusicSettings);
	}
}

void USI_MusicManager::StopBackgroundMusic(bool bShouldFade, float FadeVolumeLevel)
{
	if (IsValid(BackgroundMusic))
	{
		if (bShouldFade)
		{
			const ASI_GameMode* GameMode = GameInstance->GetGameMode();
			if (!IsValid(GameMode)) {return;}
			
			const float FadeOutDuration = CurrentMusicSettings.bUseGlobalFadeSettings ? GameMode->GlobalFadeOutDuration : CurrentMusicSettings.FadeOutDuration;
			BackgroundMusic->FadeOut(FadeOutDuration, FadeVolumeLevel);
		}
		else
		{
			BackgroundMusic->Stop();
		}
		if (!bMusicIsPaused)
		{
			GetWorld()->GetTimerManager().ClearTimer(MusicTimecode);
			OnBackgroundMusicStopped.Broadcast();
		}
		BackgroundMusic->DestroyComponent();
		bMusicIsPlaying = false;
	}
}
