// Copyright 2023, PROTOWLF, All Rights Reserved


#include "ProtoRichTextBlock.h"
#include "Engine/Font.h"
#include "Styling/SlateStyle.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Editor/WidgetCompilerLog.h"
#include "TimerManager.h"


#define LOCTEXT_NAMESPACE "UMG"


UProtoRichTextBlock::UProtoRichTextBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UProtoRichTextBlock::ReleaseSlateResources( bool bReleaseChildren )
{
	Super::ReleaseSlateResources(bReleaseChildren);

	TextLayout.Reset();
}


void UProtoRichTextBlock::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	FullText = GetText();
}


void UProtoRichTextBlock::PrintLetterByLetter()
{
	check(GetWorld());
	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(LetterTimer);
	
	CurrentCharacterIndex = -1;
	CurrentCharColorDecoratorCharacterIndex = -1;
	CurrentPrintBlockIndex = 0;

	// First Prepass gets the Marshaller and TextLayout ready
	// (Necessary to let PlayLetterByLetter() be called on the same frame as creation)
	ForceLayoutPrepass();

	InitializePrintBlocks();

	if (FullText.IsEmpty())
	{
		// No text to print, stop immediately
		StopLetterByLetterPrint(true);
	}
	else
	{
		// Start Letter By Letter printing
		HideText();
		

		LetterByLetterPrintInProgress = true;
		
		LastCharacterTimestamp = GetWorld()->GetTimeSeconds();
		LastCharacterSpecialCharacter = GetSpecialCharacter(CurrentPrintBlockIndex, 0);
		LastCharacterPrintInterval = GetLetterPrintInterval( CurrentPrintBlockIndex, LastCharacterSpecialCharacter );

		if ( LastCharacterPrintInterval > 0.0f )
		{
			FTimerDelegate Delegate;
			Delegate.BindUObject(this, &ThisClass::PlayNextLetter);
			TimerManager.SetTimer(LetterTimer, Delegate, LastCharacterPrintInterval, false);
		}
		else
		{
			PlayNextLetter();
		}

		OnBeginLetterByLetterPrint.Broadcast();
	}
}


void UProtoRichTextBlock::HideText()
{
	// Do pre-pass first to fix edge-cases where a pre-pass would happen later in the frame, wiping the decorator's text
	ForceLayoutPrepass();

	InitializePrintBlocks();
	
	// Hide all text, then unhide blocks with "donthide"
	CharColorDecorator->HideText();
	for ( FProtoTextPrintBlock PrintBlock : PrintBlocks )
	{
		if ( PrintBlock.HasCharColorDecorator && PrintBlock.DontHide )
		{
			CharColorDecorator->ShowTextAtCharacter(PrintBlock.OriginalCharColorDecoratorStringBeginIndex);
		}
	}

	// Hide all widgets, then unhide blocks with "donthide"
	WidgetDecorator->HideWidgets();
	for ( FProtoTextPrintBlock PrintBlock : PrintBlocks )
	{
		if ( PrintBlock.HasWidgetDecorator && PrintBlock.DontHide )
		{
			WidgetDecorator->ShowWidgetAtIndex( PrintBlock.WidgetIndex );
		}
	}

	// Hide all images, then unhide blocks with "donthide"
	ImageDecorator->HideImages();
	for ( FProtoTextPrintBlock PrintBlock : PrintBlocks )
	{
		if ( PrintBlock.HasImageDecorator && PrintBlock.DontHide )
		{
			ImageDecorator->ShowImageAtIndex( PrintBlock.ImageIndex );
		}
	}

	if ( LetterByLetterPrintInProgress )
	{
		StopLetterByLetterPrint();
	}
}


void UProtoRichTextBlock::ShowText()
{
	// Do pre-pass first to fix edge-cases where a pre-pass would happen later in the frame, wiping the decorator's text
	ForceLayoutPrepass();
	CharColorDecorator->ShowText();
	WidgetDecorator->ShowWidgets();
	ImageDecorator->ShowImages();

	if (LetterByLetterPrintInProgress)
	{
		StopLetterByLetterPrint();
	}
}


