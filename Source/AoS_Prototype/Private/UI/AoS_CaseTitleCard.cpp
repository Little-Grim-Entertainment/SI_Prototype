// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AoS_CaseTitleCard.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"


void UAoS_CaseTitleCard::ShowTitleCard(FText InCaseTitle, UTexture2D* InCaseBackground, USoundBase* InTitleMusic, float InDisplayTime, bool bInShouldFade)
{
	if (!IsValid(InCaseBackground)) {return;}
	
	TXT_CaseTitle->SetText(InCaseTitle);
	IMG_CaseBackground->SetBrushFromTexture(InCaseBackground);
	TitleMusic = InTitleMusic;
	bShouldFadeIn = bInShouldFade;

	CardDisplayTimerDelegate.BindUObject(this, &UAoS_CaseTitleCard::HideTitleCard);
	GetWorld()->GetTimerManager().SetTimer(CardDisplayTimerHandle, CardDisplayTimerDelegate, InDisplayTime, false);
	
	OnShowTitleCard();
}

void UAoS_CaseTitleCard::HideTitleCard()
{
	CardDisplayTimerDelegate.Unbind();
	OnHideTitleCard();
}
