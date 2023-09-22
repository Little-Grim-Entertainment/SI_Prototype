// Copyright 2023, PROTOWLF, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateTypes.h"
#include "Framework/Text/TextLayout.h"
#include "Framework/Text/ISlateRun.h"
#include "Framework/Text/ITextDecorator.h"
#include "Components/RichTextBlockDecorator.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Text/TextDecorators.h"
#include "ProtoAnimatedText.h"
#include "ProtoRichTextImageDecorator.generated.h"


class ISlateStyle;
class FProtoImageDecorator;


/** Simple struct for rich text styles */
USTRUCT(Blueprintable, BlueprintType)
struct FProtoRichImageRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	// The Image to display
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush Brush;

	// The typography baseline for this image. 0 means the bottom of the image is at the baseline of surrounding text.
	// Positive values raise the image up (likely pushing surrounding text down), negative values do the opposite.
	UPROPERTY( EditAnywhere, Category = Appearance )
	float Baseline = 0;
};


/**
 * Allows you to setup an image decorator in-line in proto rich text
 * Supports the ProtoRichText printout, and tweakable baseline
 * 
 * Understands the format <image id="NameOfImageInTable"></>
 */
UCLASS()
class PROTOANIMATEDTEXT_API UProtoRichTextImageDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()

public:

	static bool CheckMarkupName( const FString& InString )
	{
		return (InString == TEXT("image") || InString == TEXT("img") || InString == TEXT("i"));
	}

	UProtoRichTextImageDecorator(const FObjectInitializer& ObjectInitializer);

	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;

	virtual FProtoRichImageRow* FindImageRow(FName TagOrId, bool bWarnIfMissing);

	virtual void ShowImages();

	virtual void HideImages();

	/** Sets a specific widget (relative to creation order) visible
	* Called by UProtoRichTextBlock as part of letter-by-letter printing
	*/
	virtual void ShowImageAtIndex( const int32 InImageIndex);

	void SetImageSet( UDataTable* InImageSet )
	{
		ImageSet = InImageSet;
	}

	// Called by ProtoRichText when its Text content changes
	void ResetCachedImages();

protected:

	UPROPERTY(EditAnywhere, Category=Appearance, meta = (RequiredAssetDataTags = "RowStructure=ProtoRichImageRow"))
	class UDataTable* ImageSet;

	FProtoImageDecorator* FDecorator;
};