void UProtoRichTextBlock::PlayNextLetter()
{
	// Print multiple letters in the case where the print interval is smaller than the frame time
	float timeSinceLastLetter = FMath::Max( GetWorld()->GetTimeSeconds() - LastCharacterTimestamp, LastCharacterPrintInterval );
	bool printFinished = false;
	int numLettersThisFrame = 0;
	bool isLongerThanNormalWait = false;

	ForceLayoutPrepass();

	// If last character was a pause, send the resume event
	if ( LastCharacterHadPauseEvent )
	{
		LastCharacterHadPauseEvent = false;
		OnResumeLetterByLetterPrint.Broadcast();
	}

	while ( timeSinceLastLetter >= LastCharacterPrintInterval && !printFinished )
	{
		// Note: CurrentCharacterIndex has not been incremented yet for our next character we're printing
		// It is incremented inside CalculateNextLetterByLetterCharacter()
		if (CurrentCharacterIndex + 1 < TotalContentCharacters)
		{
			numLettersThisFrame++;
			int32 ThisPrintBlockIndex = CurrentPrintBlockIndex; // Cache this, because it might get incremented in CalculateNextLetterByLetterCharacter()
			CalculateNextLetterByLetterCharacter();

			if ( PrintBlocks[ThisPrintBlockIndex].DontHide )
			{
				// Hidden block, skip this character
				timeSinceLastLetter -= LastCharacterPrintInterval;
				LastCharacterSpecialCharacter = GetSpecialCharacter( ThisPrintBlockIndex, CurrentCharacterIndex );
				LastCharacterPrintInterval = 0.0f;
			}
			else
			{
				// Print the current character

				if ( PrintBlocks[ThisPrintBlockIndex].HasCharColorDecorator )
				{
					// Animate the letter printing
					// Adjust the elapsedAnimationTime by the timeWaited from last PlayNextLetter call
					if ( PrintBlocks[ThisPrintBlockIndex].HasCharColorDecorator )
					{
						float elapsedAnimationTime = FMath::Max( timeSinceLastLetter - LastCharacterPrintInterval, 0.0f );
						CharColorDecorator->SetCurrentLetterByLetterCharacter( CurrentCharColorDecoratorCharacterIndex, GetLetterAnimationTime( ThisPrintBlockIndex ), elapsedAnimationTime );
					}
				}
				else if ( PrintBlocks[ThisPrintBlockIndex].HasWidgetDecorator )
				{
					// Make the widget appear
					WidgetDecorator->ShowWidgetAtIndex( PrintBlocks[ThisPrintBlockIndex].WidgetIndex );
				}
				else if ( PrintBlocks[ThisPrintBlockIndex].HasImageDecorator )
				{
					// Make the image appear
					ImageDecorator->ShowImageAtIndex( PrintBlocks[ThisPrintBlockIndex].ImageIndex );
				}

				timeSinceLastLetter -= LastCharacterPrintInterval;
				LastCharacterSpecialCharacter = GetSpecialCharacter( ThisPrintBlockIndex, CurrentCharacterIndex );
				LastCharacterPrintInterval = GetLetterPrintInterval( ThisPrintBlockIndex, LastCharacterSpecialCharacter );
				
				if ( LastCharacterPrintInterval > GetLetterPrintInterval( ThisPrintBlockIndex, EProtoRichTextSpecialCharacter::PRT_NONE ) )
				{
					isLongerThanNormalWait = true;
				}
			}
		}
		else
		{
			printFinished = true;
			FinishLetterByLetterPrint();
		}
	}

	// Only broadcast OnPrintLetter once per frame
	if ( numLettersThisFrame > 0 )
	{
		const bool IsEndOfSentence = ( LastCharacterSpecialCharacter == EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE ) || ( CurrentCharacterIndex + 1 == TotalContentCharacters );
		OnPrintLetter.Broadcast( LastCharacterSpecialCharacter, IsEndOfSentence );
	}

	// Set timer for next letter
	if ( !printFinished )
	{
		// Adjust interval based on leftover time since last letter
		LastCharacterPrintInterval -= timeSinceLastLetter;

		FTimerDelegate Delegate;
		Delegate.BindUObject(this, &ThisClass::PlayNextLetter);
		GetWorld()->GetTimerManager().SetTimer(LetterTimer, Delegate, LastCharacterPrintInterval, false);
		LastCharacterTimestamp = GetWorld()->GetTimeSeconds();

		// If we're waiting longer than the standard time for the next character print,
		// send the paused event
		if ( isLongerThanNormalWait )
		{
			LastCharacterHadPauseEvent = true;
			OnPauseLetterByLetterPrint.Broadcast();
		}
	}
}


