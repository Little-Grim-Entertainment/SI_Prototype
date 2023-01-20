// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_GramaphoneMenu.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

void UAoS_GramaphoneMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAoS_GramaphoneMenu::NativePreConstruct()
{
	TArray<UWidget*> AlbumListChildren = AlbumList->GetAllChildren();
	
	for (UWidget* CurrentWidget : AlbumListChildren)
	{
		UAoS_AlbumWidget* AlbumWidget = Cast<UAoS_AlbumWidget>(CurrentWidget);

		if (IsValid(AlbumWidget))
		{
			AlbumWidgets.AddUnique(AlbumWidget);	
		}
	}

	if (IsValid(IMG_PlayingAlbumCover) && IsValid(TXT_AlbumTitle) && IsValid(BTN_Stop))
	{
		if (bIsAlbumPlaying)
		{
			IMG_PlayingAlbumCover->SetBrushFromTexture(GetAlbumDetails().AlbumCover);
			IMG_PlayingAlbumCover->SetVisibility(ESlateVisibility::Visible);
			TXT_AlbumTitle->SetText(GetAlbumDetails().AlbumTitle);
			BTN_Stop->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			IMG_PlayingAlbumCover->SetVisibility(ESlateVisibility::Collapsed);
			TXT_AlbumTitle->SetText(FText::FromString("No Album Playing"));
			BTN_Stop->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	
	Super::NativePreConstruct();
}

void UAoS_GramaphoneMenu::SetIsAlbumPlaying(bool bInIsAlbumPlaying)
{
	bIsAlbumPlaying = bInIsAlbumPlaying;
}

TArray<UAoS_AlbumWidget*> UAoS_GramaphoneMenu::GetAlbumWidgets() const
{
	return AlbumWidgets;
}

FAlbumDetails& UAoS_GramaphoneMenu::GetAlbumDetails()
{
	return CurrentAlbumDetails;
}

bool UAoS_GramaphoneMenu::GetIsAlbumPlaying() const
{
	return bIsAlbumPlaying;
}

void UAoS_GramaphoneMenu::SetCurrentAlbumDetails(FAlbumDetails& InAlbumDetails)
{
	CurrentAlbumDetails = InAlbumDetails;	
}
