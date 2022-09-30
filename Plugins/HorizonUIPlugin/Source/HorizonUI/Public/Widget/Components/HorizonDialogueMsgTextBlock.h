// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net


#pragma once
#include "CoreMinimal.h"
#include "Framework/Text/TextLayout.h"
#include "Delegates/DelegateCombinations.h"
#include "Tickable.h"

#include "Components/CanvasPanel.h"

#include "Widget/Components/HorizonButton.h"
#include "Widget/HorizonDialogueStyleInfo.h"
#include "HorizonDialogueMsgTextBlock.generated.h"

class UTextBlock;
class UHorizonDialogueMsgTextBlock;
class USoundBase;
class UHorizonImage;
class UHorizonFlipbookWidget;
class UHorizonTextBlock;
class UHorizonDialogueMsgDecorator;


#if 1 //============================Begin DialogueText Enum=============================
UENUM(BlueprintType)
enum class EHorizonDialogueSegmentType :uint8
{
	Invalidated = 0,
	Text,
	NewLine,
	NewPage, //(Paragraph) this is beta feature that not fully tested
	Image,
	PaperFlipbook,
	Material,
	HyperText,
	Custom
};



UENUM(BlueprintType)
enum class EHorizonDialogueTextOverflowWarpMethod_DEPRECATED :uint8
{
	Normal,    // Try get a "word"(use space to determine, for both CJK and non-CJK) and check if can place at current line, if not, move to next line and use BreakAll rule in next line for the "word"
	BreakAll, //  break all word at any place
	Invalidated
};


UENUM(BlueprintType)
enum class EHorizonDialogueTextOverflowWrapMethod :uint8
{
	Normal,    // Try get a "word"(use space to determine, for both CJK and non-CJK) and check if can place at current line, if not, move to next line and use BreakAll rule in next line for the "word"
	BreakAll, //  break all word at any place
};

#endif //============================End DialogueText Enum=============================

#if 1 //============================Begin DialogueText Struct=============================
USTRUCT(BlueprintType)
struct FHorizonDialogueBlockInfo 
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FString MsgText;
	TWeakObjectPtr<UWidget> WidgetWeakPtr;
	TWeakObjectPtr<UWidget> WidgetBackgroundWeakPtr;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FString RubyText;
	TWeakObjectPtr<UTextBlock> RubyTextWeakPtr;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 CurrentCharIndex = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 SegmentReferenceIndex = -1;//index ref to TArray<FHorizonDialogueSegmentInfo> DialogueSegmentInfoList
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FName Name;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FVector2D BlockSize = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FVector2D RubyTextBlockSize = FVector2D::ZeroVector;



};

USTRUCT(BlueprintType)
struct FHorizonDialogueLineInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 CurrentDialogueBlockIndex = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 MaxLineHeight = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 LineWidth = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	TArray<FHorizonDialogueBlockInfo> DialogueBlockInfoList;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FVector2D Position = FVector2D(0, 0);
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	bool bNewPage = false;// should we start new page in next line
};

USTRUCT(BlueprintType)
struct FHorizonDialogueRubyTextInfo
{
	GENERATED_BODY()
public:
	TOptional<FString> Text;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateColor ColorAndOpacity;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateFontInfo Font;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FVector2D ShadowOffset = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateColor ShadowColorAndOpacity;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FMargin PaddingMargin;//padding position for Text
};
// Parse text segment and store it tag info, 
// If no supported tag in input text, then there will have only one segment.
USTRUCT(BlueprintType)
struct FHorizonDialogueSegmentInfo 
{
	GENERATED_BODY()

public:
	FHorizonDialogueSegmentInfo() {};
	

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FString Text;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateColor ColorAndOpacity;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateFontInfo Font;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FVector2D ShadowOffset = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateColor ShadowColorAndOpacity;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	float DialogueMsgSpeed = 0.01f;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	float DialogueMsgWait = 0.0f;
	float CurrentMsgWaitTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FMargin PaddingMargin;//padding position for segment



	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateColor HypertextHoveredColor = FLinearColor(0.0f, 0.0f, 0.73f, 1.0f); //color after clicked 0915BBFF
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FSlateColor HypertextVisitedColor = FLinearColor(0.5f, 0.0f, 0.5f, 1.0f); //color after clicked

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	TSubclassOf<UHorizonButton> BackgroundButtonClass;



