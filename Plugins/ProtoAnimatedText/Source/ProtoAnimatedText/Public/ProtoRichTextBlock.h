// Copyright 2023, PROTOWLF, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "Framework/Text/SlateTextLayout.h"
#include "ProtoRichTextUserWidget.h"
#include "ProtoRichTextCharColorDecorator.h"
#include "ProtoRichTextWidgetDecorator.h"
#include "ProtoRichTextImageDecorator.h"
#include "ProtoRichTextBlock.generated.h"


UENUM(BlueprintType)
enum class EProtoRichTextSpecialCharacter : uint8
{
	PRT_NONE			UMETA(DisplayName="None"),
	PRT_SPACE			UMETA(DisplayName="Space"),
	PRT_COMMA			UMETA(DisplayName="Comma"),
	PRT_MIDWORDDASH		UMETA(DisplayName="MidWordDash"),
	PRT_ENDOFSENTENCE	UMETA(DisplayName="EndOfSentence"),
	PRT_ELLIPSIS		UMETA(DisplayName="Ellipsis")
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProtoRichTextBeginLBLPrintEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProtoRichTextPrintLetterEvent, EProtoRichTextSpecialCharacter, SpecialCharacter, bool, IsEndOfSentence);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextFinishLBLPrintEvent, bool, StoppedEarly);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProtoRichTextPauseLBLPrintEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProtoRichTextResumeLBLPrintEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextNewBlockLBLPrintEvent, FName, BlockStyleName);

// Widget events
// FName param for events, in case user has multiple widgets in 1 rich text block and
// needs to specify which one is transmitting an event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextWidgetClickedEvent, FName, MarkupName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextWidgetPressedEvent, FName, MarkupName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextWidgetReleasedEvent, FName, MarkupName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextWidgetHoverEvent, FName, MarkupName);


/** struct for proto rich text styles in data tables*/
USTRUCT()
struct FProtoRichTextStyleRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle TextStyle;

	/** How many seconds the letter print animation takes when printing letter-by-letter
	* Note: this only affects the data sent to font materials, so this only has an effect
	* if using the CharPrintPercent value from the ProtoRichText_Data node*/
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint)
	float PrintLetterAnimationTime = 0.1f;

	/** How many seconds to wait between letters when printing letter-by-letter */
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint)
	float PrintLetterInterval = 0.05f;

	/** Enable advanced print intervals for certain characters */
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint)
	bool UseAdvancedPrintIntervals = false;

	/** How many seconds to wait after a comma when printing letter-by-letter */
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint, meta = (EditCondition = "UseAdvancedPrintIntervals"))
	float CommaInterval = 0.3f;

	/** How many seconds to wait after a sentence when printing letter-by-letter */
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint, meta = (EditCondition = "UseAdvancedPrintIntervals"))
	float SentenceInterval = 0.5f;

	/** How many seconds to wait after each period in an ellipsis when printing letter-by-letter */
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint, meta = (EditCondition = "UseAdvancedPrintIntervals"))
	float EllipsisInterval = 0.2f;

	/** How many seconds to wait after a dash mid-word when printing letter-by-letter */
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint, meta = (EditCondition = "UseAdvancedPrintIntervals"))
	float MidWordDashInterval = 0.05f;

	/** How many seconds to wait after a spaces when printing letter-by-letter */
	UPROPERTY(EditAnywhere, Category = LetterByLetterPrint, meta = (EditCondition = "UseAdvancedPrintIntervals"))
	float SpaceInterval = 0.0f;
	
};

/** Extra style data beyond what is in FSlateStyleSet 
* This data is read only by UProtoRichTextBlock, and sometimes sent to Proto decorators */
struct FProtoExtraStyleData
{
	float PrintLetterAnimationTime = 0.1f;
	float PrintLetterInterval = 0.05f;
	bool UseAdvancedPrintIntervals = false;
	float CommaInterval = 0.3f;
	float SentenceInterval = 0.5f;
	float EllipsisInterval = 0.2f;
	float MidWordDashInterval = 0.05;
	float SpaceInterval = 0.0f;
};


struct FProtoTextPrintBlock
{
	FString Text;
	FRunInfo RunInfo;
	FProtoExtraStyleData ExtraStyleData;

	// Index into the original content string with markup removed
	int32 OriginalContentStringBeginIndex = 0;

	// Index into the original content string with:
	// * markup removed
	// * runs that are not charcolor decorators removed
	// This is used to communicate with the ProtoRichTextCharColorDecorator
	int32 OriginalCharColorDecoratorStringBeginIndex = 0;
	
	// Note: we set this during InitializePrintBlocks(), but the line wrapping could change if the
	// layout is adjusted. However we only use this bool in GetSpecialCharacter() to check if
	// we're at the end of the sentence, because a manually written newline character is
	// hard to detect without using the original string with markup. In this case, even if
	// text wrapping changes, a false-positive is fine for detecting end of sentence.
	bool StartOfNewLine = false;

	bool HasCharColorDecorator = false;

	// To print widgets out, we just keep track of which widget
	// this PrintBlock contains, out of the total number of widgets in the Rich Text block.
	bool HasWidgetDecorator = false;
	int32 WidgetIndex = 0;

