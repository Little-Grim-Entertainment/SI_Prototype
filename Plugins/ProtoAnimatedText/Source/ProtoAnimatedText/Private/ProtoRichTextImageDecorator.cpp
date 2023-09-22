// Copyright 2023, PROTOWLF, All Rights Reserved

#include "ProtoRichTextImageDecorator.h"
#include "UObject/SoftObjectPtr.h"
#include "Rendering/DrawElements.h"
#include "Framework/Text/SlateTextRun.h"
#include "Framework/Text/SlateTextLayout.h"
#include "Slate/SlateGameResources.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Framework/Application/SlateApplication.h"
#include "Fonts/FontMeasure.h"
#include "Math/UnrealMathUtility.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SBox.h"
#include "Misc/DefaultValueHelper.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "ProtoRichTextBlock.h"
#include "ProtoRichTextUserWidget.h"
#include "Framework/Text/SlateImageRun.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"


#define LOCTEXT_NAMESPACE "UMG"


// FProtoImageDecorator
/////////////////////////////////////
#pragma region FProtoSlateImageRun

class FProtoSlateImageRun : public FSlateImageRun
{
public:

	static TSharedRef< FProtoSlateImageRun > Create( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FSlateBrush* InImage, int16 InBaseline, const FTextRange& InRange )
	{
		if ( InImage == nullptr)
		{
			InImage = FStyleDefaults::GetNoBrush();
		}
		
		return MakeShareable( new FProtoSlateImageRun( InRunInfo, InText, InImage, InBaseline, InRange ) );
	}


	virtual int32 OnPaint( const FPaintArgs& PaintArgs, const FTextArgs& TextArgs, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override
	{
		// The block size and offset values are pre-scaled, so we need to account for that when converting the block offsets into paint geometry
		const float InverseScale = Inverse(AllottedGeometry.Scale);

		if ( ProtoImage->DrawAs != ESlateBrushDrawType::NoDrawType )
		{
			FLinearColor FinalColorAndOpacity( InWidgetStyle.GetColorAndOpacityTint() * ProtoImage->GetTint( InWidgetStyle ) );
			FinalColorAndOpacity.A *= RenderOpacity;
			const ESlateDrawEffect DrawEffects = bParentEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
			FSlateDrawElement::MakeBox(
				OutDrawElements, 
				++LayerId, 
				AllottedGeometry.ToPaintGeometry(TransformVector(InverseScale, TextArgs.Block->GetSize()), FSlateLayoutTransform(TransformPoint(InverseScale, TextArgs.Block->GetLocationOffset()))),
				ProtoImage, 
				DrawEffects, 
				FinalColorAndOpacity
				);
		}

		return LayerId;
	}


	void SetRenderOpacity( const float InOpacity )
	{
		RenderOpacity = InOpacity;
	}


protected:

	FProtoSlateImageRun( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FSlateBrush* InImage, int16 InBaseline, const FTextRange& InRange )
		: FSlateImageRun(InRunInfo, InText, InImage, InBaseline, InRange )
	{
		ProtoImage = InImage;
	}

	// For some reason FSlateImageRun makes its variables private, so we save an extra copy of the image
	// to do what we need in OnPaint.
	const FSlateBrush* ProtoImage;

	float RenderOpacity = 1.0f;
};
#pragma endregion FProtoSlateImageRun


// FProtoImageDecorator
/////////////////////////////////////
#pragma region FProtoImageDecorator

class FProtoImageDecorator : public ITextDecorator
{
public:

	FProtoImageDecorator(UProtoRichTextImageDecorator* InDecorator)
		: Decorator(InDecorator)
	{
	}

	virtual ~FProtoImageDecorator() {}

public:

	virtual bool Supports( const FTextRunParseResults& RunParseResult, const FString& Text ) const override
	{
		return UProtoRichTextImageDecorator::CheckMarkupName( RunParseResult.Name );
	}


