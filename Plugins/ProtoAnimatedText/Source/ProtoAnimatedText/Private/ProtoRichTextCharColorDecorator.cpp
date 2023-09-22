// Copyright 2023, PROTOWLF, All Rights Reserved

#include "ProtoRichTextCharColorDecorator.h"
#include "Framework/Text/DefaultLayoutBlock.h"
#include "Framework/Text/ShapedTextCache.h"
#include "Fonts/FontCache.h"


// FProtoCharColorTextRun
/////////////////////////////////////
#pragma region FProtoCharColorTextRun

// Vertex color data will be packed between this percentage and 1.0
#define VERTEXCOLOR_MINDATAVALUE 0.1f
// Vertex color data will step by this much between characters (note: smaller steps introduce banding, probably gamma related)
#define VERTEXCOLOR_STEPS 50


struct ProtoCharColorInfo
{
	ProtoCharColorInfo( FLinearColor InColor)
		: Color(InColor)
	{
	}
	FLinearColor Color;
	float printAnimationTime = 0; // Time in seconds this character takes to animate in a letter-by-letter print animation
	double printAnimationStartTime = 0; // Time the animation started ( FPlatformTime::Seconds()! NOT game time!)
};


class FProtoCharColorTextRun : public FSlateTextRun
{
public:

	static TSharedRef< FProtoCharColorTextRun > Create( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FTextBlockStyle& Style, const FTextRange& InRange, const int32 InOriginalContentRangeBegin )
	{
		return MakeShareable( new FProtoCharColorTextRun( InRunInfo, InText, Style, InRange, InOriginalContentRangeBegin ) );
	}

