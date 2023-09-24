// Copyright 2023, PROTOWLF, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProtoRichTextUserWidget.generated.h"

// FName param for events, in case user has multiple widgets in 1 rich text block and
// needs to specify which one is transmitting an event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextClickedEvent, FName, InName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextPressedEvent, FName, InName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextReleasedEvent, FName, InName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProtoRichTextHoverEvent, FName, InName);


/**
 * 
 */
UCLASS()
class PROTOANIMATEDTEXT_API UProtoRichTextUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Sets name set in Proto Rich Text markup. Passed as a parameter in events to Proto Rich Text
	void SetMetaDataName( const FName& InName )
	{
		MetaDataName = InName;
	}

	/** Optional event, broadcasted by child classes when clicked */
	FOnProtoRichTextClickedEvent OnClicked;

	/** Optional event, broadcasted by child classes when pressed */
	FOnProtoRichTextPressedEvent OnPressed;

	/** Optional event, broadcasted by child classes when released */
	FOnProtoRichTextReleasedEvent OnReleased;

	/** Optional event, broadcasted by child classes when hovered */
	FOnProtoRichTextHoverEvent OnHovered;

	/** Optional event, broadcasted by child classes when unhovered */
	FOnProtoRichTextHoverEvent OnUnhovered;

	FName MetaDataName;

protected:

	/** Call to broadcast an OnClick event to a ProtoRichTextBlock */
	UFUNCTION(BlueprintCallable, Category="ProtoRichText|Event")
	void CallOnClicked();

	/** Call to broadcast an OnPressed event to a ProtoRichTextBlock */
	UFUNCTION(BlueprintCallable, Category="ProtoRichText|Event")
	void CallOnPressed();

	/** Call to broadcast an OnReleased event to a ProtoRichTextBlock */
	UFUNCTION(BlueprintCallable, Category="ProtoRichText|Event")
	void CallOnReleased();

	/** Call to broadcast an OnHovered event to a ProtoRichTextBlock */
	UFUNCTION(BlueprintCallable, Category="ProtoRichText|Event")
	void CallOnHovered();

	/** Call to broadcast an OnUnhovered event to a ProtoRichTextBlock */
	UFUNCTION(BlueprintCallable, Category="ProtoRichText|Event")
	void CallOnUnhovered();

};
