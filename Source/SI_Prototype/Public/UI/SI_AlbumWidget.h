// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "UI/SI_UserWidget.h"
#include "SI_AlbumWidget.generated.h"

class UBorder;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAlbumSelected, USI_AlbumWidget*, SelectedAlbumWidget);

USTRUCT(BlueprintType)
struct FAlbumDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlbumDetails")
	FText AlbumTitle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlbumDetails")
	UTexture2D* AlbumCover;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlbumDetails")
	USoundBase* AlbumMusic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AlbumDetails")
	float AlbumVolume = 1.0f;	
};

UCLASS()
class SI_PROTOTYPE_API USI_AlbumWidget : public USI_UserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "AlbumDetails")
	FAlbumDetails AlbumDetails;

	UPROPERTY(BlueprintAssignable)
	FOnAlbumSelected OnAlbumSelected;	
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UBorder* BG_AlbumCover;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BTN_Album;
	
	UFUNCTION(BlueprintCallable, Category = "AlbumDetails")
	void SetAlbumDetails(FAlbumDetails InAlbumDetails);

	UFUNCTION(BlueprintPure, Category = "AlbumDetails")
	FAlbumDetails& GetAlbumDetails();

protected:

	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void OnAlbumButtonClicked();	
};