	UPROPERTY(BlueprintReadOnly, Category = "Content")
	float DialogueSoundVolumeMultiplier = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	float DialogueSoundPitchMultiplier = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	float DialogueSoundStartTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	USoundBase* DialogueSound = nullptr;


	EHorizonDialogueSegmentType TypeEnum = EHorizonDialogueSegmentType::Invalidated;
	bool bHypertextVisited = false;
	bool bDialogueSoundPlayed = false;
	bool bEventCallbackCalled = false;
	int32 StyleInfoReferenceIndex = -1; //if not -1, will use style in SegmentStyleListFromStyleClass
	int32 SegmentStyleReferenceIndex = -1;
	TOptional<FString> FilePath;
	TOptional<FString> DialogueSoundPath;
	TOptional<FVector2D> ImageSize;
	TOptional<FString> HypertextReference;
	TOptional<FString> EventName;
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FString EventPayload;

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	TArray<FString> Tags;

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FHorizonDialogueRubyTextInfo RubyTextInfo;

};


USTRUCT(BlueprintType)
struct FHorizonDialoguePageInfo
{
	GENERATED_BODY()
public:
	FHorizonDialoguePageInfo() {};
	FHorizonDialoguePageInfo(int32 InStartLineIndex, int32 InEndLineIndex, float InPageHeight)
	: StartLineIndex(InStartLineIndex)
	, EndLineIndex(InEndLineIndex)
	, PageHeight(InPageHeight){}
public:
	int32 StartLineIndex = -1;
	int32 EndLineIndex = -1;
	float PageHeight = 0.0f;
};

USTRUCT(BlueprintType)
struct FHorizonDialogueHypertextResult
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	UHorizonDialogueMsgTextBlock* DialogueMsgTextBlock = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 SegmentIndex = -1;

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 LineIndex = -1;

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	int32 BlockIndex = -1;

	UPROPERTY(BlueprintReadOnly, Category = "Content")
	FString HypertextReference;
	//HypertextReference parsed map
	UPROPERTY(BlueprintReadOnly, Category = "Content")
	TMap<FString, FString> UrlEncodeMap;
};


USTRUCT(BlueprintType)
struct FHorizonDialogueDialoguePageResult
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Content")
		int32 PageIndex = -1;
};

#endif //============================End DialogueText Struct=============================




UCLASS()
class HORIZONUI_API UHorizonDialogueMsgTextBlock :
	public UCanvasPanel,
	public FTickableGameObject
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHorizonHypertextEvent, const FHorizonDialogueHypertextResult&, InResult);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHorizonHypertextEventNative, const FHorizonDialogueHypertextResult&);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHorizonDialogueMsgEvent);
	DECLARE_MULTICAST_DELEGATE(FOnHorizonDialogueMsgEventNative);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHorizonDialoguePageEvent, const FHorizonDialogueDialoguePageResult&, InResult);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHorizonDialoguePageEventNative, const FHorizonDialogueDialoguePageResult&);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHorizonDialogueCustomEvent, const FString&, InEventName, const FHorizonDialogueSegmentInfo&, InSegInfo);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHorizonDialogueCustomEventNative, const FString&, FHorizonDialogueSegmentInfo&);



	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHorizonDialogueCharAdvancedEvent, const FHorizonDialogueBlockInfo&, InCurrentBlockInfo);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHorizonDialogueCharAdvancedEventNative, const FHorizonDialogueBlockInfo&);
	
public:
	UHorizonDialogueMsgTextBlock();

	// Begin UObject
	virtual void PostLoad() override;

	// End UObject

#if 1  //============================Begin Widget override=============================
public:
	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;
	virtual void OnBindingChanged(const FName& Property) override;
	//~ End UWidget Interface
