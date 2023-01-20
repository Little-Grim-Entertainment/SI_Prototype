// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "UI/AoS_AlbumWidget.h"
#include "AoS_GramaphoneMenu.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UWrapBox;
/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_GramaphoneMenu : public UAoS_UserWidget
{
	GENERATED_BODY()

public:
		
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWrapBox* AlbumList;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* IMG_PlayingAlbumCover;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TXT_AlbumTitle;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BTN_Stop;

	UFUNCTION(BlueprintCallable, Category = "Albums")
	void SetIsAlbumPlaying(bool bInIsAlbumPlaying);
	
	UFUNCTION(BlueprintPure, Category = "Albums")
	TArray<UAoS_AlbumWidget*> GetAlbumWidgets() const;
	UFUNCTION(BlueprintPure, Category = "AlbumDetails")
	FAlbumDetails& GetAlbumDetails();
	UFUNCTION(BlueprintPure, Category = "Albums")
	bool GetIsAlbumPlaying() const;

	UFUNCTION(BlueprintCallable, Category = "AlbumDetails")
	void SetCurrentAlbumDetails(FAlbumDetails& InAlbumDetails);

protected:

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

private:

	UPROPERTY()
	TArray<UAoS_AlbumWidget*> AlbumWidgets;
	
	bool bIsAlbumPlaying = false;
	
	FAlbumDetails CurrentAlbumDetails;
};