	// To print images out, we just keep track of which image
	// this PrintBlock contains, out of the total number of images in the Rich Text block.
	bool HasImageDecorator = false;
	int32 ImageIndex = 0;

	// Set by "donthide" metadata
	bool DontHide = false;
};


/**
 * 
 */
UCLASS() //hidecategories=("Appearance")
class PROTOANIMATEDTEXT_API UProtoRichTextBlock : public URichTextBlock
{
	GENERATED_BODY()
	
public:
	UProtoRichTextBlock(const FObjectInitializer& ObjectInitializer);

	//virtual void BeginDestroy() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	/**  If true, override the PrintLetterInterval from the Proto Text Style with one specified below*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProtoRichText")
	bool OverridePrintLetterInterval = false;

	/** How many seconds to wait between letters when printing letter-by-letter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProtoRichText", meta = (DisplayAfter = "OverridePrintLetterInterval", EditCondition = "OverridePrintLetterInterval"))
	float PrintLetterInterval = 0.05f;

	/**  If true, override the PrintLetterAnimationTime from the Proto Text Style with one specified below */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProtoRichText")
	bool OverridePrintLetterAnimationTime = false;

	/** How many seconds the letter print animation takes when printing letter-by-letter
	* Note: this only effects the data sent to font materials, so this only has an effect
	* if using the CharPrintPercent value from the ProtoRichText_Data node*/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "ProtoRichText", meta = ( DisplayAfter = "OverridePrintLetterAnimationTime", EditCondition = "OverridePrintLetterAnimationTime" ) )
	float PrintLetterAnimationTime = 0.1f;

	/** The amount of time to wait after finishing the line before actually marking it completed.
	* This helps prevent accidentally progressing dialogue on short lines. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProtoRichText")
	float EndHoldTime = 0.15f;

	/** Text style settings with extra parameters for ProtoRichTextBlock
	* Use this array, NOT TextStyleSet */
	UPROPERTY(EditAnywhere, Category=Appearance, meta=(RequiredAssetDataTags = "RowStructure=/Script/PROTOANIMATEDTEXT.ProtoRichTextStyleRow"))
	class UDataTable* ProtoTextStyleSet;

	UPROPERTY(EditAnywhere, Category=Appearance, meta = (RequiredAssetDataTags = "RowStructure=/Script/PROTOANIMATEDTEXT.ProtoRichWidgetRow"))
	class UDataTable* WidgetSet;

	UPROPERTY(EditAnywhere, Category=Appearance, meta = (RequiredAssetDataTags = "RowStructure=/Script/PROTOANIMATEDTEXT.ProtoRichImageRow"))
	class UDataTable* ImageSet;

	/**
	* Play a letter-by-letter animation revealing the current text in this widget.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProtoRichText")
	virtual void PrintLetterByLetter();

	/**
	* Returns true if this text box is currently printing letter-by-letter.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProtoRichText")
	virtual bool IsLetterByLetterPrintInProgress() const { return LetterByLetterPrintInProgress; }

	/**
	* Sets text alpha to 0.0. Will stop a letter-by-letter print.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProtoRichText")
	virtual void HideText();

	/**
	* Sets text alpha to 1.0. Will stop a letter-by-letter print.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProtoRichText")
	virtual void ShowText();

	/**
	* Helper function to override PrintLetterInterval. Call ClearPrintLetterIntervalOverride to clear.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProtoRichText")
	virtual void SetPrintLetterIntervalOverride( const float InOverridePrintLetterInterval );

	/**
	* Clear override to PrintLetterInterval set by OverridePrintLetterInterval.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProtoRichText")
	virtual void ClearPrintLetterIntervalOverride();

	UFUNCTION(BlueprintCallable, Category = "ProtoRichText")
	virtual void SetProtoTextStyleSet(class UDataTable* NewTextStyleSet);

	virtual void UpdateStyleData() override;
	virtual void RebuildProtoStyleInstance();

#if WITH_EDITOR
	// UWidget interface
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
	// End UWidget interface
#endif

	/**
	 * Directly sets the widget text.
	 * Warning: This will wipe any binding created for the Text property!
	 * @param InText The text to assign to the widget
	 */
	virtual void SetText(const FText& InText) override;

	virtual void SynchronizeProperties() override;

	// Called by ProtoRichTextWidgetDecorator when creating a suitable in-line widget
	virtual void BindWidgetEvents( UProtoRichTextUserWidget* ProtoUserWidget, const FName& WidgetName );