#endif //============================End Widget override=============================

#if WITH_EDITOR
public:
	//~ Begin UWidget Interface
	//#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
	//virtual const FSlateBrush* GetEditorIcon() override;
	//#endif //#if (ENGINE_MAJOR_VERSION <= 4) && (ENGINE_MINOR_VERSION <= 12)
	virtual const FText GetPaletteCategory() override;
	virtual void OnCreationFromPalette() override;
	//~ End UWidget Interface

	virtual FString GetLabelMetadata() const override;

	void HandleTextCommitted(const FText& InText, ETextCommit::Type CommitteType);

	//~ Begin UObject Interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	//~ End UObject Interface
#endif

#if 1  //============================Begin Tick=============================
public://FTickableGameObject override
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UHorizonDialogueMsgTextBlock, STATGROUP_Tickables); }
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickableInEditor() const override { return true; }
protected:
	virtual void TickRepeatDialogue(float DeltaTime);
#endif //============================End Tick=============================


#if 1 //============================Begin DialogueText Method=============================
public: 
	/**
	* Sets the color and opacity of the text in this text block
	*
	* @param InColorAndOpacity		The new text color and opacity
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetColorAndOpacity(FSlateColor InColorAndOpacity);

	/**
	* Sets the opacity of the text in this text block
	*
	* @param InOpacity		The new text opacity
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetOpacity(float InOpacity);

	/**
	* Sets the color and opacity of the text drop shadow
	* Note: if opacity is zero no shadow will be drawn
	*
	* @param InShadowColorAndOpacity		The new drop shadow color and opacity
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity, bool bForce = false);

	/**
	* Sets the offset that the text drop shadow should be drawn at
	*
	* @param InShadowOffset		The new offset
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetShadowOffset(FVector2D InShadowOffset, bool bForce = false);

	/**
	* Dynamically set the font info for this text block
	*
	* @param InFontInfo THe new font info
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetFont(FSlateFontInfo InFontInfo, bool bForce = false);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetFontSize(int32 fontSize);

	/**
	*  Set the text justification for this text block
	*
	*  @param Justification new justification
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetJustification(ETextJustify::Type InJustification, bool bForce = false);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	FORCEINLINE TEnumAsByte<ETextJustify::Type> GetJustification() const { return Justification; }


	/**
	* Gets the widget text
	* @return The widget text
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg", meta = (DisplayName = "GetText (Text)"))
	FText GetText() const;

	/**
	* Directly sets the widget text.
	* Warning: This will wipe any binding created for the Text property!
	* @param InText The text to assign to the widget
	*/
	//UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|Widget", meta = (DisplayName = "SetText (Text)"))
	virtual void SetText(FText InText);


	/**
	 * Set Text and try Rebuild Dialogue in next widget tick if CachedGeometry().X > 0, retry otherwise
	 *
	 * Move semantics version.
	 *
	 * @param InText: Text want to rebuild
	*/
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetTextAndRebuildDialogue(const FText& InText);

	/**
	 * Set Text and try Rebuild Dialogue in next widget tick if CachedGeometry().X > 0, retry otherwise
	 *
	 * Move semantics version.
	 *
	 * @param InText: Text want to rebuild 
	 */
	virtual void SetTextAndRebuildDialogue(FText&& InText);

#endif //============================End DialogueText Method=============================


#if 1 //============================Begin DialogueMsg: Setter/Getter=============================
public:
	virtual void SetIsRichText(bool b);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetIsDialogueMsgText(bool b);
	FORCEINLINE bool IsDialogueMsgText() { return bIsDialogueMsgText; };

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetDialogueMsgSpeed(float speed, bool bForce = false);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetIsStartTickDialogueMsg(bool bShouldStartTick, bool bShouldResetDialogue = true);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetIsRepeatDialogueMsg(bool b);
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetRepeatDialogueMsgInterval(float interval);

	FORCEINLINE TArray<FHorizonDialogueLineInfo>& GetDialogueLineInfoList() { return DialogueLineInfoList; };
	FORCEINLINE TArray<FHorizonDialoguePageInfo>& GetDialoguePageInfoList() { return DialoguePageInfoList; };
	FORCEINLINE TArray<FHorizonDialogueSegmentInfo>& GetDialogueSegmentInfoList() { return DialogueSegmentInfoList; };



	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual int32 GetTextLength();

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void RequestRebuildDialogue();
	virtual bool IsNeedRebuildDialogueMsgText();