void UProtoRichTextBlock::SetText( const FText& InText )
{
	if (MyRichTextBlock.IsValid())
	{
		if (MyRichTextBlock->GetText().CompareTo(InText) != 0)
		{
			// We only reset the decorator's cached data if setting to new text.
			// For whatever reason, Slate doesn't recreate decorators if doing a SetText
			// with the same Text it already had, so if we reset our decorator
			// it will not be recreated.
			CharColorDecorator->ResetCachedDecorator();
			WidgetDecorator->ResetCachedWidgets();
			ImageDecorator->ResetCachedImages();

			//ForceLayoutPrepass might not create images and widgets if these are not called
			if (TextLayout.IsValid())
			{
				TextLayout->DirtyLayout();
			}
			if (TextMarshaller.IsValid())
			{
				TextMarshaller->MakeDirty();
			}
		}
	}

	Super::SetText( InText );
	FullText = InText;
	PrintBlocksInitialized = false;

	if (LetterByLetterPrintInProgress)
	{
		StopLetterByLetterPrint();
	}
}


void UProtoRichTextBlock::InitializePrintBlocks()
{
	// Only initialize print blocks if we need to
	if ( PrintBlocksInitialized )
	{
		return;
	}

	TotalContentCharacters = 0;
	PrintBlocks.Empty();

	if (TextLayout.IsValid())
	{
		const FGeometry& TextBoxGeometry = GetCachedGeometry();
		const FVector2D TextBoxSize = TextBoxGeometry.GetLocalSize();

		if ( AutoWrapText )
		{
			TextLayout->SetWrappingWidth(TextBoxSize.X);
		}
		else
		{
			TextLayout->SetWrappingWidth(0.0f);
		}
		
		// Index into full content string (markup removed)
		int32 nextContentCharacterIndex = 0;

		// Index into full content string for just char color decorators
		int32 nextCharColorDecoratorCharacterIndex = 0;

		int32 numWidgetsFound = 0;
		int32 numImagesFound = 0;

		TArray< FTextLayout::FLineView > LineViews = TextLayout->GetLineViews();
		for (int lineIndex = 0; lineIndex < LineViews.Num(); lineIndex++ )
		{
			const FTextLayout::FLineView& View = LineViews[lineIndex];
			const FTextLayout::FLineModel& Model = TextLayout->GetLineModels()[View.ModelIndex];

			for (int blockIndex = 0; blockIndex < View.Blocks.Num(); blockIndex++ )
			{
				const TSharedRef<ILayoutBlock> Block = View.Blocks[blockIndex];
				const TSharedRef<IRun> Run = Block->GetRun();

				FProtoTextPrintBlock PrintBlock;
				PrintBlock.StartOfNewLine = blockIndex == 0 ? true : false;

				PrintBlock.RunInfo = Run->GetRunInfo();
				InitializePrintBlockExtraStyleData( PrintBlock );
				PrintBlock.HasCharColorDecorator = UProtoRichTextCharColorDecorator::CheckMarkupName( PrintBlock.RunInfo.Name );

				PrintBlock.HasWidgetDecorator = UProtoRichTextWidgetDecorator::CheckMarkupName( PrintBlock.RunInfo.Name );
				if ( PrintBlock.HasWidgetDecorator )
				{
					PrintBlock.WidgetIndex = numWidgetsFound;
					numWidgetsFound++;
				}

				PrintBlock.HasImageDecorator = UProtoRichTextImageDecorator::CheckMarkupName( PrintBlock.RunInfo.Name );
				if ( PrintBlock.HasImageDecorator )
				{
					PrintBlock.ImageIndex = numImagesFound;
					numImagesFound++;
				}

				FTextRange PrintBlockTextRange = Block->GetTextRange();
				Run->AppendTextTo(PrintBlock.Text, PrintBlockTextRange);
				
				if ( PrintBlock.HasWidgetDecorator || PrintBlock.HasImageDecorator )
				{
					// Widget or Image decorator block. Always treat as 1 characterr
					PrintBlock.Text.Empty();
					TotalContentCharacters += 1;
					nextContentCharacterIndex += 1;
				}
				else if ( PrintBlock.Text.Len() == 0 || (PrintBlock.Text.Len() == 1 && PrintBlock.Text[0] == 0x200B) )
				{
					// This block is either empty, or is a decorator with nothing inside.
					// Treat as 1 character
					PrintBlock.Text.Empty();
					TotalContentCharacters += 1;
					nextContentCharacterIndex += 1;
				}
				else if ( PrintBlock.Text.Len() > 0 )
				{
					// This block has text
					PrintBlock.OriginalContentStringBeginIndex = nextContentCharacterIndex;
					nextContentCharacterIndex += PrintBlockTextRange.Len();

					if ( PrintBlock.HasCharColorDecorator )
					{
						PrintBlock.OriginalCharColorDecoratorStringBeginIndex = nextCharColorDecoratorCharacterIndex;
						nextCharColorDecoratorCharacterIndex += PrintBlockTextRange.Len();
					}

					TotalContentCharacters += PrintBlock.Text.Len();
				}

				// Check additional metadata
				PrintBlock.DontHide = false;
				if ( PrintBlock.RunInfo.MetaData.Contains( TEXT("donthide") ) )
				{
					PrintBlock.DontHide = true;
				}

				PrintBlocks.Add(PrintBlock);
			}
		}

		TextLayout->SetWrappingWidth(0);
	}
	else
	{
		PrintBlocks.Add(FProtoTextPrintBlock{FullText.ToString()});
		TotalContentCharacters = PrintBlocks[0].Text.Len();
	}
}