	FProtoCharColorTextRun( const FRunInfo& InRunInfo, const TSharedRef< const FString >& InText, const FTextBlockStyle& InStyle, const FTextRange& InRange, const int32 InOriginalContentRangeBegin )
		: FSlateTextRun( InRunInfo, InText, InStyle, InRange )
	{
		// Generate color values for each character and cache for use in OnPaint
		CharactersBeginIndex = InRange.BeginIndex;
		CharactersOriginalContentBeginIndex = InOriginalContentRangeBegin;
		int32 numberOfCharacters = InRange.Len();
		FMath::SRandInit( 1029384756 );
		for ( int32 i = 0; i < numberOfCharacters; i++ )
		{
			// Colorize this character, packing channels with info for a font material.
			// * R Channel: in order from 0.0 to 1.0 in uniform increments. Restarts at 0.0 at VERTEXCOLOR_STEPS characters
			// * G Channel: random value
			// * B Channel: letter-by-letter print anim progress (set by SetCurrentLetterByLetterCharacter())
			// * A Channel: set to 0.0 or 1.0 by letter-by-letter print (set by SetCurrentLetterByLetterCharacter())
			//
			// Notes:
			// * We DO NOT use the RGB tint from the containing widget -- we want the color data to be consistent.
			// * We DO use the alpha from the containing widget -- we still want the text to fade with its parent.
			// * Color the outline and shadow the same RGB color as the text -- they need the same data for font materials.
			// * Maintain the alpha of the outline and shadow from the style
			FLinearColor styleColor = InStyle.ColorAndOpacity.GetSpecifiedColor();
			FLinearColor characterColor = FLinearColor( 0.0f, 0.0f, 0.0f, styleColor.A);
			characterColor.R = VERTEXCOLOR_MINDATAVALUE + (( i % (VERTEXCOLOR_STEPS) ) * ((1.0f - VERTEXCOLOR_MINDATAVALUE) / VERTEXCOLOR_STEPS));
			characterColor.G = VERTEXCOLOR_MINDATAVALUE + ((1.0f - VERTEXCOLOR_MINDATAVALUE) * FMath::SRand());
			characterColor.B = 1.0f;
			characterColor.A = 1.0f;

			CharacterColors.Add( ProtoCharColorInfo( characterColor ) );
		}

		OutlineAlpha = InStyle.Font.OutlineSettings.OutlineColor.A;
		ShadowAlpha = InStyle.ShadowColorAndOpacity.A;
	}

	
	virtual int32 OnPaint( const FPaintArgs& PaintArgs, const FTextArgs& TextArgs, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override
	{
		// Just like FSlateTextRun::OnPaint, but we chop up the string per-character and loop the paint for all characters
		
		const ESlateDrawEffect DrawEffects = bParentEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		const bool ShouldDropShadow = Style.ShadowColorAndOpacity.A > 0.f && Style.ShadowOffset.SizeSquared() > 0.f;
		const FVector2D BlockLocationOffset = TextArgs.Block->GetLocationOffset();
		FTextRange BlockRange = TextArgs.Block->GetTextRange();
		const FLayoutBlockTextContext BlockTextContext = TextArgs.Block->GetTextContext();
		
		// The block size and offset values are pre-scaled, so we need to account for that when converting the block offsets into paint geometry
		const float InverseScale = Inverse(AllottedGeometry.Scale);

		// A negative shadow offset should be applied as a positive offset to the text to avoid clipping issues
		const FVector2D DrawShadowOffset(
			(Style.ShadowOffset.X > 0.0f) ? Style.ShadowOffset.X * AllottedGeometry.Scale : 0.0f, 
			(Style.ShadowOffset.Y > 0.0f) ? Style.ShadowOffset.Y * AllottedGeometry.Scale : 0.0f
			);
		const FVector2D DrawTextOffset(
			(Style.ShadowOffset.X < 0.0f) ? -Style.ShadowOffset.X * AllottedGeometry.Scale : 0.0f, 
			(Style.ShadowOffset.Y < 0.0f) ? -Style.ShadowOffset.Y * AllottedGeometry.Scale : 0.0f
			);

		const int32 numCharacters = BlockRange.Len();
		const int32 firstCharacterindex = BlockRange.BeginIndex;
		FVector2D characterOffset = FVector2D(0.0f, 0.0f);
		for ( int i = 0; i < numCharacters; i++ )
		{
			// Single out the range for this character
			BlockRange.BeginIndex = firstCharacterindex + i;
			BlockRange.EndIndex = BlockRange.BeginIndex + 1;

			// Animate the Blue value based on letter-by-letter animation (if necessary)
			int32 charColorIndex = (firstCharacterindex - CharactersBeginIndex) + i;
			float blueValue = CharacterColors[charColorIndex].Color.B;
			if ( CharacterColors[charColorIndex].printAnimationTime > 0.0f )
			{
				blueValue = VERTEXCOLOR_MINDATAVALUE + ( (1.0f - VERTEXCOLOR_MINDATAVALUE) * ( (1.0f / CharacterColors[charColorIndex].printAnimationTime) * ( PaintArgs.GetCurrentTime() - CharacterColors[charColorIndex].printAnimationStartTime ) ) );
				blueValue = FMath::Clamp( blueValue, VERTEXCOLOR_MINDATAVALUE, 1.0f );
			}

			// Get the final colors for this character (and its outline/shadow)
			const FLinearColor characterColor = FLinearColor( CharacterColors[charColorIndex].Color.R, CharacterColors[charColorIndex].Color.G, blueValue, CharacterColors[charColorIndex].Color.A * InWidgetStyle.GetColorAndOpacityTint().A );

			

			const FLinearColor characterOutlineColor = FLinearColor( characterColor.R, characterColor.G, characterColor.B, CharacterColors[charColorIndex].Color.A * OutlineAlpha * InWidgetStyle.GetColorAndOpacityTint().A );
			const FLinearColor characterShadowColor = FLinearColor( characterColor.R, characterColor.G, characterColor.B, CharacterColors[charColorIndex].Color.A * ShadowAlpha * InWidgetStyle.GetColorAndOpacityTint().A );

			// Make sure we have up-to-date shaped text to work with
			// We use the full line view range (rather than the run range) so that text that spans runs will still be shaped correctly
			FShapedGlyphSequenceRef ShapedText = ShapedTextCacheUtil::GetShapedTextSubSequence(
				BlockTextContext.ShapedTextCache,
				FCachedShapedTextKey(TextArgs.Line.Range, AllottedGeometry.GetAccumulatedLayoutTransform().GetScale(), BlockTextContext, Style.Font ),
				BlockRange,
				**Text,
				BlockTextContext.TextDirection
			);

			// Draw the optional shadow
			if ( ShouldDropShadow )
			{
				FShapedGlyphSequenceRef ShadowShapedText = ShapedText;
				if ( Style.ShadowColorAndOpacity != Style.Font.OutlineSettings.OutlineColor )
				{
					// Copy font info for shadow to replace the outline color
					FSlateFontInfo ShadowFontInfo = Style.Font;
					ShadowFontInfo.OutlineSettings.OutlineColor = Style.ShadowColorAndOpacity;
					ShadowFontInfo.OutlineSettings.OutlineMaterial = nullptr;
					if ( !ShadowFontInfo.OutlineSettings.bApplyOutlineToDropShadows )
					{
						ShadowFontInfo.OutlineSettings.OutlineSize = 0;
					}

					// Create new shaped text for drop shadow
					ShadowShapedText = ShapedTextCacheUtil::GetShapedTextSubSequence(
						BlockTextContext.ShapedTextCache,
						FCachedShapedTextKey( TextArgs.Line.Range, AllottedGeometry.GetAccumulatedLayoutTransform().GetScale(), BlockTextContext, ShadowFontInfo ),
						BlockRange,
						**Text,
						BlockTextContext.TextDirection
					);
				}

				FSlateDrawElement::MakeShapedText(
					OutDrawElements,
					++LayerId,
					AllottedGeometry.ToPaintGeometry( TransformVector( InverseScale, TextArgs.Block->GetSize() ), FSlateLayoutTransform( TransformPoint( InverseScale, TextArgs.Block->GetLocationOffset() + DrawShadowOffset + characterOffset ) ) ),
					ShadowShapedText,
					DrawEffects,
					//InWidgetStyle.GetColorAndOpacityTint() * Style.ShadowColorAndOpacity,
					//InWidgetStyle.GetColorAndOpacityTint() * Style.Font.OutlineSettings.OutlineColor
					characterShadowColor,
					characterShadowColor
				);
			}

			// Draw the text itself
			FSlateDrawElement::MakeShapedText(
				OutDrawElements,
				++LayerId,
				AllottedGeometry.ToPaintGeometry( TransformVector( InverseScale, TextArgs.Block->GetSize() ), FSlateLayoutTransform( TransformPoint( InverseScale, TextArgs.Block->GetLocationOffset() + DrawTextOffset + characterOffset ) ) ),
				ShapedText,
				DrawEffects,
				//InWidgetStyle.GetColorAndOpacityTint() * Style.ColorAndOpacity.GetColor( InWidgetStyle ),
				//InWidgetStyle.GetColorAndOpacityTint() * Style.Font.OutlineSettings.OutlineColor
				characterColor,
				characterOutlineColor
			);

			characterOffset.X += ShapedText->GetMeasuredWidth();
		}

		return LayerId;
	}

	void SetCurrentLetterByLetterCharacter( int32 charIndex, float animationTimeSeconds, float elapsedAnimationTime )
	{
		// Valid for the currentCharIndex to be out of range, because it could be
		// a character from another run
		int32 currentCharIndex = charIndex - CharactersOriginalContentBeginIndex;
		if ( CharacterColors.IsValidIndex( currentCharIndex ) )
		{
			// Set values that will allow us to adjust the Blue value in OnPaint
			CharacterColors[currentCharIndex].printAnimationTime = animationTimeSeconds;
			CharacterColors[currentCharIndex].printAnimationStartTime = FPlatformTime::Seconds() - static_cast<double>(elapsedAnimationTime);
			CharacterColors[currentCharIndex].Color.A = 1.0f;
		}
	}

	void ClearLetterByLetterAnimations()
	{
		for ( int i = 0; i < CharacterColors.Num(); i++ )
		{
			CharacterColors[i].printAnimationTime = 0.0f;
			CharacterColors[i].printAnimationStartTime = 0.0;
		}
	}

	// Set alpha of all characters from 0.0 to 1.0
	void SetAllCharacterAlpha( float InAlpha )
	{
		for ( int i = 0; i < CharacterColors.Num(); i++ )
		{
			CharacterColors[i].Color.A = InAlpha;
		}
	}

public:

	int32 CharactersOriginalContentBeginIndex = 0; // first character's index in the original full rich text block content (with markup stripped out)

private:

	int32 CharactersBeginIndex = 0; // first character's index in this run's content text. TODO: this seems to always be zero? Not sure why we need this
	TArray<ProtoCharColorInfo> CharacterColors;
	float OutlineAlpha = 1.0f;
	float ShadowAlpha = 1.0f;
};
#pragma endregion FProtoCharColorTextRun


// FProtoRichTextCharColorDecorator
/////////////////////////////////////
#pragma region FProtoRichTextCharColorDecorator
class FProtoRichTextCharColorDecorator : public ITextDecorator
{
public:
	FProtoRichTextCharColorDecorator(URichTextBlockDecorator* InDecorator, const FSlateFontInfo& InDefaultFont, const FLinearColor& InDefaultColor)
		: DefaultFont(InDefaultFont)
		, DefaultColor(InDefaultColor)
		, Decorator(InDecorator)
	{
	}