#endif //============================End DialogueMsg: Setter/Getter=============================
#if 1 //============================Begin DialogueMsg=============================
public:
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void StartDialogue();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void StopDialogue();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SkipDialogue();


	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void PauseDialogue();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void ResumeDialogue();

	virtual void ResetDialogueMsgText();

	virtual void RebuildDialogueMsgTextBlock();
private:
	void TriggerCustomEventCallback(FHorizonDialogueSegmentInfo& InSegInfo);
	void TriggerPlaySound(FHorizonDialogueSegmentInfo& InSegInfo);

#endif //============================End DialogueMsg=============================

#if 1 //============================Begin DialogueMsg Page=============================
public:

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void NextDialogueMsgPage(bool bShouldStartTick = true);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void PrevDialogueMsgPage(bool bShouldStartTick = true);

	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|DialogueMsg")
	FORCEINLINE int32 GetCurrentPageIndex() { return CurrentPageIndex; };
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetDialogueMsgPage(int32 InPageIndex, bool bShouldStartTick = true);


	// Note: if false, user should call NextDialogueMsgPage or SetDialogueMsgPage in order to proceed to next page.
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetIsAutoNextDialogueMsgPage(bool b);

	FORCEINLINE bool IsAutoNextDialogueMsgPage() { return bIsAutoNextDialogueMsgPage; }

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SetAutoNextDialogueMsgPageIntervalRate(float InAutoNextDialogueMsgPageIntervalRate);
	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual int32 GetCurrentPageTextLength();

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual FText GetPageTextByIndex(int32 PageIndex);


	UFUNCTION(BlueprintPure, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual int32 GetNumPage();

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg", meta = (DeprecatedFunction, DeprecationMessage = "Use SkipCurrentDialoguePage instead"))
	virtual void SkipCurrentDialogueMsgPageTick();

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual void SkipCurrentDialoguePage();

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual bool IsDialogueMsgPageEnd();
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|DialogueMsg")
	virtual bool IsDialogueMsgCompleted();

private:
	void CalculateAutoNextDialogueMsgPageInterval();
	void SetPageVisiblity(bool b, const FHorizonDialoguePageInfo& InPageInfo);
	TOptional<float> GetMinimalPaddingMarginTopOffset(const FHorizonDialogueLineInfo& InLineInfo);
#endif //============================End Dialogue Page=============================

#if 1 //============================Begin Dialogue: Rebuild=============================
protected:
	virtual void RebuildSegmentInfoList();
	virtual void RebuildLineInfoList();
	virtual void RebuildPageInfoList();
	virtual void RebuildBlockInfoJustification();
	virtual void CalculateBlockSize(FHorizonDialogueBlockInfo& InBlockInfo);
	virtual void CalculateMaxLineHeight(FHorizonDialogueLineInfo& InLineInfo, const FHorizonDialogueSegmentInfo& InSegInfo, 
										const FVector2D& InOneWordSize);

	virtual void SetupRubyTextPosition(const FVector2D& InCurrentPosition, FHorizonDialogueBlockInfo& InBlockInfo, const FHorizonDialogueSegmentInfo& InSegInfo);
protected:
	virtual void BuildSegmeentDecoration(int32 InCurrentSegmentInfoIndex);
	virtual void PreBuildBlockDecoration(FHorizonDialogueBlockInfo& InBlockInfo);
	virtual void BuildBlockDecoration(FHorizonDialogueBlockInfo& InBlockInfo);

private:
	void RebuildSegmentInfoListImplement(const FHorizonDialogueSegmentInfo& parentSegParam, const FXmlNode* pCurrentNode);
	void AddTextSegmentInfo(const FString& text);

	FHorizonDialogueSegmentInfo CreateDefaultSegmentInfo(EHorizonDialogueSegmentType segmentType);
	FHorizonDialogueSegmentInfo CreateSegmentInfo(const FHorizonDialogueSegmentInfo& parentSegParam, const FXmlNode* pXmlNode);
	bool ParseRubyTextSegmentInfo(const FString& InTag, FString InValue, FHorizonDialogueSegmentInfo& InSegParam);

	TOptional<FVector2D> ParseVector2D(FString& InValue);

	TOptional<FLinearColor> ParseLinearColor(FString& InValue);
	//void BuildSegmentInfoList(const FString& segmentStr);

	FHorizonDialogueBlockInfo CreateDialogueTextBlockInfo(int32 segmentIndex, int32 segTextStartIndex, int32 segTextEndIndex, const FVector2D& pos);
	FHorizonDialogueBlockInfo CreateDialogueImageBlockInfo(int32 segmentIndex, const FVector2D& pos);
	FHorizonDialogueBlockInfo CreateDialogueFlipbookBlockInfo(int32 segmentIndex, const FVector2D& pos);

	//add BG button to Block
	void AddBackgroundButton(int32 segmentIndex,
		FHorizonDialogueBlockInfo& blockInfo,
		UCanvasPanelSlot* pCanvasPanelSlot, const FVector2D& paddingPos);
	void AddDialogueBlock(FHorizonDialogueLineInfo& lineInfo, FHorizonDialogueBlockInfo&& blockInfo);

	void LoadSound(FHorizonDialogueSegmentInfo& segInfo, FHorizonDialogueBlockInfo& blockInfo);
	void SetSegmentColor(int32 segmentIndex, int32 lineIndex, const FSlateColor& InColor);
#endif //============================End Dialogue: Rebuild=============================


#if 1 //============================Begin Dialogue Method: Text Overflow=============================
public:
	UFUNCTION(BlueprintGetter)
	EHorizonDialogueTextOverflowWrapMethod GetTextOverflowWrapMethod() const;
	UFUNCTION(BlueprintSetter)
	void SetTextOverflowWrapMethod(EHorizonDialogueTextOverflowWrapMethod InOverflowWrapMethod);
private://text overflow Wrap method implement

	bool TryAddNewLine(TCHAR currentChar, float& currentLineWidth, FVector2D& blockPos,
		const int& currentSegInfoIndex, int32& segStartCharIndex, int32& segCharIndex);


	bool TryAddDialogueBlock(const float& maxLineWidth,
		const FVector2D& oneWordSize, float& currentLineWidth,
		FVector2D& blockPos,
		const int& currentSegInfoIndex, int32& segStartCharIndex, int32& segCharIndex,
		bool bWordBreakMode = false);





	void TextOverflowWarpNormal_Implement(float& currentLineWidth, FVector2D& blockPos, const int& currentSegInfoIndex,
		const float& maxLineWidth, const FHorizonDialogueSegmentInfo& segInfo);

	void TextOverflowWarpNormal_WordBreakImplement(int32& segCharIndex, int32& segWordCharEndIndex, float& currentLineWidth, FVector2D& blockPos, const int& currentSegInfoIndex,
		const float& maxLineWidth, const FHorizonDialogueSegmentInfo& segInfo);

	void TextOverflowWarpBreakAll_Implement(float& currentLineWidth, FVector2D& blockPos, const int& currentSegInfoIndex,
		const float& maxLineWidth, const FHorizonDialogueSegmentInfo& segInfo);



#endif //============================End Dialogue Method: Text Overflow=============================


#if 1 //============================Begin Dialogue Delegate=============================
public: //delegate

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonHypertextEvent OnHypertextClickedDelegate;
	FOnHorizonHypertextEventNative OnHypertextClickedDelegateNative;


	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonHypertextEvent OnHypertextPressedDelegate;
	FOnHorizonHypertextEventNative OnHypertextPressedDelegateNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonHypertextEvent OnHypertextReleasedDelegate;
	FOnHorizonHypertextEventNative OnHypertextReleasedDelegateNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonHypertextEvent OnHypertextHoveredDelegate;
	FOnHorizonHypertextEventNative OnHypertextHoveredDelegateNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonHypertextEvent OnHypertextUnhoveredDelegate;
	FOnHorizonHypertextEventNative OnHypertextUnhoveredDelegateNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonDialogueMsgEvent OnDialogueMsgLoopFunction;
	FOnHorizonDialogueMsgEventNative OnDialogueMsgLoopFunctionNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonDialogueMsgEvent OnDialogueMsgCompleteFunction;
	FOnHorizonDialogueMsgEventNative OnDialogueMsgCompleteFunctionNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonDialoguePageEvent OnSetDialoguePageFunction;
	FOnHorizonDialoguePageEventNative OnSetDialoguePageFunctionNative;
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonDialoguePageEvent OnDialoguePageEndFunction;
	FOnHorizonDialoguePageEventNative OnDialoguePageEndFunctionNative;


	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonDialogueMsgEvent OnRebuildDialogueDelegate;
	FOnHorizonDialogueMsgEventNative OnRebuildDialogueDelegateNative;



	
	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonDialogueCustomEvent OnCustomEventDelegate;
	FOnHorizonDialogueCustomEventNative OnCustomEventDelegateNative;

	UPROPERTY(BlueprintAssignable, Category = "HorizonPlugin|UI|DialogueMsg")
	FOnHorizonDialogueCharAdvancedEvent OnCharAdvancedDelegate;
	FOnHorizonDialogueCharAdvancedEventNative OnCharAdvancedDelegateNative;

#endif //============================End Dialogue Delegate=============================


#if 1 //============================Begin CreateWidget=============================
protected:
	virtual UHorizonImage* CreateDialogueImage(FHorizonDialogueSegmentInfo& InSegInfo);
	virtual UHorizonFlipbookWidget* CreateDialogueFlipbook(FHorizonDialogueSegmentInfo& InSegInfo);
	virtual UHorizonTextBlock* CreateDialogueTextBlock(FHorizonDialogueSegmentInfo& InSegInfo);
	virtual UHorizonTextBlock* CreateDialogueRubyTextBlock(FHorizonDialogueSegmentInfo& InSegInfo);
#endif //============================End CreateWidget=============================

#if 1 //============================Begin Attribute: Content=============================
public:
	/** The text to display */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Content", meta = (MultiLine = "true"))
	FText Text;


private:
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTextOverflowWrapMethod, BlueprintSetter=SetTextOverflowWrapMethod, Category = "Content")
	EHorizonDialogueTextOverflowWrapMethod TextOverFlowWrapMethod = EHorizonDialogueTextOverflowWrapMethod::Normal;

	UPROPERTY()
	EHorizonDialogueTextOverflowWarpMethod_DEPRECATED TextOverFlowWarpMethod_DEPRECATED = EHorizonDialogueTextOverflowWarpMethod_DEPRECATED::Invalidated;

