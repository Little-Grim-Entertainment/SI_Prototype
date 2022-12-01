// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_MoviePlayerWidget.generated.h"

class UMediaSource;
class UMediaPlayer;
class UMediaTexture;
class UImage;


UCLASS()
class AOS_PROTOTYPE_API UAoS_MoviePlayerWidget : public UAoS_UserWidget
{
	GENERATED_BODY()

public:

	void SetMediaTexture(UMediaTexture* InMediaTexture);
	void SetMediaPlayer(UMediaPlayer* InMediaPlayer);
	void SetMediaSource(UMediaSource* InMediaSource);

	void PlayVideo();
	
protected:

	UPROPERTY(meta=(BindWidget))
	UImage* IMG_Video;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnVideoPlay();
	void OnVideoPlay_Implementation();
	
	UFUNCTION(BlueprintPure)
	UMediaTexture* GetCurrentMediaTexture() const;

	UPROPERTY(BlueprintReadOnly)
	UMediaTexture* CurrentMediaTexture;
	UPROPERTY(BlueprintReadOnly)
	UMediaPlayer* CurrentMediaPlayer;
	UPROPERTY(BlueprintReadOnly)
	UMediaSource* CurrentMediaSource;	
};
