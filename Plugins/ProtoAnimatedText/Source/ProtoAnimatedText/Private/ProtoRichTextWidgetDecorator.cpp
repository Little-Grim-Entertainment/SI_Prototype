// Copyright 2023, PROTOWLF, All Rights Reserved

#include "ProtoRichTextWidgetDecorator.h"
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
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"


#define LOCTEXT_NAMESPACE "UMG"


UProtoRichTextWidgetDecorator::UProtoRichTextWidgetDecorator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


const TSubclassOf<UUserWidget> UProtoRichTextWidgetDecorator::FindWidgetClass(FName TagOrId, bool bWarnIfMissing)
{
	const FProtoRichWidgetRow* WidgetRow = FindWidgetRow(TagOrId, bWarnIfMissing);
	if (WidgetRow)
	{
		return WidgetRow->WidgetClass;
	}

	return nullptr;
}


FProtoRichWidgetRow* UProtoRichTextWidgetDecorator::FindWidgetRow(FName TagOrId, bool bWarnIfMissing)
{
	if (WidgetSet)
	{
		FString ContextString;
		return WidgetSet->FindRow<FProtoRichWidgetRow>(TagOrId, ContextString, bWarnIfMissing);
	}
	
	return nullptr;
}


TSharedPtr<ITextDecorator> UProtoRichTextWidgetDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return FWidgetDecorator::Create( TEXT("widget"), FWidgetDecorator::FCreateWidget::CreateUObject(this, &UProtoRichTextWidgetDecorator::CreateWidgetCallback) );
}


FSlateWidgetRun::FWidgetRunInfo UProtoRichTextWidgetDecorator::CreateWidgetCallback( const FTextRunInfo& RunInfo, const ISlateStyle* Style )
{
	if ( RunInfo.MetaData.Contains( TEXT( "id" ) ) )
	{
		FProtoRichWidgetRow* WidgetInfo = FindWidgetRow( *RunInfo.MetaData[TEXT( "id" )], true );
		if ( WidgetInfo )
		{
			TSubclassOf<UUserWidget> WidgetClass = WidgetInfo->WidgetClass;
			float WidgetBaseline = WidgetInfo->Baseline;
			if ( IsValid(WidgetClass) )
			{
				// Check if it already is cached before making a new one
				// If the markup specifies a name, check for the name too. Necessary for two of the same widget class to work
				FName WidgetName = FName();
				bool WidgetHasName = false;
				if ( RunInfo.MetaData.Contains( TEXT( "name" ) ) )
				{
					WidgetName = FName( RunInfo.MetaData[TEXT( "name" )] );
					WidgetHasName = true;
				}
				else if ( RunInfo.MetaData.Contains( TEXT( "n" ) ) )
				{
					WidgetName = FName( RunInfo.MetaData[TEXT( "n" )] );
					WidgetHasName = true;
				}

				//for ( int i = 0; i < DecoratorWidgets.Num(); i++ )
				//{
				//	if (DecoratorWidgets[i].Widget->GetClass() == WidgetClass && (!WidgetHasName || DecoratorWidgets[i].Name == WidgetName))
				//	{
				//		DecoratorWidgets[i].Widget->InvalidateLayoutAndVolatility();
				//		return FSlateWidgetRun::FWidgetRunInfo( DecoratorWidgets[i].Widget->TakeWidget(), WidgetBaseline );
				//	}
				//}

				UUserWidget *CreatedWidget = CreateInLineWidget( WidgetClass, WidgetName );
				if ( CreatedWidget )
				{
					DecoratorWidgets.Add(FProtoDecoratorWidgetInfo(CreatedWidget, WidgetName));
					CreatedWidget->InvalidateLayoutAndVolatility();
					return FSlateWidgetRun::FWidgetRunInfo( CreatedWidget->TakeWidget(), WidgetBaseline );
				}
			}
		}
	}

	// Something went wrong, fallback:
	HasInvalidWidgets = true;
	TSharedRef< SWidget > Widget = SNew( SButton ) 
		[
			SNew( STextBlock )
			.Text( LOCTEXT( "TestWidget", "INVALID WIDGET!" ) )
		];
	return FSlateWidgetRun::FWidgetRunInfo( Widget, 0 );
}


UUserWidget* UProtoRichTextWidgetDecorator::CreateInLineWidget( const TSubclassOf<UUserWidget> WidgetClass, const FName &MetaDataName )
{
	UUserWidget *CreatedWidget = CreateWidget<UUserWidget>( GetWorld(), WidgetClass );

	// If our parent is a ProtoRichTextBlock, and our widget is a ProtoRichTextUserWidget, we can hook up events
	if ( GetOuter()->IsA( UProtoRichTextBlock::StaticClass() ) && CreatedWidget->IsA( UProtoRichTextUserWidget::StaticClass() ) )
	{
		UProtoRichTextUserWidget* ProtoUserWidget = Cast<UProtoRichTextUserWidget>( CreatedWidget );
		ProtoUserWidget->SetMetaDataName( MetaDataName );
		UProtoRichTextBlock* OuterProtoRichText = Cast<UProtoRichTextBlock>( GetOuter() );
		OuterProtoRichText->BindWidgetEvents( ProtoUserWidget, MetaDataName );
	}

	return CreatedWidget;
}


void UProtoRichTextWidgetDecorator::ShowWidgets()
{
	for ( FProtoDecoratorWidgetInfo WidgetInfo : DecoratorWidgets )
	{
		WidgetInfo.Widget->SetRenderOpacity( 1.0f );
		WidgetInfo.Widget->SetVisibility( ESlateVisibility::Visible );
	}
}


void UProtoRichTextWidgetDecorator::HideWidgets()
{
	for ( FProtoDecoratorWidgetInfo WidgetInfo : DecoratorWidgets )
	{
		WidgetInfo.Widget->SetRenderOpacity( 0.0f );
		WidgetInfo.Widget->SetVisibility( ESlateVisibility::Hidden );
	}
}


void UProtoRichTextWidgetDecorator::ShowWidgetAtIndex( int32 InWidgetIndex )
{
	if ( !HasInvalidWidgets )
	{
#if PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS
		if (InWidgetIndex >= DecoratorWidgets.Num())
		{
			UE_LOG(LogProtoAnimatedText, Error, TEXT("UProtoRichTextWidgetDecorator tried to show a widget at index %i, but it was out of range of cached widgets!"), InWidgetIndex);
			return;
		}
#endif // PROTOANIMATEDTEXT_ENABLEDEFENSIVECHECKS

		DecoratorWidgets.RangeCheck( InWidgetIndex );
		DecoratorWidgets[InWidgetIndex].Widget->SetRenderOpacity( 1.0f );
		DecoratorWidgets[InWidgetIndex].Widget->SetVisibility( ESlateVisibility::Visible );
	}
}


void UProtoRichTextWidgetDecorator::ResetCachedWidgets()
{
	DecoratorWidgets.Empty();
	HasInvalidWidgets = false;
}


#undef LOCTEXT_NAMESPACE