	virtual ~FProtoRichTextCharColorDecorator() {};

	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override;

	virtual TSharedRef<ISlateRun> Create(const TSharedRef<FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef<FString>& InOutModelText, const ISlateStyle* Style) override;

	void SetCurrentLetterByLetterCharacter( int32 charIndex, float animationTimeSeconds, float elapsedAnimationTime );

	void HideText();

	void ShowText();

	void ShowTextAtCharacter( const int32& InCharacterIndex );

	void ResetCachedDecorator();

protected:

	FTextBlockStyle CreateTextBlockStyle(const FRunInfo& InRunInfo, const ISlateStyle* Style) const;

	void ExplodeRunInfo(const FRunInfo& InRunInfo, FSlateFontInfo& OutFont, FLinearColor& OutFontColor) const;

protected:

	FSlateFontInfo DefaultFont;
	FLinearColor DefaultColor;

	// We need to tell each FProtoCharColorTextRun which character index in the content text they
	// begin at, relative to the original full string. The "content" as in the full rich text string
	// with the markup stripped out.
	// As we create runs, we increment this value to keep track of where the last run ended.
	int32 LastContentCharacterIndex = 0;

private:
	TWeakObjectPtr<URichTextBlockDecorator> Decorator;
	TArray<TSharedPtr<FProtoCharColorTextRun>> TextRuns;
};


bool FProtoRichTextCharColorDecorator::Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const
{
	return UProtoRichTextCharColorDecorator::CheckMarkupName( RunParseResult.Name );
}


TSharedRef<ISlateRun> FProtoRichTextCharColorDecorator::Create(const TSharedRef<FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef<FString>& InOutModelText, const ISlateStyle* Style)
{
	FRunInfo RunInfo(RunParseResult.Name);
	for (const TPair<FString, FTextRange>& Pair : RunParseResult.MetaData)
	{
		RunInfo.MetaData.Add(Pair.Key, OriginalText.Mid(Pair.Value.BeginIndex, Pair.Value.EndIndex - Pair.Value.BeginIndex));
	}

	FTextRange ModelRange;
	int32 RunContentLength = RunParseResult.ContentRange.EndIndex - RunParseResult.ContentRange.BeginIndex;
	ModelRange.BeginIndex = InOutModelText->Len();
	*InOutModelText += OriginalText.Mid(RunParseResult.ContentRange.BeginIndex, RunContentLength );
	ModelRange.EndIndex = InOutModelText->Len();

	TSharedPtr<FProtoCharColorTextRun> ProtoCharColorRun = FProtoCharColorTextRun::Create(RunInfo, InOutModelText, CreateTextBlockStyle(RunInfo, Style), ModelRange, LastContentCharacterIndex);
	TextRuns.Add( ProtoCharColorRun );
	LastContentCharacterIndex += RunContentLength;

	return ProtoCharColorRun.ToSharedRef();
}


FTextBlockStyle FProtoRichTextCharColorDecorator::CreateTextBlockStyle(const FRunInfo& InRunInfo, const ISlateStyle* Style) const
{
	FTextBlockStyle TextBlockStyle;
	TextBlockStyle.SetFont(DefaultFont);
	TextBlockStyle.SetColorAndOpacity(DefaultColor);

	for (const TPair<FString, FString>& Pair : InRunInfo.MetaData)
	{
		if ( Pair.Key == TEXT( "style" ) || Pair.Key == TEXT( "s" ) )
		{
			const FTextBlockStyle* FoundTextBlockStyle = &(Style->GetWidgetStyle< FTextBlockStyle >(FName(*Pair.Value)));
			if ( FoundTextBlockStyle )
			{
				TextBlockStyle.SetFont(FoundTextBlockStyle->Font);
				TextBlockStyle.SetColorAndOpacity(FoundTextBlockStyle->ColorAndOpacity);
			}
		}
	}

	return TextBlockStyle;
}


void FProtoRichTextCharColorDecorator::ExplodeRunInfo(const FRunInfo& InRunInfo, FSlateFontInfo& OutFont, FLinearColor& OutFontColor) const
{
	OutFont = DefaultFont;

	const FString* const FontFamilyString = InRunInfo.MetaData.Find(TEXT("font"));
	const FString* const FontSizeString = InRunInfo.MetaData.Find(TEXT("size"));
	const FString* const FontStyleString = InRunInfo.MetaData.Find(TEXT("style"));
	const FString* const FontColorString = InRunInfo.MetaData.Find(TEXT("color"));

	if (FontFamilyString)
	{
		FSoftObjectPath Font(**FontFamilyString);
		if (UObject* FontAsset = Font.TryLoad())
		{
			OutFont.FontObject = FontAsset;
		}
	}

	if (FontSizeString)
	{
		OutFont.Size = static_cast<uint8>(FPlatformString::Atoi(**FontSizeString));
	}

	if (FontStyleString)
	{
		OutFont.TypefaceFontName = FName(**FontStyleString);
	}

	OutFontColor = DefaultColor;
	if (FontColorString)
	{
		const FString& FontColorStringRef = *FontColorString;

		// Is Hex color?
		if (!FontColorStringRef.IsEmpty() && FontColorStringRef[0] == TCHAR('#'))
		{
			OutFontColor = FLinearColor(FColor::FromHex(FontColorStringRef));
		}
		else if (OutFontColor.InitFromString(*FontColorString))
		{
			// Initialized
		}
		else
		{
			OutFontColor = DefaultColor;
		}
	}
}


void FProtoRichTextCharColorDecorator::SetCurrentLetterByLetterCharacter( int32 charIndex, float animationTimeSeconds, float elapsedAnimationTime )
{
	for ( int i = 0; i < TextRuns.Num(); i++ )
	{
		TextRuns[i]->SetCurrentLetterByLetterCharacter( charIndex, animationTimeSeconds, elapsedAnimationTime );
	}
}


void FProtoRichTextCharColorDecorator::HideText()
{
	for ( int i = 0; i < TextRuns.Num(); i++ )
	{
		TextRuns[i]->SetAllCharacterAlpha(0.0f);
		TextRuns[i]->ClearLetterByLetterAnimations();
	}
}


void FProtoRichTextCharColorDecorator::ShowText()
{
	for ( int i = 0; i < TextRuns.Num(); i++ )
	{
		TextRuns[i]->SetAllCharacterAlpha(1.0f);
		TextRuns[i]->ClearLetterByLetterAnimations();
	}
}


void FProtoRichTextCharColorDecorator::ShowTextAtCharacter( const int32& InCharacterIndex )
{
	for ( int i = 0; i < TextRuns.Num(); i++ )
	{
		if ( TextRuns[i]->CharactersOriginalContentBeginIndex == InCharacterIndex )
		{
			TextRuns[i]->SetAllCharacterAlpha(1.0f);
			TextRuns[i]->ClearLetterByLetterAnimations();
			break;
		}
	}
}


void FProtoRichTextCharColorDecorator::ResetCachedDecorator()
{
	TextRuns.Empty();
	LastContentCharacterIndex = 0;
}

#pragma endregion FProtoRichTextCharColorDecorator


// UProtoRichTextCharColorDecorator
/////////////////////////////////////
#pragma region UProtoRichTextCharColorDecorator
TSharedPtr<ITextDecorator> UProtoRichTextCharColorDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	FSlateFontInfo DefaultFont = InOwner->GetCurrentDefaultTextStyle().Font;
	FLinearColor DefaultColor = InOwner->GetCurrentDefaultTextStyle().ColorAndOpacity.GetSpecifiedColor();
	FDecorator = new FProtoRichTextCharColorDecorator(this, DefaultFont, DefaultColor);
	return MakeShareable(FDecorator);
}


void UProtoRichTextCharColorDecorator::HideText()
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextCharColorDecorator tried HideText, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->HideText();
}


void UProtoRichTextCharColorDecorator::ShowText()
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextCharColorDecorator tried ShowText, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->ShowText();
}


void UProtoRichTextCharColorDecorator::ShowTextAtCharacter( const int32& InCharacterIndex )
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextCharColorDecorator tried ShowTextAtCharacter, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->ShowTextAtCharacter( InCharacterIndex );
}


void UProtoRichTextCharColorDecorator::SetCurrentLetterByLetterCharacter( int32 charIndex, float animationTimeSeconds, float elapsedAnimationTime )
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextCharColorDecorator tried SetCurrentLetterByLetterCharacter, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->SetCurrentLetterByLetterCharacter( charIndex, animationTimeSeconds, elapsedAnimationTime );
}


void UProtoRichTextCharColorDecorator::ResetCachedDecorator()
{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
	if (!FDecorator)
	{
		UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextCharColorDecorator tried to reset cached decorator, but the decorator was undefined!"));
		return;
	}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

	FDecorator->ResetCachedDecorator();
}

#pragma endregion UProtoRichTextCharColorDecorator
