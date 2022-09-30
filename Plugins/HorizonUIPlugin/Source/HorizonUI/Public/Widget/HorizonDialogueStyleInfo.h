// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once
// Core
#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
//UObject
#include "UObject/NoExportTypes.h"
#include "UObject/SoftObjectPtr.h"

// SlateCore
#include "Styling/SlateColor.h"
#include "Fonts/SlateFontInfo.h"
#include "Layout/Margin.h"

// HorizonUI
#include "Components/HorizonButton.h"
#include "HorizonDialogueStyleInfo.generated.h"

class FXmlNode;
class UHorizonFlipbookWidget;
class UPaperFlipbook;
class UTexture2D;
class UMaterial;
class UPaperSprite;



USTRUCT(BlueprintType)
struct FHorizonDialogueSegmentInfoRubyTextStyle
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RubyText")
	TArray<FString> Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RubyText")
	TArray<FSlateColor> ColorAndOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RubyText")
	TArray<FSlateFontInfo> Font;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RubyText")
	TArray<FVector2D> ShadowOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RubyText")
	TArray<FSlateColor> ShadowColorAndOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RubyText")
	TArray<FMargin> PaddingMargin;
};

USTRUCT(BlueprintType)
struct FHorizonDialogueSegmentInfoStyle
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
		FName StyleName;

	//Optional parameters. If not be set, will use parent's setting(or default)
	//Because TOptional can't be acceee from blueprint, so use TArray instead, will use TArray::Last() if num of array larger than 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		TArray<FString> Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TArray<FSlateColor> ColorAndOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Font")
		TArray<FSlateFontInfo> Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Font")
		TArray<int> FontSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Font")
		TArray<FName> TypefaceFontName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		TArray<FVector2D> ShadowOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		TArray<FSlateColor> ShadowColorAndOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		TArray<float> DialogueMsgSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		TArray<float> DialogueMsgWait;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
		TArray<FMargin> PaddingMargin;//padding position for segment

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HyperText")
		TArray<FString> HypertextReference;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HyperText")
		TArray<FSlateColor> HypertextHoveredColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HyperText")
		TArray<FSlateColor> HypertextVisitedColor;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HyperText")
		TArray<TSubclassOf<UHorizonButton>> BackgroundButtonClass;
public: //for tag <img>, ignore case
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (DisplayThumbnail = "true", AllowedClasses = "Texture2D"))
		TSoftObjectPtr<UTexture2D> Texture2D = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (DisplayThumbnail = "true", AllowedClasses = "Material"))
		TSoftObjectPtr<UMaterial> Material = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (DisplayThumbnail = "true"))
		TSoftObjectPtr<UPaperSprite> PaperSprite = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TSoftObjectPtr<USoundBase> DialogueSound = nullptr;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TArray<float> DialogueSoundVolumeMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TArray<float> DialogueSoundPitchMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TArray<float> DialogueSoundStartTime;

public: //for tag <pfb> or <PaperFlipBook>, ignore case
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbook", meta = (DisplayThumbnail = "true", DisplayName = "PaperFlipbook", AllowedClasses = "PaperFlipbook"))
		TSoftObjectPtr<UPaperFlipbook> PaperFlipbook = nullptr;

public:
	//image size for Texture2D, Material or PaperFlipbook
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	TArray<FVector2D> ImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RubyText")
	FHorizonDialogueSegmentInfoRubyTextStyle RubyTextStyleInfo;
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, AutoExpandCategories = (StyleList))
class HORIZONUI_API UHorizonDialogueStyleInfo: public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StyleList", meta = (TitleProperty = "StyleName"))
	TArray<FHorizonDialogueSegmentInfoStyle> SegmentStyleList;


public:
#if WITH_EDITOR
	//~ Begin UObject Interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	//~ End UObject Interface
#endif
};
