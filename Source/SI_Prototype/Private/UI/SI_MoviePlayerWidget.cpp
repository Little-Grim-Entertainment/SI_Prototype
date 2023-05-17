// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_MoviePlayerWidget.h"
#include "MediaTexture.h"
#include "MediaSource.h"
#include "MediaPlayer.h"
#include "Components/Image.h"

UMediaTexture* USI_MoviePlayerWidget::GetCurrentMediaTexture() const
{
	return CurrentMediaTexture;
}

void USI_MoviePlayerWidget::SetMediaTexture(UMediaTexture* InMediaTexture)
{
	CurrentMediaTexture = InMediaTexture;
	UTexture* InTexture = Cast<UTexture>(CurrentMediaTexture);
	if  (IsValid(InTexture))
	{
		IMG_Video->SetBrushFromAtlasInterface(InTexture);	
	}
}

void USI_MoviePlayerWidget::SetMediaPlayer(UMediaPlayer* InMediaPlayer)
{
	if (IsValid(InMediaPlayer))
	{
		CurrentMediaPlayer = InMediaPlayer;
	}
}

void USI_MoviePlayerWidget::SetMediaSource(UMediaSource* InMediaSource)
{
	if (IsValid(InMediaSource))
	{
		CurrentMediaSource = InMediaSource;
	}
}

void USI_MoviePlayerWidget::PlayVideo_Implementation()
{
	if (!IsValid(CurrentMediaPlayer) || !IsValid(CurrentMediaSource)) {return;}
	
}

void USI_MoviePlayerWidget::OnVideoStopped_Implementation()
{
	if (!IsValid(CurrentMediaPlayer) || !IsValid(CurrentMediaSource)) {return;}

	CurrentMediaPlayer = nullptr;
	CurrentMediaSource = nullptr;
	CurrentMediaTexture = nullptr;
}