// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_AlbumWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"

void USI_AlbumWidget::SetAlbumDetails(FAlbumDetails InAlbumDetails)
{
	AlbumDetails = InAlbumDetails;
}

FAlbumDetails& USI_AlbumWidget::GetAlbumDetails()
{
	return AlbumDetails;
}

void USI_AlbumWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(AlbumDetails.AlbumCover) && IsValid(BG_AlbumCover))
	{
		BG_AlbumCover->SetBrushFromTexture(AlbumDetails.AlbumCover);
	}
	if (IsValid(BTN_Album) && !BTN_Album->OnClicked.IsBound())
	{
		BTN_Album->OnClicked.AddDynamic(this, &ThisClass::OnAlbumButtonClicked);
	}
}

void USI_AlbumWidget::OnAlbumButtonClicked()
{
	OnAlbumSelected.Broadcast(this);
}