#endif //============================End Attribute: Content=============================


#if 1 //============================Begin Attribute: Behavior=============================
public:
	/** millisecond for a word */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (EditCondition = "bIsDialogueMsgText"))
	float DialogueMsgSpeed = 0.01f;

	/** should we start tick dialogue*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (EditCondition = "bIsDialogueMsgText"))
	bool bIsStartTickDialogueMsg = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (EditCondition = "bIsDialogueMsgText"))
	bool bIsRepeatDialogueMsg = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (EditCondition = "bIsRepeatDialogueMsg"))
	float RepeatDialogueMsgInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	bool bIsDialogueMsgText = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	bool bIsAutoNextDialogueMsgPage = true;

	// AutoNextDialogueMsgPageInterval = AutoNextDialogueMsgPageIntervalRate * GetTextLength();
	// Then clamp to Min, Max
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = "SetAutoNextDialogueMsgPageIntervalRate", Category = "Behavior", meta = (EditCondition = "bIsAutoNextDialogueMsgPage"))
	float AutoNextDialogueMsgPageIntervalRate = 0.01f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (EditCondition = "bIsAutoNextDialogueMsgPage"))
	float AutoNextDialogueMsgPageIntervalMin = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (EditCondition = "bIsAutoNextDialogueMsgPage"))
	float AutoNextDialogueMsgPageIntervalMax = 10.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Behavior")
	bool bIgnoreTimeDilation = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bIgnoreTimeDilation"), Category = "Behavior")
	float CustomTimeDilation = 1.0f;

	// Hotfix rebuild msg: should set to true if geometry.Size.X is 0 and message didn't appear in some case
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bIgnoreTimeDilation"), Category = "Behavior")
	bool bForceRebuildDialogueMsgText = false;
#endif //============================End Attribute: Behavior=============================
#if 1 //============================Begin Attribute: Style=============================
public:
	//Load SegmentStyles from seperate UHorizonDialogueStyleInfo class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	TArray<TSubclassOf<UHorizonDialogueStyleInfo>> StyleInfoClassList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (TitleProperty = "StyleName"))
	TArray<FHorizonDialogueSegmentInfoStyle> SegmentStyleList;
#endif //============================End Attribute: Style=============================
#if 1 //============================Begin Attribute: Appearance=============================
public:

	/** if true, then try to parse Text xml tag*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	bool bIsRichText = true;



	/** The color of the text */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FSlateColor ColorAndOpacity = FLinearColor::White;

	/** The font to render the text with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FSlateFontInfo Font;

	/** The direction the shadow is cast */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FVector2D ShadowOffset = FVector2D::UnitVector;

	/** The color of the shadow */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (DisplayName = "Shadow Color"))
	FLinearColor ShadowColorAndOpacity = FLinearColor::Transparent;

	///** Called when this text is double clicked */
	//SLATE_EVENT(FOnClicked, OnDoubleClicked)

	// UTextLayoutWidget 
	/** How the text should be aligned with the margin. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	TEnumAsByte<ETextJustify::Type> Justification;

	/** The amount of blank space left around the edges of this text line. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", AdvancedDisplay)
	FMargin LineMargin = FMargin(30, 10, 30, 5);

	/** ButtonStyle for href */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	TSubclassOf<UHorizonButton> DefaultButtonStyleWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	TArray<TSubclassOf<UHorizonDialogueMsgDecorator>> DecoratorClasses;


