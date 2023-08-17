	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SI_UserWidget.h"
#include "SI_MoviePlayerWidget.generated.h"

class UMediaSource;
class UMediaPlayer;
class UMediaTexture;
class UImage;


UCLASS()
class SI_PROTOTYPE_API USI_MoviePlayerWidget : public USI_UserWidget
{
	GENERATED_BODY()

public:

	void SetMediaTexture(UMediaTexture* InMediaTexture);
	void SetMediaPlayer(UMediaPlayer* InMediaPlayer);
	void SetMediaSource(UMediaSource* InMediaSource);

	UFUNCTION(BlueprintNativeEvent)
	void PlayVideo();
	UFUNCTION(BlueprintNativeEvent)
	void OnVideoStopped();
	
protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* IMG_Video;
	
	void PlayVideo_Implementation();
	
	UFUNCTION(BlueprintPure)
	UMediaTexture* GetCurrentMediaTexture() const;

	UPROPERTY(BlueprintReadOnly)
	UMediaTexture* CurrentMediaTexture;
	UPROPERTY(BlueprintReadOnly)
	UMaterial* CurrentMediaMaterial;
	UPROPERTY(BlueprintReadOnly)
	UMediaPlayer* CurrentMediaPlayer;
	UPROPERTY(BlueprintReadOnly)
	UMediaSource* CurrentMediaSource;
};