	virtual TSharedRef< ISlateRun > Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef< FString >& InOutModelText, const ISlateStyle* Style) override
	{
		FRunInfo RunInfo(RunParseResult.Name);
		for (const TPair<FString, FTextRange>& Pair : RunParseResult.MetaData)
		{
			RunInfo.MetaData.Add(Pair.Key, OriginalText.Mid(Pair.Value.BeginIndex, Pair.Value.EndIndex - Pair.Value.BeginIndex));
		}

		FTextRange ModelRange;
		ModelRange.BeginIndex = InOutModelText->Len();
		*InOutModelText += TEXT('\u200B'); // Zero-Width Breaking Space
		ModelRange.EndIndex = InOutModelText->Len();

		if (RunInfo.MetaData.Contains(TEXT("id")))
		{
			

			const bool bWarnIfMissing = true;
			FProtoRichImageRow* imageRow = Decorator->FindImageRow(*RunInfo.MetaData[TEXT("id")], bWarnIfMissing);
			if (imageRow)
			{
				const FInlineTextImageStyle& ImageStyle = FInlineTextImageStyle::GetDefault();
				//return FSlateImageRun::Create( RunInfo, InOutModelText, &imageRow->Brush, imageRow->Baseline, ModelRange );
				TSharedRef< FProtoSlateImageRun > ImageRun = FProtoSlateImageRun::Create(RunInfo, InOutModelText, &imageRow->Brush, imageRow->Baseline, ModelRange);
				ImageRuns.Add(ImageRun);
				return ImageRun;
			}
		}
		
		// If we get here something went wrong, fallback:
		HasInvalidImages = true;
		TSharedRef< SWidget > Widget = SNew( SButton ) 
			[
				SNew( STextBlock )
				.Text( LOCTEXT( "InvalidImageWidget", "INVALID IMAGE!" ) )
			];
		TSharedPtr<ISlateRun> SlateRun;
		FSlateWidgetRun::FWidgetRunInfo WidgetRunInfo(Widget, 0);
		SlateRun = FSlateWidgetRun::Create(TextLayout, RunInfo, InOutModelText, WidgetRunInfo, ModelRange);
		return SlateRun.ToSharedRef();;
	}


	void ShowImages()
	{
		for ( TSharedRef< FProtoSlateImageRun > ImageRun : ImageRuns )
		{
			ImageRun->SetRenderOpacity( 1.0f );
		}
	}
	
	
	void HideImages()
	{
		for ( TSharedRef< FProtoSlateImageRun > ImageRun : ImageRuns )
		{
			ImageRun->SetRenderOpacity( 0.0f );
		}
	}
	
	
	void ShowImageAtIndex( int32 InImageIndex )
	{
		if ( !HasInvalidImages )
		{
			ImageRuns.RangeCheck( InImageIndex );
			ImageRuns[InImageIndex]->SetRenderOpacity( 1.0f );
		}
	}


	void ResetCachedImages()
	{
		ImageRuns.Empty();
		HasInvalidImages = false;
	}


protected:

	TArray<TSharedRef< FProtoSlateImageRun >> ImageRuns;

	UProtoRichTextImageDecorator* Decorator;

	bool HasInvalidImages = false;

};
#pragma endregion FProtoImageDecorator


// UProtoRichTextImageDecorator
/////////////////////////////////////
#pragma region UProtoRichTextImageDecorator

UProtoRichTextImageDecorator::UProtoRichTextImageDecorator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


FProtoRichImageRow* UProtoRichTextImageDecorator::FindImageRow(FName TagOrId, bool bWarnIfMissing)
{
	if (ImageSet)
	{
		FString ContextString;
		return ImageSet->FindRow<FProtoRichImageRow>(TagOrId, ContextString, bWarnIfMissing);
	}
	
	return nullptr;
}


TSharedPtr<ITextDecorator> UProtoRichTextImageDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	FDecorator = new FProtoImageDecorator(this);
	return MakeShareable(FDecorator);
}


void UProtoRichTextImageDecorator::ShowImages()
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextImageDecorator tried to show all images, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->ShowImages();
}


void UProtoRichTextImageDecorator::HideImages()
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextImageDecorator tried to hide all images, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->HideImages();
}


void UProtoRichTextImageDecorator::ShowImageAtIndex( int32 InImageIndex )
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextImageDecorator tried to show an image at index %i, but the decorator was undefined!"), InImageIndex);
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->ShowImageAtIndex( InImageIndex );
}


void UProtoRichTextImageDecorator::ResetCachedImages()
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextImageDecorator tried to reset cached images, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->ResetCachedImages();
}
#pragma endregion UProtoRichTextImageDecorator

#undef LOCTEXT_NAMESPACE
