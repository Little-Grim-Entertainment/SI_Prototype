// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_CaseTitleCard.generated.h"

class UTextBlock;
class UImage;
class USoundBase;

UCLASS()
class AOS_PROTOTYPE_API UAoS_CaseTitleCard : public UAoS_UserWidget
{
	GENERATED_BODY()

public:
	
	void ShowTitleCard(FText InCaseTitle, UTexture2D* InCaseBackground, USoundBase* InTitleMusic, float InDisplayTime = 7.0f, bool bInShouldFade = false);
	void HideTitleCard();

	UFUNCTION(BlueprintPure, Category = "Music")
	USoundBase* GetTitleMusic() const {return TitleMusic;}
	UFUNCTION(BlueprintPure, Category = "UI")
	bool GetShouldFadeIn() const {return bShouldFadeIn;}

protected:
		
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_CaseTitle;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* IMG_CaseBackground;

	UFUNCTION(BlueprintImplementableEvent, Category = "Cases")
	void OnShowTitleCard();
	UFUNCTION(BlueprintImplementableEvent, Category = "Cases")
	void OnHideTitleCard();

private:

	UPROPERTY()
	USoundBase* TitleMusic;
	
	FTimerHandle CardDisplayTimerHandle;
	FTimerDelegate CardDisplayTimerDelegate;
	
	float DisplayTime;
	bool bShouldFadeIn;
};