void UProtoRichTextBlock::InitializePrintBlockExtraStyleData(FProtoTextPrintBlock &InOutPrintBlock)
{
	InOutPrintBlock.ExtraStyleData = DefaultExtraStyleData;

	if ( !InOutPrintBlock.RunInfo.Name.IsEmpty() )
	{
		
		if (UProtoRichTextCharColorDecorator::CheckMarkupName(InOutPrintBlock.RunInfo.Name))
		{
			// This print block is using a proto charcolor decorator
			// This decorator has text style in metadata

			for (const TTuple<FString, FString>& MetaData : InOutPrintBlock.RunInfo.MetaData)
			{
				if ( MetaData.Key == TEXT( "style" ) || MetaData.Key == TEXT( "s" ) )
				{
					// This metadata is this print block's text style
					FName styleName = FName( *MetaData.Value );
					if ( ExtraStyleData.Contains( styleName ) )
					{
						InOutPrintBlock.ExtraStyleData = *ExtraStyleData.Find( styleName );
					}
				}
			}
		}
		else
		{
			// This print block is a normal RichTextBlock text run
			// The run name is the text style

			FName styleName = FName( *InOutPrintBlock.RunInfo.Name );
			if ( ExtraStyleData.Contains( styleName ) )
			{
				InOutPrintBlock.ExtraStyleData = *ExtraStyleData.Find( styleName );
			}
		}
	}
}


int32 UProtoRichTextBlock::CalculateNextLetterByLetterCharacter()
{
	int32 GoalLetterIndex = CurrentCharacterIndex + 1;
	while (CurrentCharacterIndex < GoalLetterIndex && CurrentPrintBlockIndex < PrintBlocks.Num())
	{
		const FProtoTextPrintBlock& PrintBlock = PrintBlocks[CurrentPrintBlockIndex];
		bool printBlockComplete = false;

		if ( PrintBlock.HasCharColorDecorator )
		{
			// Text

			if ( CurrentCharacterIndex - PrintBlock.OriginalContentStringBeginIndex == 0 )
			{
				// First character of this print block, send event
				OnNewBlockLetterByLetterPrint.Broadcast( GetPrintBlockStyleName( PrintBlock ) );
			}

			CurrentCharacterIndex++;
			CurrentCharColorDecoratorCharacterIndex++;
			if ( CurrentCharacterIndex - PrintBlock.OriginalContentStringBeginIndex == PrintBlock.Text.Len() - 1 )
			{
				printBlockComplete = true;
			}
		}
		else if ( PrintBlock.HasWidgetDecorator || PrintBlock.HasImageDecorator )
		{
			// Widget or Image

			// We treat this as printing 1 character
			CurrentCharacterIndex++;
			printBlockComplete = true;
		}
		else if ( PrintBlock.Text.IsEmpty() )
		{
			// PrintBlock is empty, treat as 1 character
			printBlockComplete = true;
			CurrentCharacterIndex++;
		}
		else
		{
			// Something else, so it can't do a printout.
			// Skip, but also update CurrentCharacterIndex
			CurrentCharacterIndex += PrintBlock.Text.Len();
			printBlockComplete = true;
		}

		if (printBlockComplete)
		{
			CurrentPrintBlockIndex++;
		}
	}

	return CurrentCharacterIndex;
}


