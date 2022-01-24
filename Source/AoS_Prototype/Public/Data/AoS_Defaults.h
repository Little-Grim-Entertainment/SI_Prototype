// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Defaults.generated.h"

USTRUCT(BlueprintType)
struct FColorDefaults
{
	GENERATED_BODY()

	// Color  0Palette
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Palette Colors")
	TArray<FSlateColor> AccentColors;
	
};

USTRUCT(BlueprintType)
struct FFontStyles
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fonts")
	FSlateFontInfo HeaderFontStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fonts")
	FSlateFontInfo HoverHeaderFontStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fonts")
	FSlateFontInfo SecondaryFontStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fonts")
	FSlateFontInfo HoverSecondaryFontStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fonts")
	FSlateFontInfo ParagraphFontStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fonts")
	FSlateFontInfo HoverParagraphFontStyle;
};

UENUM(BlueprintType)
enum EFontStyle
{
	FS_Header     UMETA(DisplayName = "Header"),
	FS_HeaderHover      UMETA(DisplayName = "HeaderHover"),
	FS_Secondary   UMETA(DisplayName = "Secondary"),
	FS_SecondaryHover   UMETA(DisplayName = "SecondaryHover"),
	FS_Paragraph   UMETA(DisplayName = "Paragraph"),
};

UCLASS()
class AOS_PROTOTYPE_API UAoS_Defaults : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors")
	FColorDefaults Colors;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fonts")
	FFontStyles Fonts;
};
