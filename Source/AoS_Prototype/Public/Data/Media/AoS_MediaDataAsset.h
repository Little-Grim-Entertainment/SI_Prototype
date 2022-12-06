// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_MediaDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_MediaDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Videos")
	FString MediaName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media")
	bool bCanRepeat = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media")
	bool bIsOpeningMedia = false;

	UFUNCTION(BlueprintPure, Category = "Media")
	bool GetMediaIsPlaying() const;
	UFUNCTION(BlueprintPure, Category = "Media")
	bool GetMediaHasPlayed() const;
	UFUNCTION(BlueprintPure, Category = "Media")
	bool GetMediaWasSkipped() const;

	UFUNCTION(BlueprintCallable, Category = "Media")
	virtual void StartMedia();
	UFUNCTION(BlueprintCallable, Category = "Media")
	virtual void SkipMedia();

	UFUNCTION(BlueprintCallable, Category = "Media")
	virtual void ResetMediaDefaults();

protected:

	bool bIsPlaying = false;
	UPROPERTY(EditAnywhere, Category = "Media")
	bool bHasPlayed = false;
	UPROPERTY(EditAnywhere, Category = "Media")
	bool bWasSkipped = false;
};