#endif //============================End Attribute: Appearance=============================
#if 1 //============================Begin Attribute: Performance=============================
	/** If true, it will automatically wrap this text widget with an invalidation panel */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Performance", AdvancedDisplay)
	//bool bWrapWithInvalidationPanel = false;
#endif //============================End Attribute: Performance=============================
#if 1 //============================Begin Attribute: Non-Public=============================
protected:

	TArray<FHorizonDialoguePageInfo> DialoguePageInfoList;
	TArray<FHorizonDialogueLineInfo> DialogueLineInfoList;
	TArray<FHorizonDialogueSegmentInfo> DialogueSegmentInfoList;

	int32 CurrentDialogueLineIndex = 0;
	int32 CurrentPageIndex = 0;


	float MsgDeltaTime = 0.0f;

	float RepeatDialogueMsgDeltaTime = 0.0f;

	bool bCreationFromPalette = false;

private:
	float AutoNextDialogueMsgPageDeltaTime = 0.0f;
	//AutoNextDialogueMsgPageInterval = FMath::Clamp(AutoNextDialogueMsgPageInterval, AutoNextDialogueMsgPageIntervalMin, AutoNextDialogueMsgPageIntervalMax);
	float AutoNextDialogueMsgPageInterval = 1.0f;
	UPROPERTY()
	TArray<UHorizonDialogueStyleInfo*> StyleInfoList;

	bool bNeedRebuildDialogueMsgText = false;
	// off set for recalcuate position.Y for line's in other page
	float CurrentPageHeightOffset = 0.0f;

	int32 TexLength = 0;
	float MaxLineWidth = 0.0f;


#endif //============================Begin Attribute: Non-Public=============================





};