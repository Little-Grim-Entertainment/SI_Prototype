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
#include "ProtoRichTextWidgetDecorator.generated.h"


class ISlateStyle;


/** Simple struct for rich text styles */
USTRUCT(Blueprintable, BlueprintType)
struct FProtoRichWidgetRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	// The Blueprint-created widget to display in-line
	UPROPERTY(EditAnywhere, Category = Appearance)
	TSubclassOf<UUserWidget> WidgetClass;

	// The typography baseline for this widget. 0 means the bottom of the widget is at the baseline of surrounding text.
	// Positive values raise the widget up (likely pushing surrounding text down), negative values do the opposite.
	UPROPERTY( EditAnywhere, Category = Appearance )
	float Baseline = 0;
};


USTRUCT()
struct FProtoDecoratorWidgetInfo
{
	GENERATED_BODY()

	FProtoDecoratorWidgetInfo()
	{
	}

	FProtoDecoratorWidgetInfo( UUserWidget *InWidget, FName &InName )
		: Widget(InWidget)
		, Name(InName)
	{
	}

	UPROPERTY( Instanced )
	UUserWidget* Widget;

	FName Name;
};


/**
 * Allows you to setup a widget decorator in-line in rich text.
 * We recommend you subclass this
 * as a blueprint to configure the instance.
 *
 * Understands the format <widget id="NameOfWidgetInTable"></>
 */
UCLASS()
class PROTOANIMATEDTEXT_API UProtoRichTextWidgetDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()

public:

	static bool CheckMarkupName( const FString& InString )
	{
		return ( InString == TEXT("widget") || InString == TEXT("w") );
	}

	UProtoRichTextWidgetDecorator(const FObjectInitializer& ObjectInitializer);

	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;

	virtual const TSubclassOf<UUserWidget> FindWidgetClass(FName TagOrId, bool bWarnIfMissing);

	virtual void ShowWidgets();

	virtual void HideWidgets();

	/** Sets a specific widget (relative to creation order) visible
	* Called by UProtoRichTextBlock as part of letter-by-letter printing
	*/
	virtual void ShowWidgetAtIndex( const int32 InWidgetIndex);

	// Widget (TODO: array) created by ProtoRichTextWidgetDecorator, for inline widgets
	UPROPERTY()
	TArray<FProtoDecoratorWidgetInfo> DecoratorWidgets;

	void SetWidgetSet( UDataTable* InWidgetSet )
	{
		WidgetSet = InWidgetSet;
	}

	// Called by ProtoRichText when its Text content changes
	void ResetCachedWidgets();

protected:

	FProtoRichWidgetRow* FindWidgetRow(FName TagOrId, bool bWarnIfMissing);

	FSlateWidgetRun::FWidgetRunInfo CreateWidgetCallback(const FTextRunInfo& RunInfo, const ISlateStyle* Style );

	UUserWidget* CreateInLineWidget(const TSubclassOf<UUserWidget> WidgetClass, const FName &MetaDataName);

	UPROPERTY(EditAnywhere, Category=Appearance, meta = (RequiredAssetDataTags = "RowStructure=FProtoRichWidgetRow"))
	class UDataTable* WidgetSet;

	bool HasInvalidWidgets = false;
};