EProtoRichTextSpecialCharacter UProtoRichTextBlock::GetSpecialCharacter( const int32 InPrintBlockIndex, const int32 InCharacterIndex )
{
	PrintBlocks.RangeCheck( InPrintBlockIndex );
	const FProtoTextPrintBlock PrintBlock = PrintBlocks[InPrintBlockIndex];
	
	if ( PrintBlock.ExtraStyleData.UseAdvancedPrintIntervals )
	{
		const int32 printBlockCharacterIndex = InCharacterIndex - PrintBlock.OriginalContentStringBeginIndex;
		const FString character = PrintBlock.Text.Mid( printBlockCharacterIndex, 1 );

		if ( character == TEXT( "," ) )
		{
			return EProtoRichTextSpecialCharacter::PRT_COMMA;
		}
		else if ( character == TEXT( " " ) )
		{
			return EProtoRichTextSpecialCharacter::PRT_SPACE;
		}
		else if ( character == TEXT( "!" ) || character == TEXT( "?" ) )
		{
			// Must have a space after to be the end of a sentence
			if ( printBlockCharacterIndex + 1 < PrintBlock.Text.Len() )
			{
				// Check next character in print block
				FString nextCharacter = PrintBlock.Text.Mid( printBlockCharacterIndex + 1, 1 );
				if ( nextCharacter.IsEmpty() || nextCharacter == TEXT( " " ) )
				{
					return EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE;
				}
			}
			else if ( InPrintBlockIndex + 1 < PrintBlocks.Num() && PrintBlocks[InPrintBlockIndex + 1].Text.Len() > 0 )
			{
				// Check first character of next print block
				FString nextCharacter = PrintBlocks[InPrintBlockIndex + 1].Text.Mid( 0, 1 );
				if ( nextCharacter.IsEmpty() || nextCharacter == TEXT( " " ) || PrintBlocks[InPrintBlockIndex + 1].StartOfNewLine )
				{
					return EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE;
				}
			}
			else
			{
				// It was the last character of the last print block, count it as end of sentence
				return EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE;
			}
		}
		else if ( character == TEXT( "." ) )
		{
			// Check if it's an ellipsis (we'll count the last . of an ellipsis as end of sentence though)
			if ( printBlockCharacterIndex + 1 < PrintBlock.Text.Len() )
			{
				// Check next character in print block
				FString nextCharacter = PrintBlock.Text.Mid( printBlockCharacterIndex + 1, 1 );
				if ( nextCharacter == TEXT( "." ) )
				{
					return EProtoRichTextSpecialCharacter::PRT_ELLIPSIS;
				}
			}
			else if ( InPrintBlockIndex + 1 < PrintBlocks.Num() && PrintBlocks[InPrintBlockIndex + 1].Text.Len() > 0 )
			{
				// Check first character of next print block
				FString nextCharacter = PrintBlocks[InPrintBlockIndex + 1].Text.Mid( 0, 1 );
				if ( nextCharacter.IsEmpty() || nextCharacter == TEXT( "." ) )
				{
					return EProtoRichTextSpecialCharacter::PRT_ELLIPSIS;
				}
			}
			
			// Must have a space after to be the end of a sentence
			if ( printBlockCharacterIndex + 1 < PrintBlock.Text.Len() )
			{
				// Check next character in print block
				FString nextCharacter = PrintBlock.Text.Mid( printBlockCharacterIndex + 1, 1 );
				if ( nextCharacter.IsEmpty() || nextCharacter == TEXT( " " ) )
				{
					return EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE;
				}
			}
			else if ( InPrintBlockIndex + 1 < PrintBlocks.Num() && PrintBlocks[InPrintBlockIndex + 1].Text.Len() > 0 )
			{
				// Check first character of next print block
				FString nextCharacter = PrintBlocks[InPrintBlockIndex + 1].Text.Mid( 0, 1 );
				if ( nextCharacter.IsEmpty() || nextCharacter == TEXT( " " ) || PrintBlocks[InPrintBlockIndex + 1].StartOfNewLine )
				{
					return EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE;
				}
			}
			else
			{
				// It was the last character of the last print block, count it as end of sentence
				return EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE;
			}
		}
		else if ( character == TEXT( "-" ) )
		{
			// Only a mid-word dash if the next character is not a space
			bool foundNextCharacter = false;
			FString nextCharacter;
			if ( printBlockCharacterIndex + 1 < PrintBlock.Text.Len() )
			{
				// Check next character in print block
				foundNextCharacter = true;
				nextCharacter = PrintBlock.Text.Mid( printBlockCharacterIndex + 1, 1 );
			}
			else if ( InPrintBlockIndex + 1 < PrintBlocks.Num() && PrintBlocks[InPrintBlockIndex + 1].Text.Len() > 0 )
			{
				// Check first character of next print block
				foundNextCharacter = true;
				nextCharacter = PrintBlocks[InPrintBlockIndex + 1].Text.Mid( 0, 1 );
			}
			
			if ( foundNextCharacter )
			{
				if ( !nextCharacter.IsEmpty() && nextCharacter != TEXT( " " ) )
				{
					return EProtoRichTextSpecialCharacter::PRT_MIDWORDDASH;
				}
			}
		}
	}

	return EProtoRichTextSpecialCharacter::PRT_NONE;
}


