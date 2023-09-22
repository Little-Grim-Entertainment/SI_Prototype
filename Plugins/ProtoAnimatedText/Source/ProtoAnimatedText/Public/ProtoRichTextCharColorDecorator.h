// Copyright 2023, PROTOWLF, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "Components/RichTextBlock.h"
#include "UObject/SoftObjectPtr.h"
#include "Rendering/DrawElements.h"
#include "Framework/Text/TextLayout.h"
#include "Framework/Text/SlateTextRun.h"
#include "Framework/Text/ITextDecorator.h"
#include "ProtoAnimatedText.h"
#include "ProtoRichTextCharColorDecorator.generated.h"


class FProtoRichTextCharColorDecorator;

/**
 * 
 */
UCLASS()
class PROTOANIMATEDTEXT_API UProtoRichTextCharColorDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()
	
public:

	static bool CheckMarkupName( const FString& InString )
	{
		return (InString == TEXT("text") || InString == TEXT("t"));
	}

	UProtoRichTextCharColorDecorator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	{
	}

	virtual TSharedPtr<ITextDecorator> CreateDecorator( URichTextBlock* InOwner ) override;

	/** Called by UProtoRichTextBlock at the start of a letter-by-letter print.
	*/
	virtual void HideText();

	/** Can use this to skip a letter-by-letter print to the end.
	*/
	virtual void ShowText();

	/** Set the run at this character index to be shown
	*/
	virtual void ShowTextAtCharacter( const int32& InCharacterIndex );

	/** Sets which character is currently printing in a letter-by-letter animation.
	* Should only be called by UProtoRichTextBlock
	* 
	* CharIndex should be the index of the character relative to the full content string (i.e. markup stripped out)
	* of the ProtoRichTextBlock. The decorator runs use ranges relative to this full content string already.
	* 
	* animationTimeSeconds is the length of the animation for the character.
	* elapsedAnimationTime (optional) start the animation this many seconds into the animation.
	*/
	virtual void SetCurrentLetterByLetterCharacter( int32 charIndex, float animationTimeSeconds, float elapsedAnimationTime = 0.0f );

	virtual void ResetCachedDecorator();

protected:

	FProtoRichTextCharColorDecorator* FDecorator;
};