public:

	/** Called when this text begins printing letter-by-letter */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextBeginLBLPrintEvent OnBeginLetterByLetterPrint;

	/** Called each time a character is printed in a letter-by-letter print */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextPrintLetterEvent OnPrintLetter;

	/** Called when this text finishes printing letter-by-letter */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextFinishLBLPrintEvent OnFinishLetterByLetterPrint;

	/** Called when the letter-by-letter print pauses for a long-interval character
	* Depends on settings in your FProtoRichTextStyle.
	* E.G. commas, ends of sentences */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextPauseLBLPrintEvent OnPauseLetterByLetterPrint;

	/** Called when the letter-by-letter print resumes after pausing for a long-interval character
	* Depends on settings in your FProtoRichTextStyle.
	* E.G. commas, ends of sentences */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextResumeLBLPrintEvent OnResumeLetterByLetterPrint;

	/** Called when the letter-by-letter print reaches the first character of a new text
	* block. Provides the name of the Text Style for this block */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextNewBlockLBLPrintEvent OnNewBlockLetterByLetterPrint;


	/** Called when an in-line Widget is clicked.
	* Widget must be a child of ProtoRichTextUserWidget and call CallOnClicked. */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextWidgetClickedEvent OnWidgetClicked;

	/** Called when an in-line Widget is pressed.
	* Widget must be a child of ProtoRichTextUserWidget and call CallOnPressed. */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextWidgetPressedEvent OnWidgetPressed;

	/** Called when an in-line Widget is released.
	* Widget must be a child of ProtoRichTextUserWidget and call CallOnReleased. */
	UPROPERTY(BlueprintAssignable, Category="ProtoRichText|Event")
	FOnProtoRichTextWidgetReleasedEvent OnWidgetReleased;

	/** Called when an in-line Widget is hovered.
	* Widget must be a child of ProtoRichTextUserWidget and call CallOnHovered. */
	UPROPERTY( BlueprintAssignable, Category = "ProtoRichText|Event" )
	FOnProtoRichTextWidgetHoverEvent OnWidgetHovered;

	/** Called when an in-line Widget is un-hovered.
	* Widget must be a child of ProtoRichTextUserWidget and call CallOnUnhovered. */
	UPROPERTY( BlueprintAssignable, Category = "ProtoRichText|Event" )
	FOnProtoRichTextWidgetHoverEvent OnWidgetUnhovered;


protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void StopLetterByLetterPrint(const bool NoEvent = false);

	virtual void PlayNextLetter();

	virtual void FinishLetterByLetterPrint();

	virtual float GetLetterPrintInterval(const int32 InPrintBlockIndex, const EProtoRichTextSpecialCharacter InSpecialCharacter);

	virtual float GetLetterAnimationTime(const int32 InPrintBlockIndex);

	/** Calculates the PrintBlocks array for the current text.
	* Requires a ForceLayoutPrepass() if called on the same frame as creation. */
	virtual void InitializePrintBlocks();

	virtual void InitializePrintBlockExtraStyleData( FProtoTextPrintBlock &InOutPrintBlock );

	virtual int32 CalculateNextLetterByLetterCharacter();

	virtual EProtoRichTextSpecialCharacter GetSpecialCharacter(const int32 InPrintBlockIndex, const int32 InCharacterIndex);

	virtual FName GetPrintBlockStyleName( const FProtoTextPrintBlock &InPrintBlock );


protected:

	UFUNCTION()
	void HandleWidgetClicked( const FName InName )
	{
		OnWidgetClicked.Broadcast(InName);
	}

	UFUNCTION()
	void HandleWidgetPressed( const FName InName )
	{
		OnWidgetPressed.Broadcast(InName);
	}

	UFUNCTION()
	void HandleWidgetReleased( const FName InName )
	{
		OnWidgetReleased.Broadcast(InName);
	}

	UFUNCTION()
	void HandleWidgetHovered( const FName InName )
	{
		OnWidgetHovered.Broadcast(InName);
	}

	UFUNCTION()
	void HandleWidgetUnhovered( const FName InName )
	{
		OnWidgetUnhovered.Broadcast(InName);
	}


protected:

	bool PrintBlocksInitialized = false;

	TSharedPtr<FSlateTextLayout> TextLayout;
	TSharedPtr<FRichTextLayoutMarshaller> TextMarshaller;

	// Special decorators we create automatically and interact with directly
	UPROPERTY(Transient)
	UProtoRichTextCharColorDecorator* CharColorDecorator;

	UPROPERTY(Transient)
	UProtoRichTextWidgetDecorator* WidgetDecorator;

	UPROPERTY(Transient)
	UProtoRichTextImageDecorator* ImageDecorator;

	TArray<FProtoTextPrintBlock> PrintBlocks;

	// Original full Text with markup since the last SetText call
	FText FullText;

	// Used when printing letter-by-letter
	// Index into the full content string (markup removed)
	int32 CurrentCharacterIndex = 0;

	// Used when printing letter-by-letter
	// Index into the full content string (markup removed), but only
	// content contained in ProtoRichTextCharColorDecorator runs
	int32 CurrentCharColorDecoratorCharacterIndex = 0;

	int32 CurrentPrintBlockIndex = 0;
	int32 TotalContentCharacters = 0;

	float LastCharacterTimestamp; // Used to determine if we need to print multiple characters in 1 frame
	float LastCharacterPrintInterval;
	EProtoRichTextSpecialCharacter LastCharacterSpecialCharacter;
	bool LastCharacterHadPauseEvent;

	bool LetterByLetterPrintInProgress = false;

	FTimerHandle LetterTimer;

	TMap<FName, FProtoExtraStyleData> ExtraStyleData;
	FProtoExtraStyleData DefaultExtraStyleData;
};