TSharedRef<SWidget> UProtoRichTextBlock::RebuildWidget()
{
	// Similar to URichTextBlock::RebuildWidget

	// Stomp these decorators no matter what.
	// Workaround for a UI Editor issue where creating UWidgets by dragging into the 2d view will add child UObjects to the Widget
	// in some way that causes them to be created early in-game.
	InstanceDecorators.Reset();
	CharColorDecorator = nullptr;
	WidgetDecorator = nullptr;
	ImageDecorator = nullptr;
	
	UpdateStyleData();

	// Automatically create our required decorators (unless we found user specified ones in UpdateStyleData())
	if ( !CharColorDecorator )
	{
		CharColorDecorator = NewObject<UProtoRichTextCharColorDecorator>(this, UProtoRichTextCharColorDecorator::StaticClass());
		InstanceDecorators.Add( CharColorDecorator );
	}

	if ( !WidgetDecorator )
	{
		WidgetDecorator = NewObject<UProtoRichTextWidgetDecorator>(this, UProtoRichTextWidgetDecorator::StaticClass());
		WidgetDecorator->SetWidgetSet( WidgetSet );
		InstanceDecorators.Add( WidgetDecorator );
	}
	
	if ( !ImageDecorator )
	{
		ImageDecorator = NewObject<UProtoRichTextImageDecorator>(this, UProtoRichTextImageDecorator::StaticClass());
		ImageDecorator->SetImageSet( ImageSet );
		InstanceDecorators.Add( ImageDecorator );
	}

	TArray< TSharedRef< class ITextDecorator > > CreatedDecorators;
	CreateDecorators(CreatedDecorators);

	TextMarshaller = FRichTextLayoutMarshaller::Create(CreateMarkupParser(), CreateMarkupWriter(), CreatedDecorators, StyleInstance.Get());

	// Hate disabling deprecation warnings, but following Epic's lead from RichTextBlock.cpp. Getting non-const DefaultTextStyleOverride and DefaultTextStyle is troublesome.
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	MyRichTextBlock =
		SNew(SRichTextBlock)
		.TextStyle(bOverrideDefaultStyle ? &DefaultTextStyleOverride : &DefaultTextStyle)
		.Marshaller(TextMarshaller)
		.CreateSlateTextLayout(
			FCreateSlateTextLayout::CreateWeakLambda(this, [this] (SWidget* InOwner, const FTextBlockStyle& InDefaultTextStyle) mutable
			{
				TextLayout = FSlateTextLayout::Create(InOwner, InDefaultTextStyle);
				return StaticCastSharedPtr<FSlateTextLayout>(TextLayout).ToSharedRef();
			}));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
	return MyRichTextBlock.ToSharedRef();
}


void UProtoRichTextBlock::FinishLetterByLetterPrint()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(LetterTimer);
	LetterByLetterPrintInProgress = false;

	OnFinishLetterByLetterPrint.Broadcast(false);
}


void UProtoRichTextBlock::StopLetterByLetterPrint(const bool NoEvent)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(LetterTimer);
	LetterByLetterPrintInProgress = false;

	if ( !NoEvent )
	{
		OnFinishLetterByLetterPrint.Broadcast(true);
	}
}


float UProtoRichTextBlock::GetLetterPrintInterval(const int32 InPrintBlockIndex, const EProtoRichTextSpecialCharacter InSpecialCharacter)
{
	if ( OverridePrintLetterInterval )
	{
		return PrintLetterInterval;
	}
	else
	{
		PrintBlocks.RangeCheck( InPrintBlockIndex );
		const FProtoTextPrintBlock PrintBlock = PrintBlocks[InPrintBlockIndex];

		if ( PrintBlock.ExtraStyleData.UseAdvancedPrintIntervals )
		{
			if ( InSpecialCharacter == EProtoRichTextSpecialCharacter::PRT_NONE )
			{
				return PrintBlocks[InPrintBlockIndex].ExtraStyleData.PrintLetterInterval;
			}
			else if ( InSpecialCharacter == EProtoRichTextSpecialCharacter::PRT_COMMA )
			{
				return PrintBlocks[InPrintBlockIndex].ExtraStyleData.CommaInterval;
			}
			else if ( InSpecialCharacter == EProtoRichTextSpecialCharacter::PRT_SPACE )
			{
				return PrintBlocks[InPrintBlockIndex].ExtraStyleData.SpaceInterval;
			}
			else if ( InSpecialCharacter == EProtoRichTextSpecialCharacter::PRT_ENDOFSENTENCE )
			{
				return PrintBlocks[InPrintBlockIndex].ExtraStyleData.SentenceInterval;
			}
			else if ( InSpecialCharacter == EProtoRichTextSpecialCharacter::PRT_ELLIPSIS )
			{
				return PrintBlocks[InPrintBlockIndex].ExtraStyleData.EllipsisInterval;
			}
			else if ( InSpecialCharacter == EProtoRichTextSpecialCharacter::PRT_MIDWORDDASH )
			{
				return PrintBlocks[InPrintBlockIndex].ExtraStyleData.MidWordDashInterval;
			}
		}

		return PrintBlocks[InPrintBlockIndex].ExtraStyleData.PrintLetterInterval;
	}
}


float UProtoRichTextBlock::GetLetterAnimationTime(const int32 InPrintBlockIndex)
{
	if ( OverridePrintLetterAnimationTime )
	{
		return PrintLetterAnimationTime;
	}
	else
	{
		PrintBlocks.RangeCheck( InPrintBlockIndex );
		return PrintBlocks[InPrintBlockIndex].ExtraStyleData.PrintLetterAnimationTime;
	}
}


FName UProtoRichTextBlock::GetPrintBlockStyleName( const FProtoTextPrintBlock &InPrintBlock )
{
	if ( InPrintBlock.RunInfo.Name.IsEmpty() )
	{
		return FName( TEXT( "None" ) );
	}
	
	if ( InPrintBlock.HasCharColorDecorator )
	{
		// This print block is using a proto charcolor decorator
		// This decorator has text style in metadata

		for (const TTuple<FString, FString>& MetaData : InPrintBlock.RunInfo.MetaData)
		{
			if ( MetaData.Key == TEXT( "style" ) || MetaData.Key == TEXT( "s" ) )
			{
				// This metadata is this print block's text style
				return FName( *MetaData.Value );
			}
		}
	}
	else
	{
		// This print block is a normal RichTextBlock text run
		// The run name is the text style

		return FName( *InPrintBlock.RunInfo.Name );
	}

	return FName( TEXT( "None" ) );
}


void UProtoRichTextBlock::SetPrintLetterIntervalOverride( const float InOverridePrintLetterInterval )
{
	OverridePrintLetterInterval = true;
	PrintLetterInterval = InOverridePrintLetterInterval;
}


void UProtoRichTextBlock::ClearPrintLetterIntervalOverride()
{
	OverridePrintLetterInterval = false;
}


void UProtoRichTextBlock::BindWidgetEvents( UProtoRichTextUserWidget* ProtoUserWidget, const FName& WidgetName )
{
	ProtoUserWidget->OnClicked.AddDynamic( this, &UProtoRichTextBlock::HandleWidgetClicked );
	ProtoUserWidget->OnPressed.AddDynamic( this, &UProtoRichTextBlock::HandleWidgetPressed );
	ProtoUserWidget->OnReleased.AddDynamic( this, &UProtoRichTextBlock::HandleWidgetReleased );
	ProtoUserWidget->OnHovered.AddDynamic( this, &UProtoRichTextBlock::HandleWidgetHovered );
	ProtoUserWidget->OnUnhovered.AddDynamic( this, &UProtoRichTextBlock::HandleWidgetUnhovered );
}


void UProtoRichTextBlock::UpdateStyleData()
{
	if (!StyleInstance.IsValid())
	{
		// Call RebuildProtoStyleInstance() after RebuildStyleInstance(), use the StyleInstance there
		RebuildStyleInstance();
		RebuildProtoStyleInstance();

		for (TSubclassOf<URichTextBlockDecorator> DecoratorClass : DecoratorClasses)
		{
			if (UClass* ResolvedClass = DecoratorClass.Get())
			{
				if (!ResolvedClass->HasAnyClassFlags(CLASS_Abstract))
				{
					URichTextBlockDecorator* Decorator = NewObject<URichTextBlockDecorator>(this, ResolvedClass);
					InstanceDecorators.Add(Decorator);

					// If the user manually specifies one of our automatically created decorators, use that instead
					if ( Decorator->IsA( UProtoRichTextCharColorDecorator::StaticClass() ) )
					{
						check( !CharColorDecorator ); // Hit once in Daydream
						CharColorDecorator = Cast<UProtoRichTextCharColorDecorator>( Decorator );
					}
					else if ( Decorator->IsA( UProtoRichTextWidgetDecorator::StaticClass() ) )
					{
						check( !WidgetDecorator );
						WidgetDecorator = Cast<UProtoRichTextWidgetDecorator>( Decorator );
					}
					else if ( Decorator->IsA( UProtoRichTextImageDecorator::StaticClass() ) )
					{
						check( !ImageDecorator );
						ImageDecorator = Cast<UProtoRichTextImageDecorator>( Decorator );
					}
				}
			}
		}
	}
}


void UProtoRichTextBlock::RebuildProtoStyleInstance()
{
	// Piggybacking off of URichTextBlock::RebuildStyleInstance()
	// Take the StyleInstance created there, and if ProtoTextStyleSet is defined, stomp its data
	// Also pull FProtoExtraStyleData out of ProtoTextStyleSet
	if (ProtoTextStyleSet && ProtoTextStyleSet->GetRowStruct()->IsChildOf(FProtoRichTextStyleRow::StaticStruct()))
	{
		for (const auto& Entry : ProtoTextStyleSet->GetRowMap())
		{
			FName SubStyleName = Entry.Key;
			FProtoRichTextStyleRow* ProtoRichTextStyleRow = (FProtoRichTextStyleRow*)Entry.Value;

			// Set the Text Style
			StyleInstance->Set(SubStyleName, ProtoRichTextStyleRow->TextStyle);

			// Set the extra properties from ProtoRichTextStyleRow
			FProtoExtraStyleData extraData;
			extraData.PrintLetterAnimationTime = ProtoRichTextStyleRow->PrintLetterAnimationTime;
			extraData.PrintLetterInterval = ProtoRichTextStyleRow->PrintLetterInterval;
			extraData.UseAdvancedPrintIntervals = ProtoRichTextStyleRow->UseAdvancedPrintIntervals;
			extraData.CommaInterval = ProtoRichTextStyleRow->CommaInterval;
			extraData.SentenceInterval = ProtoRichTextStyleRow->SentenceInterval;
			extraData.EllipsisInterval = ProtoRichTextStyleRow->EllipsisInterval;
			extraData.MidWordDashInterval = ProtoRichTextStyleRow->MidWordDashInterval;
			extraData.SpaceInterval = ProtoRichTextStyleRow->SpaceInterval;
			ExtraStyleData.Add( SubStyleName, extraData );

			if (SubStyleName == FName(TEXT("Default")))
			{
				DefaultTextStyle = ProtoRichTextStyleRow->TextStyle;
				DefaultExtraStyleData = extraData;
			}
		}
	}
}


void UProtoRichTextBlock::SetProtoTextStyleSet(class UDataTable* NewTextStyleSet)
{
	if (ProtoTextStyleSet != NewTextStyleSet)
	{
		ProtoTextStyleSet = NewTextStyleSet;

		RebuildStyleInstance();

		if (MyRichTextBlock.IsValid())
		{
			MyRichTextBlock->SetDecoratorStyleSet(StyleInstance.Get());
			MyRichTextBlock->SetTextStyle(DefaultTextStyle);
		}
	}
}


#if WITH_EDITOR

void UProtoRichTextBlock::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if ( TextStyleSet )
	{
		CompileLog.Warning(FText::Format(
			LOCTEXT("ProtoRichTextBlock_WrongTextStyleField", "{0} Do not use the Text Style Set property. Use the Proto Text Style Set property instead."), 
			FText::FromString(GetName())));
	}

	if (ProtoTextStyleSet && !ProtoTextStyleSet->GetRowStruct()->IsChildOf(FProtoRichTextStyleRow::StaticStruct()))
	{
		CompileLog.Warning(FText::Format(
			LOCTEXT("ProtoRichTextBlock_InvalidTextStyle", "{0} Proto Text Style Set property expects a Data Table with a Proto Rich Text Style Row structure (currently set to {1})."), 
			FText::FromString(GetName()), 
			FText::AsCultureInvariant(TextStyleSet->GetPathName())));
	}
}

#endif //if WITH_EDITOR

